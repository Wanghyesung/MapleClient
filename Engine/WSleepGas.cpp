#include "WSleepGas.h"
#include "WResources.h"
#include "WAnimator.h"
//#include "WMonsterAttackScript.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	SleepGas::SleepGas() 
	{
	
		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MagnusStoneMater", pMater);
		
		//25
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"sleepGas_start", nullptr, Vector2(0.0f, 0.0f), Vector2(135.0f, 210.0f), 25, Vector2(450.f, 450.f), Vector2::Zero, Vector2(3780.f, 481.f),0.12f);
		pAnim->Create(L"sleepGas_end", nullptr, Vector2(0.0f, 210.f), Vector2(420.0f, 271.0f), 6, Vector2(450.f, 450.f), Vector2::Zero, Vector2(3780.f, 481.f), 0.12f);

		mr->SetMaterial(pMater);
	}

	SleepGas::~SleepGas()
	{

	}
	void SleepGas::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"sleepGas");
		GetComponent<Animator>()->SetTexture(pAtlas);
	}
	void SleepGas::Update()
	{
		
	}

	void SleepGas::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SleepGas::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void SleepGas::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cRender = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iAnimIdx = cAnimIdx;
		SetRender(cRender);
	}

}