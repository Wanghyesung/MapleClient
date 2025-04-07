#include "WMobZone.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WPlayer.h"
#include "WSceneManger.h"
#include "WMonster.h"

#include "WAnimator.h"
#include "WTime.h"
#include "WTransform.h"
namespace W
{
	MobZone::MobZone()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MobZoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_Zone0");
		Resources::Find<Texture>(L"Megnus_Zone1");
		Resources::Find<Texture>(L"Megnus_Zone2");
		Resources::Find<Texture>(L"Megnus_Zone3");

		Animator* pAnim = AddComponent<Animator>();		
		
		for (int i = 0; i < 4; ++i)
		{
			std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_Zone" + i);

			Animator* pAnim = GetComponent<Animator>();
			switch (i)
			{
			case 0:
				pAnim->Create(L"Megnus_Zone" + i, pAtlas, Vector2(0.0f, 0.0f), Vector2(796.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

			case 1:
				pAnim->Create(L"Megnus_Zone" + i, pAtlas, Vector2(0.0f, 0.0f), Vector2(696.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
				break;
			case 2:
				pAnim->Create(L"Megnus_Zone" + i, pAtlas, Vector2(0.0f, 0.0f), Vector2(596.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
				break;
			case 3:
				pAnim->Create(L"Megnus_Zone" + i, pAtlas, Vector2(0.0f, 0.0f), Vector2(396.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
				break;
			}
		}

		pAnim->Play(L"Megnus_Zone0", true);

		

	}
	MobZone::~MobZone()
	{

	}
	void MobZone::Initialize()
	{
		
	}
	void MobZone::Update()
	{
	}
	void MobZone::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MobZone::Render()
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