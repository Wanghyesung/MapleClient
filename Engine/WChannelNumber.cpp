#include "WChannelNumber.h"

namespace W
{
	UINT ChannelNumber::NUMBER = 1;

	ChannelNumber::ChannelNumber():
		m_iNumber(NUMBER)
	{
		++NUMBER;

		std::wstring strNum = std::to_wstring(m_iNumber);

		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"ch" + strNum + L"_Tex", L"..\\Resources\\Texture\\UI\\StartUI\\ch" + strNum + L"_.png");

		pTex =
			Resources::Load<Texture>(L"ch" + strNum + L"Tex", L"..\\Resources\\Texture\\UI\\StartUI\\ch" + strNum + L".png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"chMater" + strNum, pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	ChannelNumber::~ChannelNumber()
	{

	}
	void ChannelNumber::Initialize()
	{

	}
	void ChannelNumber::Update()
	{
		UI::Update();
	}
	void ChannelNumber::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ChannelNumber::Render()
	{
		UI::Render();
	}
	void ChannelNumber::MouseOn()
	{

	}
	void ChannelNumber::MouseLbtnDown()
	{
		std::wstring strNum = std::to_wstring(m_iNumber);
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"chMater" + strNum);
		pMater->SetTexture(Resources::Find<Texture>(L"ch" + strNum + L"_Tex"));

	}
	void ChannelNumber::MouseLbtnUp()
	{
		std::wstring strNum = std::to_wstring(m_iNumber);
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"chMater" + strNum);
		pMater->SetTexture(Resources::Find<Texture>(L"ch" + strNum + L"Tex"));
	}
	void ChannelNumber::MouseLbtnClicked()
	{

	}
}