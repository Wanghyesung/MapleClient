#include "WSKillSpeedUI.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WSceneManger.h"
#include "WSkillManager.h"

namespace W
{
	SkillSpeedUI::SkillSpeedUI()
	{

		SetPlayerSkill(Player::ePlayerSkill::speed);

		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillSpeedUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\speed\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillSpeedUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\speed\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillSpeedUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\2\\speed\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillSpeedMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillSpeedUI::~SkillSpeedUI()
	{

	}
	void SkillSpeedUI::Initialize()
	{

	}
	void SkillSpeedUI::Update()
	{
		SKill::Update();
	}
	void SkillSpeedUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillSpeedUI::Render()
	{
		SKill::Render();
	}
	void SkillSpeedUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillSpeedUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillSpeedMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillSpeedUI1"));
	}
	void SkillSpeedUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillSpeedMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillSpeedUI0"));
	}
	void SkillSpeedUI::MouseLbtnClicked()
	{

	}

	void SkillSpeedUI::Using()
	{
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::speed);
	}
}