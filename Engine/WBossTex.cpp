#include "WBossTex.h"
#include "WResources.h"

namespace W
{
	BossTex::BossTex()
	{

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"MonsterUITexMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		Resources::Load<Texture>(L"BossTex0", L"..\\Resources\\Texture\\UI\\MonsterUI\\tex0.png");
		Resources::Load<Texture>(L"BossTex1", L"..\\Resources\\Texture\\UI\\MonsterUI\\tex1.png");
		Resources::Load<Texture>(L"BossTex2", L"..\\Resources\\Texture\\UI\\MonsterUI\\tex2.png");
		Resources::Load<Texture>(L"BossTex3", L"..\\Resources\\Texture\\UI\\MonsterUI\\tex3.png");

		GetComponent<Transform>()->SetPosition(0.83f, -0.5f, 0.f);
		GetComponent<Transform>()->SetScale(0.844f * 5.55f, 1.f * 5.55f, 0.f);
	}
	BossTex::~BossTex()
	{

	}
	void BossTex::Initialize()
	{

	}
	void BossTex::Update()
	{
		UI::Update();
	}
	void BossTex::LateUpdate()
	{
		UI::LateUpdate();

	}
	void BossTex::Render()
	{
		UI::Render();

	}
	void BossTex::MouseOn()
	{
	}
	void BossTex::MouseLbtnDown()
	{
	}
	void BossTex::MouseLbtnUp()
	{
	}
	void BossTex::MouseLbtnClicked()
	{
	}
	void BossTex::ChanageTex(UINT _iTexNum)
	{
		std::wstring strNum = std::to_wstring(_iTexNum);
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"BossTex" + strNum);

		//pShMater->SetTexture(Resources::Find<Texture>(L"SKillluckUI1"));
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
}