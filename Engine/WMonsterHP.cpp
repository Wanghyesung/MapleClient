#include "WMonsterHP.h"
#include "WMonster.h"
#include "WRenderer.h"
#include "WMonsterBackHP.h"
#include "WResources.h"
#include "WTransform.h"

namespace W
{
	UINT MonsterHP::HP_COUNT = 0;

	MonsterHP::MonsterHP():
		m_fHP(100.f),
		m_iHPCount(HP_COUNT)
	{
		++HP_COUNT;
		std::wstring strNum =  std::to_wstring(m_iHPCount);

		std::shared_ptr<Texture> spAtlas;
		
		Resources::Load<Texture>(L"MonHP", L"..\\Resources\\Texture\\MonsterUI\\energe.png");
		Resources::Load<Texture>(L"BossHP", L"..\\Resources\\Texture\\MonsterUI\\bossHP.png");
		

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"PlayerUIShader"));
		Resources::Insert(L"MonHP" + strNum, pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

	}
	MonsterHP::~MonsterHP()
	{
		
	}
	void MonsterHP::Initialize()
	{
		eLayerType eType = GetLayerType();
		shared_ptr<Texture> pTex = nullptr;
		if (eType == eLayerType::Object)
		{
			pTex = Resources::Find<Texture>(L"MonHP");
			GetComponent<Transform>()->SetScale(1.f * 0.66f, 1.f * 0.13f, 0.f);
		}
		else
		{
			pTex = Resources::Find<Texture>(L"BossHP");
			GetComponent<Transform>()->SetScale(1.2f * 7.6f, 1.2f * 0.4f, 0.f);
			GetComponent<Transform>()->SetPosition(0.f, 3.5f, -2.f);
		}

		MeshRenderer* pRenderer = GetComponent<MeshRenderer>();
		pRenderer->GetMaterial()->SetTexture(pTex);
	}
	void MonsterHP::Update()
	{
		
	}
	void MonsterHP::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MonsterHP::Render()
	{
		renderer::PlayerUICB PlayerUICB;
		PlayerUICB.vSize.x = m_fHP;
		
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::PlayerUI];
		pConstBuffer->SetData(&PlayerUICB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void MonsterHP::UpdateState(const wstring& _strStateName, int _iState)
	{
		m_fHP = _iState;
	}
	
}