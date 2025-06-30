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
	MobZone::MobZone():
		m_iLevel(0)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MobZoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		Animator* pAnim = AddComponent<Animator>();		
		pAnim->Create(L"Megnus_Zone0", nullptr, Vector2(0.0f, 0.0f), Vector2(796.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(6368.f, 852.f), 0.15f);
		
		pAnim->Create(L"Megnus_Zone1", nullptr, Vector2(0.0f, 0.0f), Vector2(696.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(5568.f, 852.f), 0.15f);
		
		pAnim->Create(L"Megnus_Zone2", nullptr, Vector2(0.0f, 0.0f), Vector2(596.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(4768.f, 852.f), 0.15f);
		
		pAnim->Create(L"Megnus_Zone3", nullptr, Vector2(0.0f, 0.0f), Vector2(396.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(3168.f, 852.f), 0.15f);
				
	}
	MobZone::~MobZone()
	{

	}
	void MobZone::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_Zone0");
		GetComponent<Animator>()->SetTexture(pAtlas);
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

	void MobZone::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cLevel = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		m_iAnimIdx = cAnimIdx;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);

			if (cLevel != m_iLevel)
			{
				shared_ptr<Texture> pTex = Resources::Find<Texture>(L"Megnus_Zone" + to_wstring(m_iLevel));
				GetComponent<Animator>()->SetTexture(pTex);

				if (m_iLevel == 4)
					SetRender(false);
			}

			m_iLevel = cLevel;
		}
	}
	
}