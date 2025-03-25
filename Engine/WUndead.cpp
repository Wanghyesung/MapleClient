#include "WUndead.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	Undead::Undead()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"UndeadMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"UndeadTex", L"..\\Resources\\Texture\\Abnormal\\undead.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"undead", pAtlas, Vector2(0.0f, 0.0f), Vector2(43.0f, 46.0f), 10, Vector2(70.f, 70.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"undead", true);

		//m_eType = BattleManager::eAbnormalType::Undead;

	}
	Undead::~Undead()
	{
	}
	void Undead::Initialize()
	{
	}
	void Undead::Update()
	{
		Abnormal::Update();
	}
	void Undead::LateUpdate()
	{
		Abnormal::LateUpdate();

	}
	void Undead::Render()
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
	void Undead::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::Undead);

		//BattleManager::Restore_move(m_pTarget, BattleManager::eAbnormalType::Undead);
	}
}