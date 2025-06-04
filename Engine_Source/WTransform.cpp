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

	Transform::Transform():
		Component(eComponentType::Transform),
		m_vNextPosition(Vector3::Zero), 
		m_vPrevPosition(Vector3::Zero),
		m_fLerpTime(1.f/ SERVER_TICK_RATE),
		m_fCurLerpTime(0.f),
		m_fCurLerpRate(0.f),
		m_fRecvTime(0.f),
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
		m_fLerpTime(SERVER_TICK_RATE / 1.f),
		m_fCurLerpTime(0.f),
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
			if (m_fCurLerpTime / m_fLerpTime < 1.f)
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
		m_fCurLerpTime += Time::DeltaTime();

		m_fCurLerpRate = m_fCurLerpTime/ m_fLerpTime;

		//fCurRate = std::clamp
		if (m_fCurLerpRate >= 1.f)
			m_fCurLerpRate = 1.f;
		
		m_vPosition = PositionLerp(m_vPrevPosition, m_vNextPosition, m_fCurLerpRate, false);
	}

	void Transform::recv_position(Vector3 _vPosition)
	{
		m_vPrevPosition = m_vPosition;
		m_vNextPosition = _vPosition;

		m_fCurLerpTime = 0.f;
	}

	Vector3 Transform::PositionLerp(const Vector3& _vFrom, const Vector3& _vTo, float fRate, bool bClampZ)
	{
		Vector3 vResult = Vector3::Zero;

		vResult.x = _vFrom.x + (_vTo.x - _vFrom.x) * fRate;
		vResult.y = _vFrom.y + (_vTo.y - _vFrom.y) * fRate;

		if (bClampZ)
			vResult.z = _vFrom.z; // z값 고정 또는 제한된 범위로만 보간
		else
			vResult.z = _vFrom.z + (_vTo.z - _vFrom.z) * fRate;
	
		return vResult;
	}

	void Transform::SetDirectPosition(const Vector3& _vPosition)
	{
		m_fCurLerpTime = m_fLerpTime;

		m_vNextPosition = _vPosition;
		m_vPrevPosition = _vPosition;
		m_vPosition = _vPosition;
	}
	void Transform::SetDirectPosition(float x, float y, float z)
	{
		Vector3 vPosition = Vector3(x, y, z);

		m_fCurLerpTime = m_fLerpTime;

		m_vNextPosition = vPosition;
		m_vPrevPosition = vPosition;
		m_vPosition = vPosition;
	}
}