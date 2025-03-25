#include "WSkillLoadUI.h"
#include "WSkillManager.h"
namespace W
{
	SkillLoadUI::SkillLoadUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::load);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillLoadUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\darkload\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillLoadUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\darkload\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillLoadUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\darkload\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillLoadMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}

	SkillLoadUI::~SkillLoadUI()
	{

	}
	void SkillLoadUI::Initialize()
	{

	}
	void SkillLoadUI::Update()
	{
		SKill::Update();
	}
	void SkillLoadUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillLoadUI::Render()
	{
		SKill::Render();
	}
	void SkillLoadUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillLoadUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillLoadMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillLoadUI1"));
	}
	void SkillLoadUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillLoadMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillLoadUI0"));
	}

	void SkillLoadUI::MouseLbtnClicked()
	{

	}
	void SkillLoadUI::Using()
	{
		//SkillManager::SetActiveSkill(GetPlayerSkill());
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::load);
	}
}