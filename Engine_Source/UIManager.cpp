#include "UIManager.h"
#include "WSceneManger.h"
#include "WLayer.h"
#include "WInput.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WLayer.h"

namespace W
{
	UI* UIManager::m_pFoucseUI = nullptr;
	UI* UIManager::m_pTargetUI = nullptr;
	UI* UIManager::m_pLateRenderUI = nullptr;
	vector<UI*> UIManager::m_vecDeleteUI = {};

	void UIManager::Update()
	{
		m_pFoucseUI = GetFoucseUI();

		if (m_pFoucseUI == nullptr)
			return;

		m_pTargetUI = GetTargetUI(m_pFoucseUI);

		bool KeyDown = Input::GetKeyDown(eKeyCode::LBUTTON);
		bool KeyUP = Input::GetKeyUp(eKeyCode::LBUTTON);


		if (m_pTargetUI != nullptr)
		{
			
			m_pTargetUI->MouseOn();

			if (KeyDown)
			{
				m_pTargetUI->MouseLbtnDown();

				m_pTargetUI->m_bLbntDown = true;
			}

			else if (KeyUP)
			{
				m_pTargetUI->MouseLbtnUp();

				//저번 프레임에서도 down이 true였다면
				if (m_pTargetUI->m_bLbntDown)
				{
					m_pTargetUI->MouseLbtnClicked();
				}
				m_pTargetUI->m_bLbntDown = false;

			}

			m_pTargetUI->m_bMouseOn = false;
		}
	}

	void UIManager::LateUpdate()
	{
		ReleaseChildUI();

		TargetUIDraw();
	}


	void UIManager::MoveFrontChildUI(UI* pUI)
	{

	}

	UI* UIManager::GetFoucseUI()
	{
		Layer* pLayer = SceneManger::GetActiveScene()->GetLayer(eLayerType::UI);

		bool bIsLbntDown = Input::GetKeyDown(eKeyCode::LBUTTON);

		UI* pFoucseUI = m_pFoucseUI;

		if (!bIsLbntDown)
			return pFoucseUI;

		const std::unordered_map<UINT, GameObject*>& hashUI = pLayer->GetGameObjects();

		auto targetiter = hashUI.end();
		auto iter = hashUI.begin();

		for (; iter != hashUI.end(); ++iter)
		{
			UI* pUI = dynamic_cast<UI*>(iter->second);
			if (!pUI)
				continue;

			if (pUI->IsMosueOn())
			{
				targetiter = iter;
			}
		}

		if (hashUI.end() == targetiter)
			return nullptr;

		pFoucseUI = ((UI*)targetiter->second);

		return pFoucseUI;
	}

	UI* UIManager::GetTargetUI(UI* _pParentUI)
	{
		bool bLbtnUP = Input::GetKeyUp(eKeyCode::LBUTTON);
		static std::vector<UI*> vecNoeTarget;
		static std::list<UI*> queue;


		UI* pTargetUI = nullptr;

		queue.clear();
		vecNoeTarget.clear();

		queue.push_back(_pParentUI);

		while (!queue.empty())
		{
			UI* pUI = queue.front();

			if (pUI->m_bLbntDown)
			{
				pTargetUI = pUI;
				break;
			}

			queue.pop_front();

			if (pUI->IsMosueOn())
			{
				if (pTargetUI != nullptr)
				{
					vecNoeTarget.push_back(pTargetUI);
				}
				pTargetUI = pUI;
			}
			else
			{
				vecNoeTarget.push_back(pUI);
			}

			const std::vector<UI*>& vecChildUI = pUI->GetChildUI();
			for (int i = 0; i < vecChildUI.size(); ++i)
			{
				queue.push_back(vecChildUI[i]);
			}
		}

		if (bLbtnUP)
		{
			for (int i = 0; i < vecNoeTarget.size(); ++i)
			{
				vecNoeTarget[i]->m_bLbntDown = false;
			}
		}
		
		return pTargetUI;
	}
	
	void UIManager::ReleaseChildUI()
	{
		Layer* pLayer = SceneManger::GetActiveScene()->GetLayer(eLayerType::UI);
		const std::unordered_map<UINT, GameObject*>& hashUI = pLayer->GetGameObjects();
		
		auto iter = hashUI.begin();
		for (iter; iter != hashUI.end(); ++iter)
		{
			GameObject* pObj = iter->second;

			UI* pUI = dynamic_cast<UI*>(pObj);
			if (!pUI)
				continue;
			std::queue<UI*> queue;
			queue.push(pUI);

			while (!queue.empty())
			{
				UI* pChildUI = queue.front();
				queue.pop();

				if (pChildUI->GetState() == GameObject::eState::Dead)
				{
					UI* pParentUI = pChildUI->GetParentUI();
					if(pParentUI)
						pParentUI->DeleteChildUI(pChildUI);

					delete pChildUI;
					pChildUI = nullptr;
				}
				else
				{
					const std::vector<UI*> vecChildUI = pChildUI->GetChildUI();

					for (UI* ChildUI : vecChildUI)
						queue.push(ChildUI);
				}
			}
		}
	}

	void UIManager::SetLateRenderUI(UI* _pTarget)
	{
		if (m_pLateRenderUI != _pTarget)
		{
			if (m_pLateRenderUI)
				m_pLateRenderUI->m_bTargetOn = false;

			m_pLateRenderUI = _pTarget;
			m_pLateRenderUI->m_bTargetOn = true;
		}
	}

	void UIManager::ReleaseLateRenderUI(UI* _pTarget)
	{
		if (m_pLateRenderUI != _pTarget)
			return;

		m_pLateRenderUI->m_bTargetOn = false;
		m_pLateRenderUI = nullptr;
	}

	void UIManager::TargetUIDraw()
	{
		if (m_pLateRenderUI == nullptr)
			return;

		m_pLateRenderUI->render_post();

	}
	
}