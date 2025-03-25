#include "WItemScript.h"
#include "WInput.h"
#include "WGameObject.h"
#include "WItemManager.h"
#include "WIconUI.h"
#include "WSceneManger.h"
#include "WInventory.h"
#include "WObject.h"
#include "WItemObject.h"
#include "WRigidbody.h"
namespace W
{
	ItemScript::ItemScript()
	{

	}
	ItemScript::~ItemScript()
	{

	}
	void ItemScript::Initialize()
	{

	}
	void ItemScript::Update()
	{

	}
	void ItemScript::LateUpdate()
	{

	}
	void ItemScript::Render()
	{

	}
	void ItemScript::OnCollisionEnter(Collider2D* other)
	{
		
	}
	void ItemScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		if (pGameObj->GetLayerType() == eLayerType::Player)
		{
			if(Input::GetKeyDown(eKeyCode::Z))
			{
				dynamic_cast<ItemObject*>(GetOwner())->SetActive();
				GetOwner()->GetComponent<Collider2D>()->SetActive(false);
				GetOwner()->GetComponent<Rigidbody>()->SetVelocity(Vector2(0.f, 2.f));
			}
		}
	}
	void ItemScript::OnCollisionExit(Collider2D* other)
	{

	}
}