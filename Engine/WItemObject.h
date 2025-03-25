#pragma once
#include "WGameObject.h"
namespace W
{
	class IconUI;

	class ItemObject : public GameObject
	{
	public:
		ItemObject(const std::wstring _strItemName);
		virtual ~ItemObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetVelociy(const Vector2& _vVel);
		void SetActive() { m_bActive = true; }
	private:
		void move_player();
		void add_item();

	private:
		bool m_bActive;
		std::wstring m_strItemName;
	};
}


