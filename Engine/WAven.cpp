#include "WAven.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WAttackScript.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WEventManager.h"
namespace W
{
	Aven::Aven() :
		m_iDir(1)
	{
		//SetName(L"Aven");

		GetComponent<Transform>()->SetScale(2.f * 0.72, 2.f * 0.72, 0.f);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//¿©±â ¹Ù²ñ
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"AvenMater", pMater);

		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"avenTex", L"..\\Resources\\Texture\\Player\\skill\\ball.png");
		pMater->SetTexture(pAtlas);
		mr->SetMaterial(pMater);

	}

	Aven::~Aven()
	{

	}

	void Aven::Initialize()
	{
		AttackScript* pScript = AddComponent<AttackScript>();
		pScript->SetStayObject(1, 10.f);

		Collider2D* pCollider = AddComponent<Collider2D>();
		GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);
		pCollider->SetSize(Vector2(0.5f, 0.5f));

	}

	void Aven::Update()
	{
		GameObject::Update();

		Vector3 vRotation = GetComponent<Transform>()->GetRotation();
		vRotation.z += XM_PI  * Time::DeltaTime() * 6;
		GetComponent<Transform>()->SetRotation(vRotation);
	}

	void Aven::LateUpdate()
	{
		Transform* pTr = GetComponent<Transform>();
		Vector3 vPosition = pTr->GetPosition();
		vPosition.x += (m_iDir * 8.f * Time::DeltaTime());
		pTr->SetPosition(vPosition);

		GameObject::LateUpdate();
	}

	void Aven::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vColor = Vector4::One;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Aven::Off()
	{
		PlayerAttackObject::Off();
		//EventManager::AddPlayerPool(this);
	}
}