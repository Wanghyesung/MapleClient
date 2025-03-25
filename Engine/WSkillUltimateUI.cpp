#include "WSkillUltimateUI.h"
#include "WSkillManager.h"
#include "WPlayer.h"
namespace W
{
	SkillUltimateUI::SkillUltimateUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::ultimate);
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillUltimateUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\6\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillUltimateUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\6\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillUltimateUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\6\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		//pSKillMater->SetRenderinMode(eRenderingMode::Transparent);
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillUltimateMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}

	SkillUltimateUI::~SkillUltimateUI()
	{

	}
	void SkillUltimateUI::Initialize()
	{

	}
	void SkillUltimateUI::Update()
	{
		SKill::Update();
	}
	void SkillUltimateUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillUltimateUI::Render()
	{
		SKill::Render();
	}
	void SkillUltimateUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillUltimateUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillUltimateMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillUltimateUI1"));
	}
	void SkillUltimateUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillUltimateMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillUltimateUI0"));
	}

	void SkillUltimateUI::MouseLbtnClicked()
	{

	}

	void SkillUltimateUI::Using()
	{
		
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::ultimate);
	}
}