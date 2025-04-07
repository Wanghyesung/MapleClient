#include "WShuriken.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WEventManager.h"
namespace W
{

	Shuriken::Shuriken()
	{
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
	
	}

	//이동, 삭제시간, attackscript말고 각각의 클래스에서
	void Shuriken::Update()
	{	
		
	}

	void Shuriken::LateUpdate()
	{
		
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
	
}