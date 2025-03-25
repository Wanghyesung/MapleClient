#include "WTemptation.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WRigidbody.h"
#include "WPlayer.h"
#include "WBattleManager.h"
#include "WEventManager.h"
namespace W
{
	Temptation::Temptation()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"TemptationMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"temptationTex", L"..\\Resources\\Texture\\Abnormal\\temptation.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"temptation", pAtlas, Vector2(0.0f, 0.0f), Vector2(50.0f, 63.0f), 8, Vector2(80.f, 80.f), Vector2::Zero, 0.2f);

		pAnim->Play(L"temptation", true);

		//GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 0.f));
	}
	Temptation::~Temptation()
	{

	}
	void Temptation::Initialize()
	{

	}
	void Temptation::Update()
	{
		Rigidbody* pRigidbody = m_pTarget->GetComponent<Rigidbody>();
		int iDir = m_pTarget->GetDir();

		bool bGround = pRigidbody->IsGround();
		if (bGround)
		{
			pRigidbody->SetVelocity(Vector2(iDir * 1.5f, 3.5f));
			pRigidbody->SetGround(false);
		}
		else
			pRigidbody->AddForce(Vector2(1.5f * iDir, 0.f));

		Abnormal::Update();
	}
	void Temptation::LateUpdate()
	{
		Abnormal::LateUpdate();
	}
	void Temptation::Render()
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

	void Temptation::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::temptation);

		//BattleManager::Restore_move(m_pTarget, BattleManager::eAbnormalType::temptation);
	}

	
}