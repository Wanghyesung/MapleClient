#include "WUltimateBackground.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WTransform.h"
namespace W
{
	UltimateBackground::UltimateBackground()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"FullScreenAnimMaterial");
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		mr->SetMaterial(pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"ultimate1");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(1412.f, 812.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14120.f, 1624.f), 0.13f);
		pAnim->FindAnimation(L"ultimate1")->Create(L"ultimate1", pTex, Vector2(0.f, 812.f), Vector2(1412.f, 812.f), 6, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14120.f, 1624.f), 0.13f);
	
		GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -4.f));
	}
	UltimateBackground::~UltimateBackground()
	{

	}
	void UltimateBackground::Initialize()
	{
		GetComponent<Animator>()->Play(L"ultimate1", true);
	}

	void UltimateBackground::Update()
	{
		
	}
	void UltimateBackground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateBackground::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4(1.f, 1.f, 1.f, 0.5f);
		
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void UltimateBackground::UpdateState(const wstring& _strStateName, int _iState)
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