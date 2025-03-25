#include "WLoad.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WObject.h"
#include "WTime.h"
#include "WAutoShuriken.h"
#include "WEventManager.h"
#include "WRenderer.h"
#include "WPlayerScript.h"
#include "WAttackScript.h"
namespace W
{
	Load::Load():
		m_fEndTime(10.f),
		m_fCurEndTime(0.f),
		m_fCurRespawnTime(0.f),
		m_fRespawnTime(2.f),
		m_bEnd(false)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"loadMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"loadTex");
		pAnim->Create(L"active", pAtlas, Vector2(0.0f, 0.0f), Vector2(1700.0f, 1200.0f), 5, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"active")->Create(L"active",pAtlas, Vector2(0.0f, 1200.0f), Vector2(1700.0f, 1200.0f), 5, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);

		pAnim->Create(L"end", pAtlas, Vector2(0.0f, 2400.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.01f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 3600.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 4800.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 6000.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"end") = std::bind(&PlayerAttackObject::PushObjectPool, this);

		//test
		pAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);

		SetSound(L"loop", Resources::Find<AudioClip>(L"load_loop"), true);
		SetSound(L"dead", Resources::Find<AudioClip>(L"load_dead"), false);
		SetHitSound(Resources::Find<AudioClip>(L"load_hit"), false);
	}
	Load::~Load()
	{

	}
	void Load::Initialize()
	{
		init_skill();
	}
	void Load::Update()
	{
		if (!m_bEnd)
		{
			m_fCurRespawnTime += Time::DeltaTime();
			m_fCurEndTime += Time::DeltaTime();

			if (m_fCurEndTime >= m_fEndTime)
				end();

			if (m_fCurRespawnTime >= m_fRespawnTime)
			{
				m_fCurRespawnTime = 0.f;
				create_shuriken();
			}
		}
	
		GameObject::Update();
	}
	void Load::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Load::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Load::Off()
	{
		m_fEndTime = 10.f;
		m_fCurEndTime = 0.f;
		m_fCurRespawnTime = 0.f;
		m_fRespawnTime = 2.f;
		m_bEnd = false;

		PlayerAttackObject::Off();
	}

	void Load::Start()
	{
		GetScript<AttackScript>()->SetDeleteObject(false);
		GetComponent<Animator>()->Play(L"active", true);

		StartSound(L"loop");
	}

	void Load::end()
	{
		m_bEnd = true;
		GetComponent<Animator>()->Play(L"end", true);

		GetComponent<Collider2D>()->SetActive(true);

		StartSound(L"dead");
	}

	void Load::create_shuriken()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		
		Vector3 vLook[5] = { Vector3{1,0,0}, Vector3{0.5f,0.5f,0} , Vector3{0,1.f,0},
			Vector3{-0.5f,0.5f,0},Vector3{-1.f,0,0} };

		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 5; ++i)
		{
			PlayerAttackObject* pAttackObj = pScript->GetPlayerSkill(L"autoSuriken");
			AutoShuriken* pShuriken = dynamic_cast<AutoShuriken*>(pAttackObj);

			pShuriken->SetDir(Vector2(vLook[i].x, vLook[i].y));

			Transform* pTr = pShuriken->GetComponent<Transform>();

			Vector3 vFinalPos = vPosition + vLook[i];
			pTr->SetPosition(vFinalPos);
			
			//////
			pShuriken->SetVelocity(Vector2(vLook[i]));
			EventManager::CreateObject(pShuriken, eLayerType::AttackObject);
		}
	}
	void Load::init_skill()
	{
		//GetComponent<Animator>()->Binds();
		Collider2D* pCollider = AddComponent<Collider2D>();
		//pCollider->SetSize(Vector2(6.f, 6.f));
		pCollider->SetActive(false);

		const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 1.f;
		AttackInfo.fAttack = Attack.fAttack;
		AttackInfo.fDex = Attack.fDex;

		AttackInfo.fAttRcnt = 0.3f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;

		AttackInfo.iDamageCount = 10;

		//12명 공격가능, 10번공격, 20초뒤 삭제, 이동 X 
		AddComponent<AttackScript>()->SetStayObject(AttackInfo.iDamageCount, 2.f);
		GetComponent<AttackScript>()->SetDeleteTime(20.f);
		GetComponent<AttackScript>()->SetAbleAttackCount(12);

		GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
	}
}