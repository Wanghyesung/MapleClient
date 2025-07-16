#include "WDamageFont.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WTexture.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	UINT DamageFont::FONTCOUNT = 0;
	DamageFont::DamageFont():
		m_vColor(Vector4(1.f,1.f,1.f,0.2f)),
		m_iDamage(-1)
	{
		shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"DamageMater" + to_wstring(FONTCOUNT++), pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}

	DamageFont::~DamageFont()
	{

	}
	void DamageFont::Initialize()
	{
		m_iDamage = -1;
	}
	void DamageFont::Update()
	{
	
	}
	void DamageFont::LateUpdate()
	{	
		if (m_iDamage == -1)
			return;

		GameObject::LateUpdate();
	}
	void DamageFont::Render()
	{
		if (m_iDamage == -1)
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

	void DamageFont::UpdateState(const wstring& _strStateName, int _iState)
	{
		m_vColor.w = (_iState / 10000.f);
		
		if (m_iDamage == -1)
			CheckDamage((_iState >> 16));
	}

	void DamageFont::CheckDamage(UINT _iDamage)
	{	
		std::wstring strNum = std::to_wstring(_iDamage);

		std::shared_ptr<Texture> spTex =
			Resources::Find<Texture>(L"Number_" + strNum);

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(spTex);
		GetComponent<Transform>()->SetScale(0.01f * spTex->GetWidth() , 0.01f * spTex->GetHeight() , 0.f);

		m_vColor = Vector4(1.f, 1.f, 1.f, 0.2f);
		m_iDamage = _iDamage;
	}
}