#include "WBossUI.h"
#include "WBossTex.h"
#include "WBossEnterUI.h"
#include "WInput.h"
#include "WMonsterUI.h"
namespace W
{
	BossUI::BossUI():
		m_bRenderOn(false),
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::Zero),
		m_vecMonsterUI{}
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"BossBack", L"..\\Resources\\Texture\\UI\\MonsterUI\\background_.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"BossBackMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetPosition(0.f,0.f,-3.f);
		GetComponent<Transform>()->SetScale(7.f * 0.961f, 7.f , 0.f);

		Resources::Load<Texture>(L"BossUI00", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete0_0.png");
		Resources::Load<Texture>(L"BossUI10", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete1_0.png");
		Resources::Load<Texture>(L"BossUI20", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete2_0.png");
		Resources::Load<Texture>(L"BossUI30", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete3_0.png");

		//on
		Resources::Load<Texture>(L"BossUI01", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete0_1.png");
		Resources::Load<Texture>(L"BossUI11", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete1_1.png");
		Resources::Load<Texture>(L"BossUI21", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete2_1.png");
		Resources::Load<Texture>(L"BossUI31", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete3_1.png");
	}
	BossUI::~BossUI()
	{

	}
	void BossUI::Initialize()
	{
		m_pBossTex = new BossTex();
		m_pBossTex->ChanageTex(0);
		m_pBossTex->Initialize();
		AddChildUI(m_pBossTex, false);

		float fOffSetY = 0.26f;
		float fOffsetX = 0.04f;
		for (int i = 0; i < 4; ++i)
		{
			m_vecMonsterUI.push_back(new MonsterUI());
			m_vecMonsterUI[i]->set_bossnumber((eBossUnber)i);

		 	Vector3 vPosition = m_vecMonsterUI[i]->GetComponent<Transform>()->GetPosition();
			vPosition.y += fOffSetY;
			vPosition.y -= 0.33f * i ;
			vPosition.x += fOffsetX;
			m_vecMonsterUI[i]->GetComponent<Transform>()->SetPosition(vPosition);

			AddChildUI(m_vecMonsterUI[i], false);
		}

		m_pBossEnter = new BossEnterUI();
		AddChildUI(m_pBossEnter, false);
		m_pBossEnter->Initialize();

	}
	void BossUI::Update()
	{
		if (Input::GetKeyDown(eKeyCode::B))
		{
			if (!m_bRenderOn)
				m_bRenderOn = true;
			else
				m_bRenderOn = false;
		}

		if (!m_bRenderOn)
			return;
		UI::Update();
	}
	void BossUI::LateUpdate()
	{
		if (!m_bRenderOn)
			return;
		UI::LateUpdate();
	}
	void BossUI::Render()
	{
		if (!m_bRenderOn)
			return;
		UI::Render();
	}
	void BossUI::MouseOn()
	{
		if (m_bTargetOn && m_bRenderOn)
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
	void BossUI::MouseLbtnDown()
	{
		m_bTargetOn = true;
		m_vDragStartPos = Input::GetMousePos();
	}
	void BossUI::MouseLbtnUp()
	{
		m_bTargetOn = false;
	}
	void BossUI::MouseLbtnClicked()
	{

	}
	void BossUI::SetActiveBoss(eBossUnber _eNumber)
	{
		m_eNuber = _eNumber;
		//clear_monster();

		m_pBossTex->ChanageTex((UINT)_eNumber);
		m_pBossEnter->set_nextscene(_eNumber);
	}
	void BossUI::clear_monster()
	{
		for (int i = 0; i < m_vecMonsterUI.size(); ++i)
		{
			m_vecMonsterUI[i]->m_bSelete = false;
			m_vecMonsterUI[i]->clear();
		}
	}

}