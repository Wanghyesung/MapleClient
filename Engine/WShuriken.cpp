#include "WShuriken.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WAttackScript.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WEventManager.h"
namespace W
{
	UINT Shuriken::COUNT = 0;

	Shuriken::Shuriken():
		m_iDir(1)
	{
		m_iCount = COUNT;
		++COUNT;

		//std::wstring strNum = std::to_wstring(m_iCount);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//여기 바뀜
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		Resources::Insert(L"shurikenMater", pMater);

		mr->SetMaterial(pMater);

		Animator* pAnimator = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"shurikenTex", L"..\\Resources\\Texture\\Player\\shuriken\\shuriken.png");
		pAnimator->Create(L"shuriken_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(48.0f, 9.f), 2, Vector2(100.f, 100.f), Vector2::Zero, 0.1f);
		pAnimator->Create(L"shuriken_right", pAtlas, Vector2(48.0f, 0.0f), Vector2(-48.0f, 9.f), 2, Vector2(100.f, 100.f), Vector2::Zero, 0.1f);
	}

	Shuriken::~Shuriken()
	{

	}

	void Shuriken::Initialize()
	{
		AddComponent<AttackScript>();

		Collider2D* pCollider = AddComponent<Collider2D>();
		GetComponent<Transform>()->SetScale(1.f, 1.f, 0.f);
		pCollider->SetSize(Vector2(0.5f, 0.5f));

	}

	//이동, 삭제시간, attackscript말고 각각의 클래스에서
	void Shuriken::Update()
	{	
		GameObject::Update();
	}

	void Shuriken::LateUpdate()
	{
		Transform* pTr =GetComponent<Transform>();
		Vector3 vPosition = pTr->GetPosition();
		vPosition.x += (m_iDir * 8.f * Time::DeltaTime());
		pTr->SetPosition(vPosition);

		GameObject::LateUpdate();
	}

	void Shuriken::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vDir.x = m_iDir * -1;
		PlayerCB.vColor = Vector4::One;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Shuriken::SetDir(int _iDir)
	{
		m_iDir = _iDir;
		AttackScript* pScript = GetScript<AttackScript>();
		pScript->SetDir(m_iDir);

		Animator* pAnimator = GetComponent<Animator>();
		std::wstring strDir;
		if (m_iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";
		pAnimator->Play(L"shuriken" + strDir, true);
	}
	void Shuriken::Off()
	{
		PlayerAttackObject::Off();
	}
}