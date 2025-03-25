#include "WMonsterHP.h"
#include "WMonster.h"
#include "WObject.h"
#include "WMonsterScript.h"
#include "WRenderer.h"
#include "WMonsterBackHP.h"
#include "WMonsterManager.h"
namespace W
{
	UINT MonsterHP::HP_COUNT = 0;

	MonsterHP::MonsterHP(bool bBoss):
		m_pOwner(nullptr),
		m_fHP(100.f),
		m_iHPCount(HP_COUNT),
		m_bActive(false),
		m_bBoss(bBoss)
	{
		++HP_COUNT;
		std::wstring strNum =  std::to_wstring(m_iHPCount);

		std::shared_ptr<Texture> spAtlas;
		if (!m_bBoss)
		{
			spAtlas = Resources::Load<Texture>(L"MonHP", L"..\\Resources\\Texture\\MonsterUI\\energe.png");
			GetComponent<Transform>()->SetScale(1.f * 0.66f, 1.f * 0.13f, 0.f);
		}
		else
		{
			spAtlas = Resources::Load<Texture>(L"BossHP", L"..\\Resources\\Texture\\MonsterUI\\bossHP.png");
			GetComponent<Transform>()->SetScale(1.2f * 7.6f, 1.2f * 0.4f, 0.f);
			GetComponent<Transform>()->SetPosition(0.f, 3.5f, -2.f);
			m_bActive = true;
		}

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"PlayerUIShader"));
		Resources::Insert(L"MonHP" + strNum, pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		pMater->SetTexture(spAtlas);

	}
	MonsterHP::~MonsterHP()
	{
		
	}
	void MonsterHP::Initialize()
	{
		m_pHPBack = new MonsterBackHP(m_bBoss);
		m_pHPBack->SetHP(this);
		if(!m_bBoss)
			SceneManger::AddGameObject(eLayerType::Object, m_pHPBack);
		else
			SceneManger::AddGameObject(eLayerType::UI, m_pHPBack);
	}
	void MonsterHP::Update()
	{
		if (!m_bActive)
			return;
		
		if (m_fHP <= 0.f)
		{
			m_bActive = false;
			object::Destroy(this);
			object::Destroy(m_pHPBack);
			return;
		}

		if (!m_bBoss)
		{
			Vector3 vPosition = m_pOwner->GetComponent<Transform>()->GetPosition();
			vPosition.z -= 0.02f;
			vPosition.y += 0.5f;
			GetComponent<Transform>()->SetPosition(vPosition);
		}
		MonsterScript* pScript = m_pOwner->GetScript<MonsterScript>();
		tObjectInfo tObjInfo = pScript->GetObjectInfo();
		m_fHP = tObjInfo.fHP;

		GameObject::Update();
	}
	void MonsterHP::LateUpdate()
	{
		if (!m_bActive)
			return;

		GameObject::LateUpdate();
	}
	void MonsterHP::Render()
	{
		if (!m_bActive)
			return;
		
		renderer::PlayerUICB PlayerUICB;
		PlayerUICB.vSize.x = m_fHP;
		
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::PlayerUI];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerUICB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void MonsterHP::DeleteHP()
	{
		MonsterManager::AddDeleteObject(m_pHPBack);
		MonsterManager::AddDeleteObject(this);
		
	}
}