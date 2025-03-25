#include "WSkillBlastUI.h"
#include "WSkillManager.h"
#include "WPlayer.h"
namespace W
{
	SkillBlastUI::SkillBlastUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::blast);
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillBlastUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\blasting\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillBlastUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\blasting\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillBlastUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\blasting\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		//pSKillMater->SetRenderinMode(eRenderingMode::Transparent);
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillBlastMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}

	SkillBlastUI::~SkillBlastUI()
	{

	}
	void SkillBlastUI::Initialize()
	{

	}
	void SkillBlastUI::Update()
	{
		SKill::Update();
	}
	void SkillBlastUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillBlastUI::Render()
	{
		SKill::Render();
	}
	void SkillBlastUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillBlastUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillBlastMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillBlastUI1"));
	}
	void SkillBlastUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillBlastMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillBlastUI0"));
	}

	void SkillBlastUI::MouseLbtnClicked()
	{

	}

	void SkillBlastUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::blast);
	}
}