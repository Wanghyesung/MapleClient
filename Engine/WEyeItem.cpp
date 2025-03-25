#include "WEyeItem.h"
#include "WBattleManager.h"
#include "WHairItem.h"
#include "WSceneManger.h"
#include "WPlayer.h"
namespace W
{
	EyeItem::EyeItem()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"eyeItemTex", L"..\\Resources\\Texture\\UI\\ItemUI\\iconRaw0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"eyeitemMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.5f, 0.1f * 2.9f, 0.f);
		SetIconType(eIconType::Cash);
	}
	EyeItem::~EyeItem()
	{
	}
	void EyeItem::Initialize()
	{

	}
	void EyeItem::Update()
	{
		ItemUI::Update();
	}
	void EyeItem::LateUpdate()
	{
		ItemUI::LateUpdate();
	}
	void EyeItem::Render()
	{
		ItemUI::Render();
	}
	void EyeItem::MouseOn()
	{
		ItemUI::MouseOn();
	}
	void EyeItem::MouseLbtnDown()
	{
		ItemUI::MouseLbtnDown();
	}
	void EyeItem::MouseLbtnUp()
	{
		ItemUI::MouseLbtnUp();
	}
	void EyeItem::MouseLbtnClicked()
	{
		ItemUI::MouseLbtnClicked();
	}

}