#include "WMobZone.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WPlayer.h"
#include "WSceneManger.h"
#include "WMonster.h"
#include "WBattleManager.h"
#include "WPlayerScript.h"
#include "WAnimator.h"
#include "WInfo.h"
#include "WTime.h"
namespace W
{
	MobZone::MobZone():
		m_pTarget(nullptr),
		m_pMonster(nullptr),
		m_iCurLevel(0),
		m_tAttackInfo{},
		m_fAttackTime(2.f),
		m_fCurTime(0.f)
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
		pAnim->Create(L"Megnus_Zone0", pAtlas, Vector2(0.0f, 0.0f), Vector2(796.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		
		pAnim->Play(L"Megnus_Zone0", true);
	}
	MobZone::~MobZone()
	{

	}
	void MobZone::Initialize()
	{
		m_tAttackInfo.fAttackDamage = 10.f;
		m_tAttackInfo.fAttRcnt = 0.f;//¸ÂÀ¸
		m_tAttackInfo.fAttUpperRcnt = 0.f;

		m_vecLength.push_back(3.3f);
		m_vecLength.push_back(2.7f);
		m_vecLength.push_back(2.1f);
		m_vecLength.push_back(1.5f);

	}
	void MobZone::Update()
	{
		

		Vector3 vPosition = m_pMonster->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPosition);

		m_fCurTime += Time::DeltaTime();
		if (m_fCurTime >= m_fAttackTime)
		{
			m_fCurTime = 0.f;
			attack();
		}
		
		GameObject::Update();
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
	void MobZone::SetLevel(UINT _iNum)
	{
		m_iCurLevel = _iNum;

		if (m_iCurLevel >= 4)
		{
			SetState(GameObject::eState::Paused);
			return;
		}

		std::wstring strLevel =  std::to_wstring(m_iCurLevel);
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_Zone" + strLevel);

		Animator* pAnim = GetComponent<Animator>();
		switch (m_iCurLevel)
		{
		case 1:
			pAnim->Create(L"Megnus_Zone" + strLevel, pAtlas, Vector2(0.0f, 0.0f), Vector2(696.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
			break;
		case 2:
			pAnim->Create(L"Megnus_Zone" + strLevel, pAtlas, Vector2(0.0f, 0.0f), Vector2(596.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
			break;
		case 3:
			pAnim->Create(L"Megnus_Zone" + strLevel, pAtlas, Vector2(0.0f, 0.0f), Vector2(396.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
			break;
		}
		
		pAnim->Play(L"Megnus_Zone" + strLevel, true);
	}
	void MobZone::attack()
	{
		m_pTarget = dynamic_cast<Player*>(SceneManger::FindPlayer());
		if (m_pTarget &&
			m_pTarget->GetState() == GameObject::eState::Active)
		{
			float fPlayerX = m_pTarget->GetComponent<Transform>()->GetPosition().x;
			float fX = GetComponent<Transform>()->GetPosition().x;

			float fLen = fPlayerX - fX;
			if (fabs(fLen) >= m_vecLength[m_iCurLevel])
				m_pTarget->GetScript<PlayerScript>()->Hit(m_tAttackInfo, L"MobZone");
		}

	}
}