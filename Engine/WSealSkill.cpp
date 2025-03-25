#include "WSealSkill.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WRigidbody.h"
#include "WPlayer.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	SealSkill::SealSkill()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"SealSkillMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"sealskillTex", L"..\\Resources\\Texture\\Abnormal\\sealskill.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"sealskill", pAtlas, Vector2(0.0f, 0.0f), Vector2(73.0f, 47.0f), 10, Vector2(80.f, 80.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"sealskill", true);

		//GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 0.f));
	}
	SealSkill::~SealSkill()
	{

	}
	void SealSkill::Initialize()
	{

	}
	void SealSkill::Update()
	{
		Abnormal::Update();
	}
	void SealSkill::LateUpdate()
	{
		Abnormal::LateUpdate();
	}
	void SealSkill::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		Abnormal::Render();
	}

	void SealSkill::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::SealSkill);
		//BattleManager::Restore_move(m_pTarget, BattleManager::eAbnormalType::SealSkill);
	}


}