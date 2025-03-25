#include "WVariation.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WRigidbody.h"
#include "WPlayer.h"
#include "WObject.h"
namespace W
{
	Variation::Variation()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"VariationMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"variationTex", L"..\\Resources\\Texture\\Abnormal\\variation.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"variation", pAtlas, Vector2(0.0f, 0.0f), Vector2(128.0f, 123.0f), 7, Vector2(130.f, 130.f), Vector2::Zero, 0.12f);
		pAnim->CompleteEvent(L"variation") = std::bind(&Variation::off, this);
		pAnim->Play(L"variation", true);

		GetComponent<Transform>()->SetScale(Vector3(1.7f, 1.7f, 0.f));
	}
	Variation::~Variation()
	{

	}
	void Variation::Initialize()
	{

	}
	void Variation::Update()
	{
		Abnormal::Update();
	}
	void Variation::LateUpdate()
	{
		Abnormal::LateUpdate();
	}
	void Variation::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		Abnormal::Render();
	}

	void Variation::off()
	{
		object::Destroy(this);
	}


}