#include "WUI.h"
#include "WTransform.h"
#include "WInput.h"
#include "WCamera.h"
#include "WSceneManger.h"
#include "WApplication.h"
#include "..\\Engine\\WIconUI.h"

extern W::Application application;

namespace W
{
	UI::UI():
		m_bLbntDown(false),
		m_bMouseOn(false),
		m_pParentUI(nullptr),
		m_vecChildUI{}
	{
		
	}
	UI::UI(const UI& _pOrigin):
		GameObject(_pOrigin),
		m_bLbntDown(false),
		m_bMouseOn(false),
		m_pParentUI(nullptr),
		m_vecChildUI{}
	{
	}
	UI::~UI()
	{
		for (UI* pChildUI : m_vecChildUI)
		{
			if (pChildUI != nullptr)
			{
				delete pChildUI;
				pChildUI = nullptr;
			}
		}
	}
	void UI::Initialize()
	{

	}
	void UI::Update()
	{
		GameObject::Update();

		ChildUpdate();
	}
	void UI::LateUpdate()
	{
		//여기서 부모 UI랑 같이 움직이게
		//UI* pParentUI = GetParentUI();
		//if (pParentUI != nullptr)
		//{
		//	float fParentZ = pParentUI->GetComponent<Transform>()->GetPosition().z;
		//	Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		//	GetComponent<Transform>()->SetPosition(vPosition.x, vPosition.y, (vPosition.z + fParentZ));
		//}

		GameObject::LateUpdate();

		MouseOnCheck();

		ChildLateupdate();
	}
	void UI::Render()
	{
		GameObject::Render();

		ChildRender();
	}
	void UI::MouseOn()
	{

	}
	void UI::MouseLbtnDown()
	{

	}
	void UI::MouseLbtnUp()
	{

	}
	void UI::MouseLbtnClicked()
	{

	}
	void UI::AddChildUI(UI* _pUI , bool _bMove)
	{
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;

		//자식으로 설정될때 딱 한번만 호출
		//ture이면 부모 기준으로 물체 이동
		if (_bMove)
		{
			MoveUI(_pUI);
		}
		else
		{
			Transform* pUITransform = _pUI->GetComponent<Transform>();
			Vector3 vUITransform = pUITransform->GetPosition();
			Transform* pTransform = GetComponent<Transform>();
			float z = pTransform->GetPosition().z - 0.01f;
			pUITransform->SetPosition(vUITransform.x, vUITransform.y,z);
		}
			
	}

	void UI::DeleteChildUI(UI* _pUI)
	{
		std::vector<UI*>::iterator iter = m_vecChildUI.begin();
		
		for (iter; iter != m_vecChildUI.end(); ++iter)
		{
			if (*iter == _pUI)
			{
				m_vecChildUI.erase(iter);
				return;
			}
		}

	}


	void UI::ChildUpdate()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->Update();
		}
	}
	void UI::ChildRender()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->Render();
		}
	}
	void UI::ChildLateupdate()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->LateUpdate();
		}
	}


	void UI::MouseOnCheck()
	{
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vScale = pTransform->GetScale();
		Vector3 vPos = pTransform->GetPosition();

		Vector2 vMousePos = Input::GetMousePos();
		
		if ((vPos.x - vScale.x/2.f) <= vMousePos.x && vMousePos.x <= (vPos.x + vScale.x/2.f) &&
			(vPos.y - vScale.y/2.f) <= vMousePos.y && vMousePos.y <= (vPos.y + vScale.y/2.f))
			m_bMouseOn = true;
		else
			m_bMouseOn = false;
		
	}

	//안쓰는 함수
	//void UI::MoveToParent()
	//{
	//	if (m_pParentUI != nullptr)
	//	{
	//		Vector3 vFinalPos = {};
	//	
	//		Transform* pParentTransform = m_pParentUI->GetComponent<Transform>();
	//		Vector3 vParentPos = pParentTransform->GetPosition();
	//	
	//		if (vParentPos != m_vParntUIPos)
	//		{
	//			m_vParntUIPos = vParentPos;
	//	
	//			Transform* pTransform = GetComponent<Transform>();
	//			Vector3 vPos = pTransform->GetPosition();
	//	
	//			vFinalPos = vPos + vParentPos;
	//			//vPos.x += vParentPos.x;
	//			//vPos.y += vParentPos.y;
	//			pTransform->SetPosition(vFinalPos);
	//		}
	//	}
	//}

	void UI::MoveUI(UI* _pUI)
	{
		Vector3 vFinalPos = {};

		Transform* pParentTransform = GetComponent<Transform>();
		Vector3 vParentPos = pParentTransform->GetPosition();

		Transform* pTransform = _pUI->GetComponent<Transform>();
		Vector3 vPos = pTransform->GetPosition();

		vFinalPos = vParentPos + vPos;
		pTransform->SetPosition(vFinalPos);
	}

	void UI::MoveToParent(Vector2 _vDiff)
	{
		std::queue<UI*> queue;

		queue.push(this);

		while (!queue.empty())
		{
			UI* pUI = queue.front();

			if (pUI != this)
			{
				Transform* pChildTr = pUI->GetComponent<Transform>();
				pChildTr->SetPosition(pChildTr->GetPosition() + _vDiff);
			}
			queue.pop();

			const std::vector<UI*> vecChildUI = pUI->GetChildUI();

			for (UI* ChildUI : vecChildUI)
				queue.push(ChildUI);
		}

	}
	
}