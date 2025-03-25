#include "WChannleBntUI.h"

namespace W
{
	ChannleBntUI::ChannleBntUI()
	{
		std::shared_ptr<Texture> pChannelTex1 =
			Resources::Load<Texture>(L"ChannelTex1", L"..\\Resources\\Texture\\UI\\Interface\\channel.png");

		std::shared_ptr<Material> pChannelMater1 = std::make_shared<Material>();
		pChannelMater1->SetShader(Resources::Find<Shader>(L"UIShader"));
		pChannelMater1->SetTexture(pChannelTex1);
		Resources::Insert(L"ChannelMater1", pChannelMater1);
		
		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pChannelMater1);
	}

	ChannleBntUI::~ChannleBntUI()
	{

	}
	void ChannleBntUI::Initialize()
	{

	}
	void ChannleBntUI::Update()
	{
		UI::Update();
	}
	void ChannleBntUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ChannleBntUI::Render()
	{
		UI::Render();
	}
	void ChannleBntUI::MouseOn()
	{
		int a = 10;
	}
	void ChannleBntUI::MouseLbtnDown()
	{
		int a = 10;
	}
	void ChannleBntUI::MouseLbtnUp()
	{
	}
	void ChannleBntUI::MouseLbtnClicked()
	{
	}
}