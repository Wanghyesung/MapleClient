#include "WConfusion.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WPlayer.h"
#include "WInput.h"

namespace W
{
	Confusion::Confusion()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		
		Resources::Insert(L"ConfusionMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"confusionTex", L"..\\Resources\\Texture\\Abnormal\\confusion.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"confusion", pAtlas, Vector2(0.0f, 0.0f), Vector2(29.0f, 46.0f), 5, Vector2(40.f, 40.f), Vector2::Zero, 0.15f);


	}
	Confusion::~Confusion()
	{

	}
	void Confusion::Initialize()
	{

	}
	void Confusion::Update()
	{
		
	}
	void Confusion::LateUpdate()
	{
		Abnormal::LateUpdate();
	}
	void Confusion::Render()
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
}