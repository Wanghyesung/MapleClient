#include "WBlast.h"
#include "WAttackScript.h"
#include "WObject.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WEventManager.h"
namespace W
{
	Blast::Blast()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"BlastMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"blastTex"); 
		pAnim->Create(L"left", pAtlas, Vector2(0.0f, 0.0f), Vector2(695.0f, 506.0f), 23, Vector2(700.f, 700.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"right", pAtlas, Vector2(15290.0f, 0.0f), Vector2(-695.0f, 506.0f), 23, Vector2(700.f, 700.f), Vector2::Zero, 0.06f);

		pAnim->CompleteEvent(L"right") = std::bind(&EventManager::AddPlayerPool, this);
		pAnim->CompleteEvent(L"left") = std::bind(&EventManager::AddPlayerPool, this);

		SetHitSound(Resources::Find<AudioClip>(L"blasthit"), false);
	}
	Blast::~Blast()
	{

	}
	void Blast::Initialize()
	{
		AttackScript* pScript = AddComponent<AttackScript>();
		pScript->SetDir(m_iDir);
		pScript->SetStayObject(5, 0.5f);
		pScript->SetDeleteTime(20.f);

		GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.4f, 0.4f));
	}
	void Blast::Update()
	{
		GameObject::Update();
	}
	void Blast::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Blast::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = m_iDir * -1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Blast::Off()
	{
		PlayerAttackObject::Off();
	}
	void Blast::SetDir(int _iDir)
	{
		Animator* pAnim = GetComponent<Animator>();
		m_iDir = _iDir;
		if (m_iDir > 0)
			pAnim->Play(L"right", true);
		else
			pAnim->Play(L"left", true);

	}
	
}