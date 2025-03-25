#include "WSleepGas.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonsterAttackScript.h"
#include "WTime.h"
#include "WRenderer.h"
namespace W
{
	SleepGas::SleepGas() :
		m_strCurAnim(L""),
		m_bStart(false),
		m_bEnd(false)
	{
		GetComponent<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stop);
		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

		MeshRenderer* mr = GetComponent<MeshRenderer>();
	

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MagnusStoneMater", pMater);

		//25
		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"sleepGas");
		pAnim->Create(L"sleepGas_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(135.0f, 210.0f), 25, Vector2(450.f, 450.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sleepGas_end", pAtlas, Vector2(0.0f, 210.f), Vector2(420.0f, 271.0f), 6, Vector2(450.f, 450.f), Vector2::Zero, 0.12f);

		pAnim->CompleteEvent(L"sleepGas_start") = std::bind(&SleepGas::end, this);
		pAnim->CompleteEvent(L"sleepGas_end") = std::bind(&SleepGas::off, this);

		mr->SetMaterial(pMater);
	}

	SleepGas::~SleepGas()
	{

	}
	void SleepGas::Initialize()
	{
		m_tMonsterAttack.bSkill = true;
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 20.f;
		m_tMonsterAttack.tAttackInfo.fAttUpperRcnt = 0.f;
		m_tMonsterAttack.tAttackInfo.fAttRcnt = 1.f;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.7f, 0.5f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);
	}
	void SleepGas::Update()
	{
		GameObject::Update();
	}
	void SleepGas::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"_start";;

		if (m_bEnd)
			strState = L"_end";

		std::wstring strAnim = L"sleepGas" + strState;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
		}

		GameObject::LateUpdate();
	}
	void SleepGas::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void SleepGas::end()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y -= 0.1f;
		GetComponent<Transform>()->SetPosition(vPosition);

		m_bEnd = true;

		Initialize();
		SetMonsterAttack(m_tMonsterAttack);
	}
	void SleepGas::start()
	{
		m_bStart = true;

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y += 0.1f;
		GetComponent<Transform>()->SetPosition(vPosition);

		GetComponent<Collider2D>()->SetActive(false);
		MonsterAttackScript* pScript = GetScript<MonsterAttackScript>();
		pScript->InitStack();

		SetState(GameObject::eState::Active);
	}
	void SleepGas::off()
	{
		m_bStart = false;
		m_bEnd = false;

		GetComponent<MonsterAttackScript>()->InitStack();
		SetState(GameObject::eState::Paused);
	}
}