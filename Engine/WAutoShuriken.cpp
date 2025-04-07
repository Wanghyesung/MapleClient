#include "WAutoShuriken.h"
#include "WSceneManger.h"
#include "WLayer.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	AutoShuriken::AutoShuriken():
		m_iDir(1)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//¿©±â ¹Ù²ñ
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		Resources::Insert(L"shurikenMater", pMater);

		mr->SetMaterial(pMater);


	}

	AutoShuriken::~AutoShuriken()
	{

	}

	void AutoShuriken::Initialize()
	{
		
	}

	void AutoShuriken::Update()
	{
		
	}
	void AutoShuriken::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AutoShuriken::Render()
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