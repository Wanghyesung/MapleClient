#include "WStigma.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEventManager.h"
#include "WObject.h"
namespace W
{
	Stigma::Stigma()
	{
		GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StigamMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Stigma");
		pAnim->Create(L"start", pAtlas, Vector2(0.0f, 0.0f), Vector2(189.0f, 187.0f), 7, Vector2(200.f, 200.f), Vector2::Zero, 0.12f);
		
		mr->SetMaterial(pMater);
		pAnim->Play(L"start", true);
	}
	Stigma::~Stigma()
	{

	}
	void Stigma::Initialize()
	{

	}
	void Stigma::Update()
	{
		
	}

	void Stigma::LateUpdate()
	{
		Abnormal::LateUpdate();
	}

	void Stigma::Render()
	{
		GameObject::Render();
	}
	
}