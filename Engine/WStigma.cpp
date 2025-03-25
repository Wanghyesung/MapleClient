#include "WStigma.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEventManager.h"
#include "WObject.h"
namespace W
{
	Stigma::Stigma()
	{
		GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StigamMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Stigma");
		pAnim->Create(L"start", pAtlas, Vector2(0.0f, 0.0f), Vector2(189.0f, 187.0f), 7, Vector2(200.f, 200.f), Vector2::Zero, 0.12f);
		
		pAnim->CompleteEvent(L"start") = std::bind(&Stigma::Restore, this);
		//pAnim->CompleteEvent(L"stone_end") = std::bind(&MegnusStone::off, this);
		mr->SetMaterial(pMater);
		pAnim->Play(L"start", true);
	}
	Stigma::~Stigma()
	{

	}
	void Stigma::Initialize()
	{

	}
	void Stigma::Update()
	{
		GameObject::Update();
	}

	void Stigma::LateUpdate()
	{
		Abnormal::LateUpdate();

		Vector3 vTargetPos = GetComponent<Transform>()->GetPosition();
		vTargetPos.y -= 0.5f;
		GetComponent<Transform>()->SetPosition(vTargetPos);
	}

	void Stigma::Render()
	{
		GameObject::Render();
	}
	void Stigma::Restore()
	{
		object::Destroy(this);
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::Stigma);
		//BattleManager::Restore_move(m_pTarget, BattleManager::eAbnormalType::SealSkill);
	}
}