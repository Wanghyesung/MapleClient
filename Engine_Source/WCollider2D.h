#pragma once
#include "WComponent.h"
#include "WTransform.h"
namespace W
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		virtual ~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType _eType) { m_eType = _eType; }
		void SetSize(Vector2 _vSize) { m_vSize = _vSize; }
		Vector2 GetSize() { return m_vSize; }
		void SetCenter(Vector2 _Center) { m_vCenter = _Center; }
		Vector2 GetCenter() { return m_vCenter; }
		UINT GetColliderID() { return m_iColliderID; }
		
		Vector3 GetPosition() { return m_vPosition; }


		void SetActive(bool _bActive) { m_bActive = _bActive; }
		bool IsActive() { return m_bActive; }
	private:
		static UINT ColliderNumber;
		UINT m_iColliderID;

		bool m_bActive;

		eColliderType m_eType;
		Transform* m_pTransform;

		Vector3 m_vPosition;
		Vector2 m_vSize;
		Vector2 m_vCenter;

	};
}


