#include "WEXP.h"

namespace W
{
	EXP::EXP()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"EXPTex", L"..\\Resources\\Texture\\UI\\Interface\\EXP.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"EXPMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	EXP::~EXP()
	{
	}
	void EXP::Initialize()
	{
	}
	void EXP::Update()
	{
		UI::Update();
	}
	void EXP::LateUpdate()
	{
		UI::LateUpdate();
	}
	void EXP::Render()
	{
		UI::Render();
	}
	void EXP::MouseOn()
	{
	}
	void EXP::MouseLbtnDown()
	{
	}
	void EXP::MouseLbtnUp()
	{
	}
	void EXP::MouseLbtnClicked()
	{
	}
}