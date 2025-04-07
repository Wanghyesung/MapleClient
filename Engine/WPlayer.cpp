#include "WPlayer.h"

#include "WResources.h"
#include "WRenderer.h"
#include "WInput.h"
#include "WAnimator.h"
#include "WPlayerBody.h"
#include "WPlayerArm.h"
#include "WPlayerHead.h"
#include "WEyes.h"
#include "WPlayerHair.h"
#include "WEquip.h"
#include "WTime.h"
#include "WShadow.h"
#include "WTransform.h"
namespace W
{
	Player::Player()
	{
		SetName(L"Player");

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"PlayerShader"));
		Resources::Insert(L"Player", pMater);
		mr->SetMaterial(pMater);

		Resources::Load<Texture>(L"darkffect", L"..\\Resources\\Texture\\Player\\skill\\effect1.png");
		Resources::Load<Texture>(L"jumpeffect", L"..\\Resources\\Texture\\Player\\skill\\effect2.png");
		Resources::Load<Texture>(L"luckeffect", L"..\\Resources\\Texture\\Player\\skill\\effect.png");
		Resources::Load<Texture>(L"luckhit", L"..\\Resources\\Texture\\Player\\skill\\hit.png");
		Resources::Load<Texture>(L"quadhit", L"..\\Resources\\Texture\\Player\\skill\\hit1.png");
		Resources::Load<Texture>(L"quadffect", L"..\\Resources\\Texture\\Player\\skill\\effect7.png");
		Resources::Load<Texture>(L"raideffect1", L"..\\Resources\\Texture\\Player\\skill\\effect8.png");
		Resources::Load<Texture>(L"raideffect2", L"..\\Resources\\Texture\\Player\\skill\\effect9.png");
		Resources::Load<Texture>(L"raidhit", L"..\\Resources\\Texture\\Player\\skill\\hit2.png");
		Resources::Load<Texture>(L"speedffect", L"..\\Resources\\Texture\\Player\\skill\\effect3.png");
		Resources::Load<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		Resources::Load<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		Resources::Load<Texture>(L"windffect1", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_0.png");
		Resources::Load<Texture>(L"windffect2", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_1.png");
		Resources::Load<Texture>(L"wind", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\hit.png");
		Resources::Load<Texture>(L"windTex", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\windshuriken.png");

	}
	Player::~Player()
	{
		
	}
	void Player::Initialize()
	{
		//PlayerScript* pPlayerScript = AddComponent<PlayerScript>();
		
		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f, -5.f, -2.f);


	}
	void Player::Update()
	{
		
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void Player::Render()
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