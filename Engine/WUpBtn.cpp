#include "WUpBtn.h"

namespace W
{
	UINT UpBtn::m_iBntCount = 0;

	UpBtn::UpBtn():
		m_iNumber(m_iBntCount)
	{
		std::wstring strNum = std::to_wstring(m_iBntCount);
		//default
		std::shared_ptr<Texture> pUpBtnTex =
			Resources::Load<Texture>(L"UpBtnTex1", L"..\\Resources\\Texture\\UI\\StatUI\\up_1.png");

		//down
		pUpBtnTex = Resources::Load<Texture>(L"UpBtnTex0", L"..\\Resources\\Texture\\UI\\StatUI\\up_0.png");


		std::shared_ptr<Material> pUpBntMater = std::make_shared<Material>();
		pUpBntMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pUpBntMater->SetTexture(pUpBtnTex);
		Resources::Insert(L"UpBtnMater" + strNum, pUpBntMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pUpBntMater);

		//Ä«¿îÆ®
		++m_iBntCount;
	}
	UpBtn::~UpBtn()
	{

	}
	void UpBtn::Initialize()
	{

	}
	void UpBtn::Update()
	{
		UI::Update();
	}
	void UpBtn::LateUpdate()
	{
		UI::LateUpdate();
	}
	void UpBtn::Render()
	{
		UI::Render();
	}
	void UpBtn::MouseOn()
	{

	}
	void UpBtn::MouseLbtnDown()
	{
		std::wstring strNum = std::to_wstring(m_iNumber);
		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"UpBtnMater" + strNum);
		pShMater->SetTexture(Resources::Find<Texture>(L"UpBtnTex1"));
	}
	void UpBtn::MouseLbtnUp()
	{
		std::wstring strNum = std::to_wstring(m_iNumber);
		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"UpBtnMater" + strNum);
		pShMater->SetTexture(Resources::Find<Texture>(L"UpBtnTex0"));
	}
	void UpBtn::MouseLbtnClicked()
	{

	}
}