#include "WAlixirUI.h"
#include "WBattleManager.h"
namespace W
{
	AlixirUI::AlixirUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"alixirTex", L"..\\Resources\\Texture\\UI\\ItemUI\\alixir.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"alixirMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f);
		SetIconType(eIconType::Item);
	}
	AlixirUI::~AlixirUI()
	{
	}
	void AlixirUI::Initialize()
	{
		m_fAccHP = BattleManager::GetMaxDamage();
		m_fAccMP = BattleManager::GetMaxDamage();
	}
	void AlixirUI::Update()
	{
		ItemUI::Update();
	}
	void AlixirUI::LateUpdate()
	{
		ItemUI::LateUpdate();
	}
	void AlixirUI::Render()
	{
		ItemUI::Render();
	}
	void AlixirUI::MouseOn()
	{
		ItemUI::MouseOn();
	}
	void AlixirUI::MouseLbtnDown()
	{
		ItemUI::MouseLbtnDown();
	}
	void AlixirUI::MouseLbtnUp()
	{
		ItemUI::MouseLbtnUp();
	}
	void AlixirUI::MouseLbtnClicked()
	{
		ItemUI::MouseLbtnClicked();
	}
	void AlixirUI::Using()
	{
		int a = 10;
	}
}