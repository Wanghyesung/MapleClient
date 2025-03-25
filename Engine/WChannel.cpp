#include "WChannel.h"
#include "WChannelNumber.h"

//viewport셋팅, rendertarget deapth버퍼

//월요일까지 플레이어 움직이게 (모든 로직)

namespace W
{
	Channel::Channel():
		m_bRenderOn(false)
	{

		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"layerbackTex", L"..\\Resources\\Texture\\UI\\StartUI\\layerback.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"layerbackMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

	}
	Channel::~Channel()
	{

	}
	void Channel::Initialize()
	{
		GetComponent<Transform>()->SetPosition(0.f, 0.f, -0.02f);
		GetComponent<Transform>()->SetScale(1.182f * 5.f , 1.f * 5.f, 0.f);

		ChannelNumber* pNumber = new ChannelNumber();
		AddChildUI(pNumber);

		//위치 넣기
		//pNumber->Initialize();
		//2.14 1.17
	}
	void Channel::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}
	void Channel::LateUpdate()
	{
		if (!m_bRenderOn)
			return;
		UI::LateUpdate();
	}
	void Channel::Render()
	{
		if (!m_bRenderOn)
			return;
		UI::Render();
	}
	void Channel::MouseOn()
	{

	}
	void Channel::MouseLbtnDown()
	{

	}
	void Channel::MouseLbtnUp()
	{

	}
	void Channel::MouseLbtnClicked()
	{

	}
}