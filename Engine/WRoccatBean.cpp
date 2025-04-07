#include "WRoccatBean.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	RoccatBean::RoccatBean() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"RoccatBeanStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"PinkBean_attack3");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"attack3", pAtlas, Vector2(0.0f, 0.0f), Vector2(109.f, 159.0f), 6, Vector2(150.f, 150.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"attack3", true);

	}

	RoccatBean::~RoccatBean()
	{

	}
	void RoccatBean::Initialize()
	{
		
	}
	void RoccatBean::Update()
	{
	}
	void RoccatBean::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void RoccatBean::Render()
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
	
}