#include "WGameObject.h"
#include "WRenderer.h"
#include "WGraphicDevice_Dx11.h"
#include "WTransform.h"

namespace W
{
	GameObject::GameObject() :
		m_eState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::GameObject(const GameObject& _pOrigin):
		Entity(_pOrigin),
		m_eState(_pOrigin.m_eState),
		m_eLayerType(_pOrigin.m_eLayerType)
	{
		for (Component* pCom : _pOrigin.m_vecComponent)
		{
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

		for (Script* script : m_vecScript)
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

		for (Script* script : m_vecScript)
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

		for (Script* script : m_vecScript)
		{
			script->LateUpdate();
		}
	}
	void GameObject::Render()
	{

		for (Component* comp : m_vecComponent)
		{
			comp->Render();
		}
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		for (Script* script : m_vecScript)
		{
			script->Render();
		}
	}
	
	
}