#include "WUI.h"
#include "WTransform.h"
#include "WInput.h"
#include "WCamera.h"
#include "WSceneManger.h"
#include "WApplication.h"
#include "..\\Engine\\WIconUI.h"
#include "UIManager.h"
extern W::Application application;

namespace W
{
	UI::UI():
		m_bLbntDown(false),
		m_bMouseOn(false),
		m_bTargetOn(false),
		m_pParentUI(nullptr),
		m_vecChildUI{},
		m_iRenderOrder(0)
	{
		SetClientObject(true);
	}
	UI::UI(const UI& _pOrigin):
		GameObject(_pOrigin),
		m_bLbntDown(false),
		m_bMouseOn(false),
		m_pParentUI(nullptr),
		m_vecChildUI{},
		m_iRenderOrder(0)
	{
		SetClientObject(true);
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
		
		GameObject::LateUpdate();

		MouseOnCheck();

		ChildLateupdate();
	}
	void UI::Render()
	{
		if (m_bTargetOn)
			return;

		GameObject::Render();

		ChildRender();
	}
	void UI::MouseOn()
	{

	}
	void UI::MouseLbtnDown()
	{
		UIManager::SetLateRenderUI(this);
	}
	void UI::MouseLbtnUp()
	{
		UIManager::ReleaseLateRenderUI(this);
	}
	void UI::MouseLbtnClicked()
	{

	}
	void UI::AddChildUI(UI* _pUI , bool _bMove, int _iOrderIdx)
	{
		m_vecChildUI.push_back(_pUI);
		if (_iOrderIdx == -1)
			_pUI->m_iRenderOrder = m_vecChildUI.size() - 1;
		else
			_pUI->m_iRenderOrder = _iOrderIdx;

		//자식으로 설정될때 딱 한번만 호출
		//ture이면 부모 기준으로 물체 이동
		_pUI->m_pParentUI = this;
		if (_bMove)
			MoveUI(_pUI);
		else
			set_child_position(_pUI);
		
		sort_child();
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

	void UI::render_post()
	{
		if (!m_bTargetOn)
			return;

		GameObject::Render();

		ChildRender();
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

	void UI::sort_child()
	{
		sort(m_vecChildUI.begin(), m_vecChildUI.end(),
			[](UI* a, UI* b)
			{
				return a->GetRenderOrder() < b->GetRenderOrder();
			});
	}

	void UI::set_child_position(UI* _pChildUI)
	{
		Transform* pUITransform = _pChildUI->GetComponent<Transform>();
		Vector3 vUITransform = pUITransform->GetPosition();
		Transform* pTransform = GetComponent<Transform>();
		float z = pTransform->GetPosition().z - 0.01f;
		pUITransform->SetPosition(vUITransform.x, vUITransform.y, z);
	}


	
}