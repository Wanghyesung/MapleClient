#include "WMegnusStone.h"
#include "WMonsterAttackScript.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRigidbody.h"
#include "WCollider2D.h"
#include "WRenderer.h"
#include "WBattleManager.h"
#include "WMonster.h"
#include "WSceneManger.h"
namespace W
{
	MegnusStone::MegnusStone() :
		m_bMove(false),
		m_bEnd(false),
		m_strCurAnim{}
	{
		AddComponent<Rigidbody>();
		AddComponent<Collider2D>()->SetActive(false);

		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"MagnusStoneMater");
		if (pMater == nullptr)
		{
			pMater = std::make_shared<Material>();
			pMater->SetRenderinMode(eRenderingMode::Transparent);
			pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
			Resources::Insert(L"MagnusStoneMater", pMater);
		}

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"magnus_stone");
		pAnim->Create(L"stone_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(350.0f, 350.0f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_move", pAtlas, Vector2(0.0f, 350.0f), Vector2(350.0f, 350.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_end", pAtlas, Vector2(0.0f, 700.f), Vector2(350.0f, 350.0f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"stone_start") = std::bind(&MegnusStone::start, this);
		pAnim->CompleteEvent(L"stone_end") = std::bind(&MegnusStone::off, this);

		mr->SetMaterial(pMater);
	}
	MegnusStone::~MegnusStone()
	{

	}
	void MegnusStone::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.12f, 0.12f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);
	}
	void MegnusStone::Update()
	{
		if (m_bMove)
			move();

		if (!m_bEnd)
		{
			m_bEnd = GetScript<MonsterAttackScript>()->IsEnter();

			if (m_bEnd)
				m_bMove = false;
		}

		GameObject::Update();
	}
	void MegnusStone::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"_start";

		if (m_bEnd)
			strState = L"_end";

		else if (m_bMove)
			strState = L"_move";


		std::wstring strAnim = L"stone" + strState;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
		}

		GameObject::LateUpdate();
	}
	void MegnusStone::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void MegnusStone::move()
	{
		Rigidbody* pRigidbody = GetComponent<Rigidbody>();
		pRigidbody->AddForce(Vector2(0.f, -1.8f));
	}
	void MegnusStone::start()
	{
		m_bMove = true;
		SetMonsterAttack(m_tMonsterAttack);
	}
	void MegnusStone::off()
	{
		m_bMove = false;
		m_bEnd = false;
		GetScript<MonsterAttackScript>()->SetEnter(false);
		GetScript<MonsterAttackScript>()->InitStack();
		
		EventManager::AddMonsterPool(this);
	}
}