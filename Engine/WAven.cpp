#include "WAven.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WTransform.h"
namespace W
{
	Aven::Aven() 
	{
		//SetName(L"Aven");

		GetComponent<Transform>()->SetScale(2.f * 0.72, 2.f * 0.72, 0.f);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//¿©±â ¹Ù²ñ
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"AvenMater", pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"avenTex");
		pMater->SetTexture(pAtlas);
		mr->SetMaterial(pMater);

	}

	Aven::~Aven()
	{

	}

	void Aven::Initialize()
	{
	
	}

	void Aven::Update()
	{
		
	}

	void Aven::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}

	void Aven::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vColor = Vector4::One;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Aven::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cDir = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;
	}
	
}