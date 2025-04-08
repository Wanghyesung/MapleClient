#include "WJenesis.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"
#include "WMonster.h"
namespace W
{
	Jenesis::Jenesis()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"ArielJenesisStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"PinkBean_attack0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"attack0", pAtlas, Vector2(0.0f, 0.0f), Vector2(844.f, 820.0f), 11, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0")->Create(L"attack0", pAtlas, Vector2(0.0f, 820.0f), Vector2(844.f, 820.0f), 11, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"attack0", true);

	}
	Jenesis::~Jenesis()
	{

	}
	void Jenesis::Initialize()
	{
	}
	void Jenesis::Update()
	{
		
	}
	void Jenesis::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Jenesis::Render()
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