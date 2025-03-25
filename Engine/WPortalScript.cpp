#include "WPortalScript.h"
#include "WGameObject.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WEventManager.h"
namespace W
{
	PortalScript::PortalScript():
		m_strNextScene{}
	{

	}
	PortalScript::~PortalScript()
	{

	}
	void PortalScript::Initialize()
	{

	}
	void PortalScript::Update()
	{

	}
	void PortalScript::LateUpdate()
	{

	}
	void PortalScript::Render()
	{

	}
	void PortalScript::OnCollisionEnter(Collider2D* other)
	{
		
	}
	void PortalScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		if (pGameObj->GetLayerType() == eLayerType::Player)
		{
			if(Input::GetKeyDown(eKeyCode::UP))
			{
				EventManager::ChangeScene(m_strNextScene);
			}
		}
	}
	void PortalScript::OnCollisionExit(Collider2D* other)
	{

	}
}