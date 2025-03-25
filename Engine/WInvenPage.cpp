#include "WInvenPage.h"

namespace W
{
	InvenPage::InvenPage(Inventory::eItemPage _ePageType):
		m_ePageType(_ePageType),
		m_pParentInventory(nullptr),
		m_bActive(true)
	{
		std::wstring strNum = std::to_wstring((int)m_ePageType);

		std::shared_ptr<Texture> pInvenNumberTex =
			Resources::Load<Texture>(L"pInvenNumberTex"+ strNum, L"..\\Resources\\Texture\\UI\\InvenUI\\" + strNum + L".png");

		std::shared_ptr<Texture> pInvenNumberTex0 =
			Resources::Load<Texture>(L"pInvenNumberTex" + strNum+ L"_0", L"..\\Resources\\Texture\\UI\\InvenUI\\" + strNum + L"_1.png");

		std::shared_ptr<Material> pInvenNumberMater = std::make_shared<Material>();
		pInvenNumberMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pInvenNumberMater->SetTexture(pInvenNumberTex);
		Resources::Insert(L"pInvenMater"+strNum, pInvenNumberMater);

		MeshRenderer * pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pInvenNumberMater);

	}
	InvenPage::~InvenPage()
	{

	}
	void InvenPage::Initialize()
	{
		UI* pUI = GetParentUI();

		m_pParentInventory = dynamic_cast<Inventory*>(pUI);
	}
	void InvenPage::Update()
	{
		UI::Update();
	}
	void InvenPage::LateUpdate()
	{
		UI::LateUpdate();
	}
	void InvenPage::Render()
	{
		UI::Render();
	}
	void InvenPage::MouseOn()
	{

	}
	void InvenPage::MouseLbtnDown()
	{
		m_pParentInventory->SetActivePage(m_ePageType);
	}

	void InvenPage::MouseLbtnUp()
	{

	}
	void InvenPage::MouseLbtnClicked()
	{

	}

	void InvenPage::SetActive(bool _bOn)
	{
		m_bActive = _bOn;
		std::shared_ptr<Texture> pTex = nullptr;
		std::wstring strNum = std::to_wstring((int)m_ePageType);
		if (_bOn)
			pTex = Resources::Find<Texture>(L"pInvenNumberTex" + strNum);
		else
			pTex = Resources::Find<Texture>(L"pInvenNumberTex" + strNum + L"_0");

		std::shared_ptr<Material> pMaterial =
			Resources::Find<Material>(L"pInvenMater" + strNum);

		pMaterial->SetTexture(pTex);
	}
	
}