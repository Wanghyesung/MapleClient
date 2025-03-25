#include "WSkillNumber.h"
#include "WSKillStorage.h"

namespace W
{
	SkillNumber::SkillNumber(SKillStorage::eSkillNuber _eSKillNumber):
		m_bActive(false)
	{
		m_eSkillNumber = _eSKillNumber;
		std::wstring strNum = std::to_wstring(UINT(_eSKillNumber)+1);

		std::shared_ptr<Texture> pSkillNuber1 =
			Resources::Load<Texture>(L"SKillNuberTex"+strNum, L"..\\Resources\\Texture\\UI\\SkillUI\\"+ strNum+ L".png");

		std::shared_ptr<Texture> pSkillNuber10 =
			Resources::Load<Texture>(L"SKillNuberTex"+strNum + L"0", L"..\\Resources\\Texture\\UI\\SkillUI\\" + strNum + L"0.png");

		std::shared_ptr<Material> pSkillNuberMater = std::make_shared<Material>();
		pSkillNuberMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSkillNuberMater->SetTexture(pSkillNuber10);
		Resources::Insert(L"SkillNuberMater" + strNum, pSkillNuberMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSkillNuberMater);

	}
	SkillNumber::~SkillNumber()
	{

	}
	void SkillNumber::Initialize()
	{

	}
	void SkillNumber::Update()
	{
		if (!m_bActive)
			GameObject::Update();
		else
			UI::Update();
	}
	void SkillNumber::LateUpdate()
	{
		if (!m_bActive)
		{
			//마우스만 체크
			MouseOnCheck();
			GameObject::LateUpdate();
		}
		else
			UI::LateUpdate();
	}
	void SkillNumber::Render()
	{
		if (!m_bActive)
			GameObject::Render();
		else
			UI::Render();
	}
	void SkillNumber::MouseOn()
	{

	}
	void SkillNumber::MouseLbtnDown()
	{
		UI* pParent = GetParentUI();
		dynamic_cast<SKillStorage*>(pParent)->SetActiveNumber(m_eSkillNumber);
	}
	void SkillNumber::MouseLbtnUp()
	{

	}
	void SkillNumber::MouseLbtnClicked()
	{

	}
	void SkillNumber::SetActive(bool _bOn)
	{
		m_bActive = _bOn;
		std::wstring strNum = std::to_wstring(UINT(m_eSkillNumber) + 1);

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"SkillNuberMater" + strNum);
		if (!m_bActive)
		{
			m_bActive = false;
			pMater->SetTexture(Resources::Find<Texture>((L"SKillNuberTex" + strNum + L"0")));
		}
		else
		{
			m_bActive = true;
			pMater->SetTexture(Resources::Find<Texture>(L"SKillNuberTex" + strNum));
		}
	}
}