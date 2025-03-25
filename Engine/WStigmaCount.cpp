#include "WStigmaCount.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
namespace W
{
	StigmaCount::StigmaCount():
		m_iNumber(0),
		m_pOwner(nullptr)
	{
		GetComponent<Transform>()->SetScale(0.14f * 1.4f, 0.16f * 1.4f, 0.f);

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
		if (m_iNumber == 0)
			return;

		Vector3 vPosition =
			m_pOwner->GetComponent<Transform>()->GetPosition();
		vPosition.z = -2.2f;
		vPosition.x -= 0.04f;
		vPosition.y -= 0.02f;

		GetComponent<Transform>()->SetPosition(vPosition);

		GameObject::Update();
	}
	void StigmaCount::LateUpdate()
	{
		if (m_iNumber == 0)
			return;
		GameObject::LateUpdate();
	}
	void StigmaCount::Render()
	{
		if (m_iNumber == 0)
			return;
		
		GameObject::Render();
	}
	void StigmaCount::set_count(UINT _iCount)
	{
		if (_iCount>7)
			return;

		m_iNumber = _iCount;
		std::wstring strNum =std::to_wstring(m_iNumber);
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Resources::Find<Texture>(L"stigma" + strNum));

	}
}