#include "WDamageFont.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WTexture.h"
#include "WRenderer.h"
#include "WBattleManager.h"


namespace W
{
	UINT DamageFont::FontCount = 0;

	DamageFont::DamageFont():
		m_bActive(false),
		m_fCurTime(0.f),
		m_fDeleteTime(2.3f),
		m_iCount(FontCount++),
		m_vColor(Vector4(1.f,1.f,1.f,0.2f))
	{
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"DamageMater");

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}

	DamageFont::~DamageFont()
	{

	}
	void DamageFont::Initialize()
	{

	}
	void DamageFont::Update()
	{
		if (!m_bActive)
			return;

		m_fCurTime+= Time::DeltaTime();

		m_vColor.w += Time::DeltaTime();

		if (m_vColor.w >= 1.f)
			m_vColor.w = 1.f;
	

		if (m_fCurTime >= m_fDeleteTime)
		{
			m_bActive = false;
			m_fCurTime = 0.f;
			SceneManger::Erase(this);
			BattleManager::PushFont(this);
			return;
		}

		GameObject::Update();
	}
	void DamageFont::LateUpdate()
	{
		if (!m_bActive)
			return;

		Transform* pTr = GetComponent<Transform>();

		Vector3 vPosition = pTr->GetPosition();
		vPosition.y += (0.4f * Time::DeltaTime());
		pTr->SetPosition(vPosition);

		GameObject::LateUpdate();
	}
	void DamageFont::Render()
	{
		if (!m_bActive)
			return;

		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = m_vColor;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void DamageFont::CheckDamage(UINT _iDamage)
	{	
		std::wstring strNum = std::to_wstring(_iDamage);

		std::shared_ptr<Texture> spTex =
			Resources::Find<Texture>(L"Number_" + strNum);

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(spTex);
		GetComponent<Transform>()->SetScale(0.01f * spTex->GetWidth() , 0.01f * spTex->GetHeight() , 0.f);

		m_vColor = Vector4(1.f, 1.f, 1.f, 0.2f);
	}
}