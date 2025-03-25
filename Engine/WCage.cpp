#include "WCage.h"
#include "WResources.h"

namespace W
{
	Cage::Cage()
	{
		std::shared_ptr<Texture> pCage =
			Resources::Load<Texture>(L"CageTex", L"..\\Resources\\Texture\\NPC\\cage.png");

		std::shared_ptr<Material> pCageMater = std::make_shared<Material>();
		pCageMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pCageMater->SetTexture(pCage);
		Resources::Insert(L"CageMater", pCageMater);
	
		MeshRenderer* pNPCRenderer = AddComponent<MeshRenderer>();
		pNPCRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pNPCRenderer->SetMaterial(pCageMater);


	}
	Cage::~Cage()
	{
	
	}
	void Cage::Initialize()
	{


	}
	void Cage::Update()
	{
		GameObject::Update();

	}
	void Cage::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Cage::Render()
	{
		GameObject::Render();
	}
}