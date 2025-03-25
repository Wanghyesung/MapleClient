#include "WSkillWindUI.h"
#include "WSkillManager.h"

namespace W
{
	SkillWindUI::SkillWindUI()
	{
		SetPlayerSkill(Player::ePlayerSkill::wind);
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillWindUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\wind\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillWindUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\wind\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillWindUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\5\\wind\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillWindMater", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}

	SkillWindUI::~SkillWindUI()
	{

	}
	void SkillWindUI::Initialize()
	{

	}
	void SkillWindUI::Update()
	{
		SKill::Update();
	}
	void SkillWindUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillWindUI::Render()
	{
		SKill::Render();
	}
	void SkillWindUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillWindUI::MouseLbtnDown()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnDown();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillWindMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillWindUI1"));
	}
	void SkillWindUI::MouseLbtnUp()
	{
		bool bClone = IsClone();
		if (bClone)
			return;

		SKill::MouseLbtnUp();

		std::shared_ptr<Material> pShMater = Resources::Find<Material>(L"SKillWindMater");
		pShMater->SetTexture(Resources::Find<Texture>(L"SKillWindUI0"));
	}

	void SkillWindUI::MouseLbtnClicked()
	{

	}

	void SkillWindUI::Using()
	{
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::wind);
	}
}