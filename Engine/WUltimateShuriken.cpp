#include "WUltimateShuriken.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WCollider2D.h"
#include "WTime.h"
#include "WAttackScript.h"
#include "WRenderer.h"
namespace W
{
	UltimateShuriken::UltimateShuriken()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"UlitShurikenMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"UltiShuriken");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"shuriken", pTex, Vector2(0.f, 0.f), Vector2(581.f, 252.f), 6, Vector2(600.f, 600.f), Vector2(0.0f, 0.f), 0.1f);
		pAnim->Play(L"shuriken", true);

		mr->SetMaterial(pMater);

		AddComponent<Collider2D>();

		GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		Collider2D* pCOll = GetComponent<Collider2D>();
		pCOll->SetSize(Vector2(0.7f, 0.4f));

		AttackScript* pScript = AddComponent<AttackScript>();
		//pScript->SetDir(m_iDir);
		//최대 15명의 적 공격가능
		pScript->SetDeleteTime(7.f);
		pScript->SetAbleAttackCount(15);
		pScript->SetDeleteObject(false);

		SetHitSound(Resources::Find<AudioClip>(L"UltiShurikenHit"), false);

	}

	UltimateShuriken::~UltimateShuriken()
	{

	}
	void UltimateShuriken::Initialize()
	{
		GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		Collider2D* pCOll = GetComponent<Collider2D>();
		pCOll->SetSize(Vector2(0.7f, 0.4f));

		AttackScript* pScript = GetComponent<AttackScript>();
		//pScript->SetDir(m_iDir);
		//최대 15명의 적 공격가능
		pScript->SetStayObject(3, 0.3f);
	}
	void UltimateShuriken::Update()
	{
		Vector3 vPos = GetComponent<Transform>()->GetPosition();
		vPos.x += (Time::DeltaTime() * m_vDir.x * 9.f);
		vPos.y += (Time::DeltaTime() * m_vDir.y * 9.f);

		GetComponent<Transform>()->SetPosition(vPos);

		float fRadian = atan2f(m_vDir.y, m_vDir.x);
		if (m_vDir.x > 0.f)
			fRadian -= XM_2PI;
		else
			fRadian += XM_2PI;

		GetComponent<Transform>()->SetRotation(0.f, 0.f, fRadian);

		GameObject::Update();

	}
	void UltimateShuriken::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void UltimateShuriken::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void UltimateShuriken::SetStartPos(Vector2 _vPos)
	{
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, 0.f);

		Vector3 vTemPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector2 vCamPos = Vector2(vTemPos.x, vTemPos.y);

		vCamPos += (_vPos * 5.f);

		Vector3 vPosition = pTransform->GetPosition();
		pTransform->SetPosition(vCamPos.x, vCamPos.y,vPosition.z);

		Vector3 vPos = pTransform->GetPosition();
		vPos.z = 0.f;
		Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();
		vTargetPos.z = 0.f;

		Vector3 vDiff = vTargetPos - vPos;
		vDiff.Normalize();
		m_vDir = Vector2(vDiff.x,vDiff.y);
	}
}