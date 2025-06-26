#include "WGameObject.h"
#include "WRenderer.h"
#include "WGraphicDevice_Dx11.h"
#include "WTransform.h"

namespace W
{
	UINT GameObject::CREATE_ID = 0;
	
	GameObject::GameObject() :
		m_eState(eState::Active),
		m_iObjectID(0),
		m_iDir(1),
		m_bClientObject(false),
		m_bObjectPool(false),
		m_bRender(true)
	{
		AddComponent<Transform>();
	}

	GameObject::GameObject(const GameObject& _pOrigin):
		Entity(_pOrigin),
		m_eState(_pOrigin.m_eState),
		m_eLayerType(_pOrigin.m_eLayerType),
		m_iObjectID(0)
	{

		for (Component* pCom : _pOrigin.m_vecComponent)
		{
			if (pCom == nullptr)
				continue;

			Component* pComponent = pCom->CreateClone();
			if (!pComponent)
				continue;

			m_vecComponent.push_back(pComponent);

			pComponent->SetOwner(this);
		}
	}
	
	GameObject::~GameObject()
	{
		for (Component* comp : m_vecComponent)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* script : m_vecScript)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		
	}
	void GameObject::Update()
	{
		//생성위치 기록

		for (Component* comp : m_vecComponent)
		{
			comp->Update();
		}

		for (Component* script : m_vecScript)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{

		for (Component* comp : m_vecComponent)
		{
			comp->LateUpdate();
		}

		for (Component* script : m_vecScript)
		{
			script->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		GetComponent<MeshRenderer>()->Render();	
	}
	
	void GameObject::UpdateState(const wstring& _strStateName, int _iState)
	{
		
	}
	
}