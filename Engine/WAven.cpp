#include "WAven.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WTransform.h"
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

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"avenTex");
		pMater->SetTexture(pAtlas);
		mr->SetMaterial(pMater);

		//Resources::Load<Texture>(L"aveneffect", L"..\\Resources\\Texture\\Player\\skill\\effect4.png");
	


	}

	Aven::~Aven()
	{

	}

	void Aven::Initialize()
	{
	
	}

	void Aven::Update()
	{
		
	}

	void Aven::LateUpdate()
	{
		
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
	
}