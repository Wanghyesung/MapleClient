#include "WShadow.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WTime.h"
#include "WSceneManger.h"
namespace W
{
	Shadow::Shadow() :
		m_pOwner(nullptr),
		m_pFuncAttack(nullptr),
		m_fActiveTime(0.f),
		m_fCurTime(0.f),
		m_fAttackTime(0.f),
		m_fCurAttackTime(0.f),
		m_bActive(false),
		m_bOff(false),
		m_strCurAnim{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		
		Resources::Insert(L"Shadow_Mater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"shadowTex", L"..\\Resources\\Texture\\Player\\skill\\shadow\\shadow.png");
		Animator* pAnimator = AddComponent<Animator>();
		pAnimator->Create(L"_alert_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_jump_left", pAtlas, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_ladder_left", pAtlas, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_pronestab_left", pAtlas, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_proneattack_left", pAtlas, Vector2(150.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Create(L"_stab_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_stand_left", pAtlas, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swing1_left", pAtlas, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swing2_left", pAtlas, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swingOF_left", pAtlas, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_walk_left", pAtlas, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swingQS_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"_swingQS_left")->Create(L"_swingQS_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"_swingQS_left")->Create(L"_swingQS_left", pAtlas, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		pAnimator->Create(L"_alert_right", pAtlas, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_jump_right", pAtlas, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_ladder_right", pAtlas, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_pronestab_right", pAtlas, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_proneattack_right", pAtlas, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Create(L"_stab_right", pAtlas, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_stand_right", pAtlas, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swing1_right", pAtlas, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swing2_right", pAtlas, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swingOF_right", pAtlas, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_walk_right", pAtlas, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"_swingQS_right", pAtlas, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"_swingQS_right")->Create(L"_swingQS_right", pAtlas, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"_swingQS_right")->Create(L"_swingQS_right", pAtlas, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);

		pAnimator->Create(L"_dead", pAtlas, Vector2(150.0f, 1500.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);

		pAnimator->Play(L"_stand_left", true);
		pAnimator->CompleteEvent(L"_dead") = std::bind(&Shadow::off, this);
		GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 0.f));
	}

	Shadow::~Shadow()
	{

	}
	void Shadow::Initialize()
	{
		
	}

	void Shadow::Update()
	{
		if (!m_bActive)
			return;

		m_fCurTime += Time::DeltaTime();

		PlayerScript* pScript = m_pOwner->GetComponent<PlayerScript>();
		/*pScript->GetObjectInfo().fHP <= 0.f ||*/
		if (m_fCurTime >= m_fActiveTime)
		{
			m_bOff = true;
			m_pOwner->SetShadow(false);
		}
		
		if (m_pFuncAttack)
			update_attack();

		GameObject::Update();
	}

	void Shadow::LateUpdate()
	{
		if (!m_bActive)
			return;

		if (m_pOwner->IsAnimStop())
			GetComponent<Animator>()->Stop(true);
		else
			GetComponent<Animator>()->Stop(false);

		Animator* pAnimator = GetComponent<Animator>();
		Vector3 vPlayerPos = m_pOwner->GetComponent<Transform>()->GetPosition();

		int iDir = m_pOwner->GetDir();
		vPlayerPos.z += 0.01f;
		if (m_pOwner->GetCurPlayerState() == Player::ePlayerState::ladder)
			vPlayerPos.y -= 0.4f;
		else
			vPlayerPos.x -= iDir * 0.4f;
		GetComponent<Transform>()->SetPosition(vPlayerPos);
		
		std::wstring strDir;
		std::wstring strState;
		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";
		
		strState = m_pOwner->GetCurStateName();
		std::wstring strAnim = strState + strDir;
		if (m_bOff)
			strAnim = L"_dead";

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			bool bLoop = m_pOwner->IsLoop();
			pAnimator->Play(strAnim, bLoop);
		}

		GameObject::LateUpdate();
	}

	void Shadow::Render()
	{
		if (!m_bActive)
			return;

		renderer::ObjectCB ObjectCB;
		int iDir = m_pOwner->GetDir() * -1;
		if (m_bOff)
			iDir = 1;
		ObjectCB.vObjectDir.x = iDir;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Shadow::update_attack()
	{
		m_fCurAttackTime += Time::DeltaTime();
		if (m_fCurAttackTime >= m_fAttackTime)
		{
			m_fCurAttackTime = 0.f;
			m_pFuncAttack();
			m_pFuncAttack = nullptr;
		}
	}
	void Shadow::off()
	{
		m_fCurTime = 0.f;
		//SceneManger::Erase(this);
		m_bOff = false;
		m_bActive = false;
	}
}