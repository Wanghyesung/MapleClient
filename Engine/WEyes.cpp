#include "WEyes.h"
#include "WAnimator.h"
#include "WTexture.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WPlayerHead.h"
namespace W
{
	Eyes::Eyes():
		m_bAlert(false),
		m_iEyeNumber(0)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* pAnimator = AddComponent<Animator>();

		Resources::Load<Texture>(L"PlayerEyes2", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyes2.png");
		Resources::Load<Texture>(L"PlayerEyes1", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyes1.png");
		Resources::Load<Texture>(L"PlayerEyes0", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyes0.png");
		
		Resources::Load<Texture>(L"PlayerEyesHit2", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyesHit2.png");
		Resources::Load<Texture>(L"PlayerEyesHit1", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyesHit1.png");
		Resources::Load<Texture>(L"PlayerEyesHit0", L"..\\Resources\\Texture\\Player\\eyes\\PlayerEyesHit0.png");

	}

	Eyes::~Eyes()
	{

	}
	
	void Eyes::Initialize()
	{
		std::wstring strNum = std::to_wstring(m_iEyeNumber);

		Animator* pAnimator = GetComponent<Animator>();
		std::shared_ptr<Texture> pAtlasBdoy = Resources::Find<Texture>(L"PlayerEyes" + strNum);
		
		pAnimator->Create(L"eye_alert_left" + strNum, pAtlasBdoy, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_jump_left" + strNum, pAtlasBdoy, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_ladder_left" + strNum, pAtlasBdoy, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_pronestab_left" + strNum, pAtlasBdoy, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_proneattack_left" + strNum, pAtlasBdoy, Vector2(150.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_stab_left" + strNum, pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_stand_left" + strNum, pAtlasBdoy, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swing1_left" + strNum, pAtlasBdoy, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swing2_left" + strNum, pAtlasBdoy, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swingOF_left" + strNum, pAtlasBdoy, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_walk_left" + strNum, pAtlasBdoy, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swingQS_left" + strNum, pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eye_swingQS_left" + strNum)->Create(L"eye_swingQS_left" + strNum, pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eye_swingQS_left" + strNum)->Create(L"eye_swingQS_left" + strNum, pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		pAnimator->Create(L"eye_alert_right" + strNum, pAtlasBdoy, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_jump_right" + strNum, pAtlasBdoy, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_ladder_right" + strNum, pAtlasBdoy, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_pronestab_right" + strNum, pAtlasBdoy, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_proneattack_right" + strNum, pAtlasBdoy, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_stab_right" + strNum, pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_stand_right" + strNum, pAtlasBdoy, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swing1_right" + strNum, pAtlasBdoy, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swing2_right" + strNum, pAtlasBdoy, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swingOF_right" + strNum, pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_walk_right" + strNum, pAtlasBdoy, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eye_swingQS_right" + strNum, pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eye_swingQS_right" + strNum)->Create(L"eye_swingQS_right" + strNum, pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eye_swingQS_right" + strNum)->Create(L"eye_swingQS_right" + strNum, pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"PlayerEyesHit" +strNum);
		pAnimator->Create(L"eyealert_alert_left" + strNum, pAtlas, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_jump_left" + strNum, pAtlas, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_ladder_left" + strNum, pAtlas, Vector2(0.0f, 300.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_pronestab_left" + strNum, pAtlas, Vector2(0.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_proneattack_left" + strNum, pAtlas, Vector2(150.0f, 450.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_stab_left" + strNum, pAtlas, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_stand_left" + strNum, pAtlas, Vector2(0.0f, 750.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swing1_left" + strNum, pAtlas, Vector2(0.0f, 900.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swing2_left" + strNum, pAtlas, Vector2(0.0f, 1050.0f), Vector2(150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swingOF_left"+ strNum, pAtlas, Vector2(0.0f, 1200.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_walk_left" + strNum, pAtlas, Vector2(0.0f, 1350.0f), Vector2(150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swingQS_left" + strNum, pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eyealert_swingQS_left" + strNum)->Create(L"eyealert_swingQS_left" + strNum, pAtlasBdoy, Vector2(0.0f, 600.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eyealert_swingQS_left" + strNum)->Create(L"eyealert_swingQS_left" + strNum, pAtlasBdoy, Vector2(450.0f, 1200.0f), Vector2(150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		pAnimator->Create(L"eyealert_alert_right" + strNum, pAtlas, Vector2(450.0f, 0.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_jump_right" + strNum, pAtlas, Vector2(450.0f, 150.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_ladder_right" + strNum, pAtlas, Vector2(450.0f, 300.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_pronestab_right" + strNum, pAtlas, Vector2(450.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_proneattack_right" + strNum, pAtlas, Vector2(300.0f, 450.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_stab_right" + strNum, pAtlas, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_stand_right" + strNum, pAtlas, Vector2(450.0f, 750.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swing1_right" + strNum, pAtlas, Vector2(450.0f, 900.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swing2_right" + strNum, pAtlas, Vector2(450.0f, 1050.0f), Vector2(-150.0f, 150.0f), 3, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swingOF_right" + strNum, pAtlas, Vector2(450.0f, 1200.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_walk_right" + strNum, pAtlas, Vector2(450.0f, 1350.0f), Vector2(-150.0f, 150.0f), 4, Vector2(120.f, 120.f), Vector2::Zero, 0.18f);
		pAnimator->Create(L"eyealert_swingQS_right" + strNum, pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 2, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eyealert_swingQS_right" + strNum)->Create(L"eyealert_swingQS_right" + strNum, pAtlasBdoy, Vector2(450.0f, 600.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);
		pAnimator->FindAnimation(L"eyealert_swingQS_right" + strNum)->Create(L"eyealert_swingQS_right" + strNum, pAtlasBdoy, Vector2(0, 1200.0f), Vector2(-150.0f, 150.0f), 1, Vector2(120.f, 120.f), Vector2::Zero, 0.14f);


		Vector3 vScale = m_pPlayerHead->GetComponent<Transform>()->GetScale();
		GetComponent<Transform>()->SetScale(vScale);
	}
	void Eyes::Update()
	{
		GameObject::Update();
	}
	void Eyes::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();
		Vector3 vPlayerPos = m_pPlayerHead->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPlayerPos);

		Player* pPlayer = m_pPlayerHead->GetPlayer();

		int iDir = pPlayer->GetDir();
		std::wstring strDir;
		std::wstring strState;
		std::wstring strEye = L"eye";
		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		strState = pPlayer->GetCurStateName();

		if (m_bAlert)
			strEye += L"alert";

		std::wstring strNum = std::to_wstring(m_iEyeNumber);

		std::wstring strAnim = strEye + strState + strDir + strNum;

		if (m_strCurAnim != strAnim)
		{
			Animation* pAnim = m_pPlayerHead->GetComponent<Animator>()->GetActiveAnimation();

			m_strCurAnim = strAnim;
			bool bLoop = pPlayer->IsLoop();
			pAnimator->Play(strAnim, bLoop);

			pAnimator->GetActiveAnimation()->SetIndex(pAnim->GetCurIndex(), pAnim->GetCurTime());
		}

		GameObject::LateUpdate();
	}
	void Eyes::Render()
	{
		GameObject::Render();
	}

	void Eyes::SetEye(UINT _iNum)
	{
		m_iEyeNumber = _iNum;
		Initialize();
	}
}