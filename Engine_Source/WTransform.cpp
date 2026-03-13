#include "WTransform.h"
#include "WRenderer.h"
#include "WConstantBuffer.h"
#include "WCamera.h"
#include "WTime.h"
#include "WGameObject.h"
#include "WInput.h"
#include "WUI.h"
namespace W
{
	using namespace W;
	
	UINT Transform::COMPONENT_ID = 0;

	Transform::Transform() :
		Component(eComponentType::Transform),
		m_vNextPosition(Vector3::Zero),
		m_vPrevPosition(Vector3::Zero),
		m_vPosition(Vector3::Zero),
		m_vRotation(Vector3::Zero),
		m_vScale(Vector3::One),
		m_pParentTransform(nullptr)
	{

	}
	Transform::Transform(const Transform& _pOrigin):
		Component(eComponentType::Transform),
		m_vNextPosition(Vector3::Zero),
		m_vPrevPosition(Vector3::Zero),
		m_vPosition(_pOrigin.m_vPosition),
		m_vRotation(_pOrigin.m_vRotation),
		m_vScale(_pOrigin.m_vScale),
		m_pParentTransform(nullptr)
	{
	}
	Transform::~Transform()
	{

	}
	Transform* Transform::CreateClone()
	{
		return new Transform(*this);
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{

	}
	void Transform::LateUpdate()
	{
		if (!GetOwner()->IsClientObject())
		{
			if(m_bLerp)
				lateupdate_position();
		}	
		
		m_vWorld = Matrix::Identity;//전지 행렬
		
		//크기 행렬 생성
		Matrix mScale = Matrix::CreateScale(m_vScale);

		Matrix mRotation;
		mRotation = Matrix::CreateRotationX(m_vRotation.x);
		mRotation = Matrix::CreateRotationY(m_vRotation.y);
		mRotation = Matrix::CreateRotationZ(m_vRotation.z);

		
		Matrix mPosition;
		mPosition.Translation(m_vPosition);

		m_vWorld = mScale * mRotation * mPosition;
		
		m_vUp = Vector3::TransformNormal(Vector3::Up, mRotation);
		m_vFoward = Vector3::TransformNormal(Vector3::Forward, mRotation);
		m_vRight = Vector3::TransformNormal(Vector3::Right, mRotation);

		//내 로컬 -> 월드 -> 부모 행렬
		if (m_pParentTransform)
			m_vWorld *= m_pParentTransform->m_vWorld;

	}
	void Transform::Render()
	{

	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.m_mWorld = m_vWorld;
		trCB.m_mView = Camera::GetGpuViewMatrix();
		trCB.m_mProjection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Transform];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&trCB);
		pConstBuffer->Bind(eShaderStage::VS);
		pConstBuffer->Bind(eShaderStage::HS);
		pConstBuffer->Bind(eShaderStage::DS);
		pConstBuffer->Bind(eShaderStage::GS);
		pConstBuffer->Bind(eShaderStage::PS);
	}

	void Transform::lateupdate_position()
	{
		if (m_deqSnapshots.size() == 0)
		{
			return;
		}

		double currentServerTime = Time::AccTime();
		double dRenderTime = currentServerTime - m_dInterpolationBackTime;

		while (m_deqSnapshots.size() >= 2)
		{
			if (m_deqSnapshots[1].dServerTime > dRenderTime)
				break;

			m_deqSnapshots.pop_front();
		}

		if (m_deqSnapshots.size() >= 2)
		{
			TransformSnapshot& prevSnapshot = m_deqSnapshots[0];
			TransformSnapshot& nextSnapshot = m_deqSnapshots[1];

			double totalTime = nextSnapshot.dServerTime - prevSnapshot.dServerTime;
			double currentTime = dRenderTime - prevSnapshot.dServerTime;

			float ratio = 0.f;

			if (totalTime > 0.0)
			{
				ratio = (float)(currentTime / totalTime);
			}

			if (ratio < 0.f)
			{
				ratio = 0.f;
			}

			if (ratio > 1.f)
			{
				ratio = 1.f;
			}
			
			m_vPosition = VectorLerp(prevSnapshot.vPosition, nextSnapshot.vPosition, ratio, false);
			m_vRotation = VectorLerp(prevSnapshot.vRotation, nextSnapshot.vRotation, ratio, false);
		}
		else
		{
			m_vPosition = m_deqSnapshots[0].vPosition;
			m_vRotation = m_deqSnapshots[0].vRotation;
		}
	}

	Vector3 Transform::VectorLerp(const Vector3& _vFrom, const Vector3& _vTo, float _fRate, bool _bClampZ)
	{
		Vector3 vResult = Vector3::Zero;

		vResult.x = _vFrom.x + (_vTo.x - _vFrom.x) * _fRate;
		vResult.y = _vFrom.y + (_vTo.y - _vFrom.y) * _fRate;

		if (_bClampZ)
			vResult.z = _vFrom.z;
		else
			vResult.z = _vFrom.z + (_vTo.z - _vFrom.z) * _fRate;

		return vResult;
	}

	void Transform::recv_transform(const Vector3& _vPosition, const Vector3& _vRotation, double _dServerTime)
	{
		TransformSnapshot tSnapShot;
		tSnapShot.vPosition = _vPosition;
		tSnapShot.vRotation = _vRotation;
		tSnapShot.dServerTime = Time::AccTime();

		m_deqSnapshots.push_back(tSnapShot);

		while (m_deqSnapshots.size() > 10)
			m_deqSnapshots.pop_front();

		m_dServerTimeOffest = _dServerTime - Time::AccTime();
		m_bLerp = true;
	}
	

	void Transform::SetDirectPosition(const Vector3& _vPosition)
	{
		m_bLerp = false;
		TransformSnapshot tSnapShot;
		tSnapShot.vPosition = _vPosition;
		tSnapShot.vRotation = m_vRotation;
		tSnapShot.dServerTime = Time::AccTime();

		m_deqSnapshots.push_back(tSnapShot);

		m_vPosition = _vPosition;
	}

	void Transform::SetDirectPosition(float x, float y, float z)
	{
		m_bLerp = false;
		Vector3 vPosition = Vector3(x, y, z);

		TransformSnapshot tSnapShot;
		tSnapShot.vPosition = vPosition;
		tSnapShot.dServerTime = Time::AccTime();

		m_deqSnapshots.push_back(tSnapShot);
		m_vPosition = vPosition;

	}
	void Transform::SetDirectRotation(const Vector3& _vRotation)
	{
		m_bLerp = false;
		TransformSnapshot tSnapShot;
		tSnapShot.vPosition = m_vPosition;
		tSnapShot.vRotation = _vRotation;
		tSnapShot.dServerTime = Time::AccTime();

		m_deqSnapshots.push_back(tSnapShot);

		m_vRotation = _vRotation;
	}
	void Transform::SetDirectRotation(float x, float y, float z)
	{
		m_bLerp = false;
		Vector3 vRotation = Vector3(x, y, z);

		TransformSnapshot tSnapShot;
		tSnapShot.vPosition = m_vPosition;
		tSnapShot.vRotation = vRotation;
		tSnapShot.dServerTime = Time::AccTime();

		m_deqSnapshots.push_back(tSnapShot);

		m_vRotation = vRotation;
	}
}