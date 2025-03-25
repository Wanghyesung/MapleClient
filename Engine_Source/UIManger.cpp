#include "UIManger.h"
#include "WSceneManger.h"
#include "WLayer.h"
#include "WInput.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WLayer.h"

namespace W
{
	UI* UIManger::m_pFoucseUI = nullptr;

	void UIManger::Update()
	{
		m_pFoucseUI = GetFoucseUI();

		if (m_pFoucseUI == nullptr)
			return;

		UI* pTargetUI = GetTargetUI(m_pFoucseUI);

		bool KeyDown = Input::GetKeyDown(eKeyCode::LBUTTON);
		bool KeyUP = Input::GetKeyUp(eKeyCode::LBUTTON);


		if (pTargetUI != nullptr)
		{
			//누르면
			pTargetUI->MouseOn();

			if (KeyDown)
			{
				pTargetUI->MouseLbtnDown();
				pTargetUI->m_bLbntDown = true;
			}

			else if (KeyUP)
			{
				pTargetUI->MouseLbtnUp();

				//저번 프레임에서도 down이 true였다면
				if (pTargetUI->m_bLbntDown)
				{
					pTargetUI->MouseLbtnClicked();
				}
				pTargetUI->m_bLbntDown = false;
			}

			pTargetUI->m_bMouseOn = false;
		}

	}

	void UIManger::SetFoucseUI(UI* _pUI)
	{
		//if (m_pFoucseUI == _pUI || _pUI == nullptr)
		//{
		//	m_pFoucseUI = _pUI;
		//	return;
		//}
		Layer& pLayer = SceneManger::GetActiveScene()->GetLayer(eLayerType::UI);
		std::vector<GameObject*>& vecUI = pLayer.m_vecGameObject;
		std::vector<GameObject*>::iterator iter = vecUI.begin();

		for (; iter != vecUI.end(); ++iter)
		{
			if (*iter == _pUI)
				break;
		}

		//가장 뒤로 보냄
		vecUI.erase(iter);
	
		vecUI.push_back(m_pFoucseUI);
	}

	void UIManger::MoveFrontChildUI(UI* pUI)
	{

	}

	UI* UIManger::GetFoucseUI()
	{
		Layer& pLayer = SceneManger::GetActiveScene()->GetLayer(eLayerType::UI);

		bool bIsLbntDown = Input::GetKeyDown(eKeyCode::LBUTTON);

		UI* pFoucseUI = m_pFoucseUI;

		if (!bIsLbntDown)
			return pFoucseUI;

		std::vector<GameObject*> vecUI = pLayer.GetGameObjects();

		std::vector<GameObject*>::iterator targetiter = vecUI.end();
		std::vector<GameObject*>::iterator iter = vecUI.begin();

		for (; iter != vecUI.end(); ++iter)
		{
			UI* pUI = dynamic_cast<UI*>(*iter);
			if (!pUI)
				continue;

			if (pUI->IsMosueOn())
			{
				targetiter = iter;
			}
		}

		if (vecUI.end() == targetiter)
			return nullptr;

		pFoucseUI = ((UI*)*targetiter);

		vecUI.erase(targetiter);
		vecUI.push_back(pFoucseUI);

		return pFoucseUI;
	}

	UI* UIManger::GetTargetUI(UI* _pParentUI)
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
	void UIManger::ReleaseChildUI()
	{
		Layer& pLayer = SceneManger::GetActiveScene()->GetLayer(eLayerType::UI);
		std::vector<GameObject*> m_vecUI = pLayer.GetGameObjects();
		
		for (GameObject* pObj : m_vecUI)
		{
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
					//가장 위에 부모라면
					if (pParentUI == nullptr)
					{
						delete pChildUI;
						pChildUI = nullptr;
					}
						
					else
					{
						//벡터에서 지우고 메모리 해제
						pChildUI->GetParentUI()->DeleteChildUI(pChildUI);
						delete pChildUI;
						pChildUI = nullptr;
					}
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
	
}