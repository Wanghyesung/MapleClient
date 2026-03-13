#pragma once

#include "WComponent.h"

namespace W
{
	//트렌스폼은 위치데이터 저장->상수버퍼에 전달용
	//	위치 컴포넌트는 제일먼저 호출
	//	위치 컴포넌트(상수버퍼셋팅(호출용 위치관련된, 여러개의 상수버퍼 셋팅 vector4(*3)))

	struct TransformSnapshot
	{
		Vector3 vPosition;
		Vector3 vRotation;
		double dServerTime;
	};

	class Transform : public Component
	{
		DECLARE_COMPONENT_ID;

	public:
		Transform();
		Transform(const Transform& _pOrigin);
		virtual ~Transform();

		virtual Transform* CreateClone()override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetDirectPosition(const Vector3& _vPosition);
		void SetDirectPosition(float x, float y, float z);

		void SetDirectRotation(const Vector3& _vRotation);
		void SetDirectRotation(float x, float y, float z);


		void SetPosition(const Vector3& _vPosition) { m_vPosition = _vPosition; }
		void SetRotation(const Vector3& _vRotation) { m_vRotation = _vRotation; }
		void SetScale(const Vector3& _vScale) { m_vScale = _vScale; }

		void SetPosition(float x, float y, float z) { m_vPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { m_vRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { m_vScale = Vector3(x, y, z); }

		const Vector3& GetPosition() { return m_vPosition; }
		const Vector3& GetRotation() { return m_vRotation; }
		const Vector3& GetScale() { return m_vScale; }

		const Vector3& Foward() { return m_vFoward; }
		const Vector3& Right() { return m_vRight; }
		const Vector3& Up() { return m_vUp; }

		void SetParent(Transform* transform) { m_pParentTransform = transform; }
		Transform* GetParent() { return m_pParentTransform; }
		const Matrix& GetMatrix() { return m_vWorld; }
		
		Vector3 VectorLerp(const Vector3& _vFrom, const Vector3& _vTo, float fRate, bool bClampZ = true);


	private:
		void recv_transform(const Vector3& _vPosition, const Vector3& _vRotation, double _dServerTime);
		
		void lateupdate_position();
	private:
		//packet
		Vector3 m_vNextPosition;
		Vector3 m_vPrevPosition;

		Vector3 m_vNextRotation;
		Vector3 m_vPrevRotation;

		bool m_bLerp = false;
		deque<TransformSnapshot> m_deqSnapshots;
		double m_dInterpolationBackTime = 0.08;
		double m_dServerTimeOffest;

		Vector3 m_vPosition;
		Vector3 m_vRotation;
		Vector3 m_vScale;

		//내 각도의 방향
		Vector3 m_vUp;
		Vector3 m_vFoward;
		Vector3 m_vRight;

		//내 오브젝트 월드 행렬
		Matrix m_vWorld;

		Transform* m_pParentTransform;

		friend class EventManager;
	};

}

