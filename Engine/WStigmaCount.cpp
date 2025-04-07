#include "WStigmaCount.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
namespace W
{
	StigmaCount::StigmaCount()
	{
	
		std::shared_ptr<Texture> pTex = Resources::Load<Texture>(L"stigma1", L"..\\Resources\\Texture\\Monster\\demian\\1.png");
		pTex = Resources::Load<Texture>(L"stigma2", L"..\\Resources\\Texture\\Monster\\demian\\2.png");
		pTex = Resources::Load<Texture>(L"stigma3", L"..\\Resources\\Texture\\Monster\\demian\\3.png");
		pTex = Resources::Load<Texture>(L"stigma4", L"..\\Resources\\Texture\\Monster\\demian\\4.png");
		pTex = Resources::Load<Texture>(L"stigma5", L"..\\Resources\\Texture\\Monster\\demian\\5.png");
		pTex = Resources::Load<Texture>(L"stigma6", L"..\\Resources\\Texture\\Monster\\demian\\6.png");
		pTex = Resources::Load<Texture>(L"stigma7", L"..\\Resources\\Texture\\Monster\\demian\\7.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pMater->SetTexture(pTex);
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"stigmacount", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

	}
	StigmaCount::~StigmaCount()
	{

	}
	void StigmaCount::Initialize()
	{
		
	}
	void StigmaCount::Update()
	{
		GameObject::Update();
	}
	void StigmaCount::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void StigmaCount::Render()
	{
		GameObject::Render();
	}

}