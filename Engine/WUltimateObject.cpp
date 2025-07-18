#include "WUltimateObject.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WTransform.h"

namespace W
{
	UltimateObject::UltimateObject()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"FullScreenAnimMaterial");
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"ultimate0");
		pAnim->Create(L"ultimate", pAtlas, Vector2(0.f, 0.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14560.f, 5160.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 860.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14560.f, 5160.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 1720.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14560.f, 5160.f),0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 2580.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14560.f, 5160.f),0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 3440.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), Vector2(14560.f, 5160.f),0.08f);

		GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -4.f));

	}
	UltimateObject::~UltimateObject()
	{

	}
	void UltimateObject::Initialize()
	{
		GetComponent<Animator>()->Play(L"ultimate", false);
	}
	void UltimateObject::Update()
	{
		
	}
	void UltimateObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateObject::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void UltimateObject::UpdateState(const wstring& _strStateName, int _iState)
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