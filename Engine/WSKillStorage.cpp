#include "WSKillStorage.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSkillNumber1.h"
#include "WSkillNumber2.h"
#include "WSkillNumber3.h"
#include "WSkillNumber4.h"
#include "WSkillNumber5.h"
#include "WSkillNumber.h"
#include "WSKillNumber6.h"
namespace W
{
	SKillStorage::SKillStorage():
		m_vecSkillNumber{},
		m_bRenderOn(false),
		m_bTargetOn(false),
		m_vUIStartPosition(Vector2::One),
		m_vUIEndPosition(Vector2::One),
		m_vUIDiffPosition(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"SkillUITex", L"..\\Resources\\Texture\\UI\\SkillUI\\SkillUI.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"SkillUIMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		m_vecSkillNumber.resize((UINT)eSkillNuber::None);
	}
	SKillStorage::~SKillStorage()
	{

	}
	void SKillStorage::Initialize()
	{
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -5.f);
		pTransform->SetScale(0.881f * 3.8f, 1.f * 3.8f, 0.f); //0.881 : 1


#pragma region SKillNuber
		//스킬 숫자
		m_vecSkillNumber[(UINT)eSkillNuber::First] = new SkillNumber1();
		Transform* pSkillNumberTr = m_vecSkillNumber[(UINT)eSkillNuber::First]->GetComponent<Transform>();
		pSkillNumberTr->SetPosition(-1.1f, 1.54f, -0.01f);
		pSkillNumberTr->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::First]);
		m_vecSkillNumber[(UINT)eSkillNuber::First]->Initialize();

		m_vecSkillNumber[(UINT)eSkillNuber::Second] = new SkillNumber2();
		Transform* pSkillNumberTr2 = m_vecSkillNumber[(UINT)eSkillNuber::Second]->GetComponent<Transform>();
		pSkillNumberTr2->SetPosition(-0.85f, 1.54f, -0.01f);
		pSkillNumberTr2->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::Second]);
		m_vecSkillNumber[(UINT)eSkillNuber::Second]->Initialize();

		m_vecSkillNumber[(UINT)eSkillNuber::Third] = new SkillNumber3();
		Transform* pSkillNumberTr3 = m_vecSkillNumber[(UINT)eSkillNuber::Third]->GetComponent<Transform>();
		pSkillNumberTr3->SetPosition(-0.6f, 1.54f, -0.01f);
		pSkillNumberTr3->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::Third]);
		m_vecSkillNumber[(UINT)eSkillNuber::Third]->Initialize();

		m_vecSkillNumber[(UINT)eSkillNuber::Four] = new SkillNumber4();
		Transform* pSkillNumberTr4 = m_vecSkillNumber[(UINT)eSkillNuber::Four]->GetComponent<Transform>();
		pSkillNumberTr4->SetPosition(-0.35f, 1.54f, -0.01f);
		pSkillNumberTr4->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::Four]);
		m_vecSkillNumber[(UINT)eSkillNuber::Four]->Initialize();

		m_vecSkillNumber[(UINT)eSkillNuber::Five] = new SkillNumber5();
		Transform* pSkillNumberTr5 = m_vecSkillNumber[(UINT)eSkillNuber::Five]->GetComponent<Transform>();
		pSkillNumberTr5->SetPosition(-0.1f, 1.54f, -0.01f);
		pSkillNumberTr5->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::Five]);
		m_vecSkillNumber[(UINT)eSkillNuber::Five]->Initialize();

		m_vecSkillNumber[(UINT)eSkillNuber::Six] = new SkillNumber6();
		Transform* pSkillNumberTr6 = m_vecSkillNumber[(UINT)eSkillNuber::Six]->GetComponent<Transform>();
		pSkillNumberTr6->SetPosition(0.15f, 1.54f, -0.01f);
		pSkillNumberTr6->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(m_vecSkillNumber[(UINT)eSkillNuber::Six]);
		m_vecSkillNumber[(UINT)eSkillNuber::Six]->Initialize();
		
#pragma endregion

	}
	void SKillStorage::Update()
	{
		if (!m_bRenderOn)
			return;
		UI::Update();
	}
	void SKillStorage::LateUpdate()
	{
		if (!m_bRenderOn)
			return;
		UI::LateUpdate();
	}
	void SKillStorage::Render()
	{
		if (!m_bRenderOn)
			return;
		UI::Render();
	}
	void SKillStorage::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			//m_vUIStartPosition += vDiff;
			//m_vUIEndPosition += vDiff;

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void SKillStorage::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void SKillStorage::MouseLbtnUp()
	{
		m_bTargetOn = false;

		//m_vUIEndPosition = Input::GetMousePos();
	}
	void SKillStorage::MouseLbtnClicked()
	{

	}
	void SKillStorage::SetActiveNumber(eSkillNuber _eSkillNumber)
	{
		for (SkillNumber* pNumber : m_vecSkillNumber)
		{
			if (pNumber == nullptr)
				continue;

			if (pNumber->GetSkillNumber() == _eSkillNumber)
				pNumber->SetActive(true);
			else
				pNumber->SetActive(false);
		}
	}
}