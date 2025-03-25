#include "WMonsterUI.h"
#include "WResources.h"
#include "WBossUI.h"
namespace W
{
	UINT MonsterUI::COUNT = 0;

	MonsterUI::MonsterUI():
		m_iCount(COUNT),
		m_eBossNumber(BossUI::eBossUnber::End),
		m_bSelete(false)
	{
		++COUNT;
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		//pMater->SetTexture(pTex);
		std::wstring strNum = std::to_wstring(m_iCount);
		Resources::Insert(L"MonsterUIMater" + strNum, pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		//off
		GetComponent<Transform>()->SetPosition(-2.4f, 1.82f, 0.f);
		GetComponent<Transform>()->SetScale(2.f * 0.755f, 2.f * 0.169f, 0.f);

	}
	MonsterUI::~MonsterUI()
	{

	}
	void MonsterUI::Initialize()
	{

	}
	void MonsterUI::Update()
	{
		UI::Update();
	}
	void MonsterUI::LateUpdate()
	{
		UI::LateUpdate();

	}
	void MonsterUI::Render()
	{
		UI::Render();

	}
	void MonsterUI::MouseOn()
	{
		std::wstring strSelete;
		if (m_bSelete)
			strSelete = L"1";
		else
			strSelete = L"0";

		std::wstring strBossNum = std::to_wstring((UINT)m_eBossNumber);
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"BossUI" + strBossNum + strSelete);

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
	void MonsterUI::MouseLbtnDown()
	{
		m_bSelete = true;
	}

	void MonsterUI::MouseLbtnUp()
	{

	}

	void MonsterUI::MouseLbtnClicked()
	{
		m_bSelete = false;
		//야기서 고르면 active보스 변경
		dynamic_cast<BossUI*>(GetParentUI())->SetActiveBoss(m_eBossNumber);
	}

	void MonsterUI::set_bossnumber(BossUI::eBossUnber _eNumber)
	{
		m_eBossNumber = _eNumber;
		clear();
	}

	void MonsterUI::clear()
	{
		std::wstring strBossNum = std::to_wstring((UINT)m_eBossNumber);
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"BossUI" + strBossNum + L"0");

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
	
}