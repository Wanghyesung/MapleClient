#include "WWind.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAttackScript.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WObject.h"
#include "WEventManager.h"
namespace W
{
	Wind::Wind():
		m_fResetTime(0.6f),
		m_fCurResetTime(0.f),
		m_fFinishTime(4.f),
		m_fCurFinishTime(0.f),
		m_fStopTime(2.f),
		m_fCurStopTime(0.f),
		m_bFinish(false),
		m_bStop(false),
		m_strCurAnim{}
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"WindMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"windTex"); 
		pAnim->Create(L"move_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"stop_left", pAtlas, Vector2(0.0f, 316.0f), Vector2(460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"finish_left", pAtlas, Vector2(0.0f, 776.0f), Vector2(612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		
		pAnim->Create(L"move_right", pAtlas, Vector2(10614.f, 0.0f), Vector2(-402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"stop_right", pAtlas, Vector2(10556.f, 316.0f), Vector2(-460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"finish_right", pAtlas, Vector2(10404.f, 776.0f), Vector2(-612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);

		pAnim->CompleteEvent(L"finish_left") = std::bind(&PlayerAttackObject::PushObjectPool, this);
		pAnim->CompleteEvent(L"finish_right") = std::bind(&PlayerAttackObject::PushObjectPool, this);

		mr->SetMaterial(pMater);

		SetSound(L"move", Resources::Find<AudioClip>(L"wind_move"),true);
		SetSound(L"finish", Resources::Find<AudioClip>(L"wind_finish"), false);
		//SetSound(L"stop", Resources::Find<AudioClip>(L"wind_stop"), true);
		SetHitSound(Resources::Find<AudioClip>(L"wind_hit"), false);
	}
	Wind::~Wind()
	{

	}
	void Wind::Initialize()
	{
		AttackScript* pScript = AddComponent<AttackScript>();
		pScript->SetDir(m_iDir);
		pScript->SetStayObject(5, m_fResetTime);
		pScript->SetDeleteTime(10.f);

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.7f, 0.7f));
	}
	void Wind::Update()
	{
		m_fCurResetTime += Time::DeltaTime();
		m_fCurFinishTime += Time::DeltaTime();
		m_fCurStopTime += Time::DeltaTime();

		if (m_fCurResetTime >= m_fResetTime)
		{
			m_fCurResetTime = 0.f;
			GetScript< AttackScript>()->ResetAttackCount();
		}

		else if (!m_bStop && !m_bFinish &&
			m_fCurStopTime >= m_fStopTime)
		{
			m_fCurStopTime = 0.f;
			m_bStop = true;
		}

		else if (!m_bFinish && m_fCurFinishTime >= m_fFinishTime)
		{
			m_fFinishTime = 0.f;
			m_bStop = false;
			m_bFinish = true;
		}

		GameObject::Update();
	}

	void Wind::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		if (!m_bStop && !m_bFinish)
		{
			Vector3 vPos = GetComponent<Transform>()->GetPosition();
			vPos.x += (2.f * Time::DeltaTime() * m_iDir);
			GetComponent<Transform>()->SetPosition(vPos);
		}
		
		std::wstring strDir;
		std::wstring strState = L"move";
		if (m_iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		if(m_bStop)
			strState = L"stop";
		else if(m_bFinish)
			strState = L"finish";

		std::wstring strAnim = strState + strDir;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
			
			StartSound(strState);
		}

		GameObject::LateUpdate();
	}
	void Wind::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = m_iDir * -1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
	
		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Wind::Off()
	{
		m_fResetTime = 0.6f;
		m_fCurResetTime = 0.f;
		m_fFinishTime= 4.f;
		m_fCurFinishTime = 0.f; 
		m_fStopTime = 2.f;
		m_fCurStopTime = 0.f;
		m_bFinish = false;
		m_bStop = false;
		m_strCurAnim = {};

		PlayerAttackObject::Off();
	}
	
}