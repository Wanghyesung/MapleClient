#include "WStigmaBack.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WStigmaCount.h"
#include "WEventManager.h"
#include "WTransform.h"
namespace W
{
	StigmaBack::StigmaBack()
	{
		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StigamBackMater", pMater);
		mr->SetMaterial(pMater);
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"loop", nullptr, Vector2(0.0f, 0.0f), Vector2(80.0f, 43.0f), 11, Vector2(80.f, 80.f), Vector2::Zero, Vector2(880.f, 44.f), 0.13f);

	}
	StigmaBack::~StigmaBack()
	{

	}
	void StigmaBack::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"StigmaBack");
		GetComponent<Animator>()->SetTexture(pAtlas);
	}
	void StigmaBack::Update()
	{
		
	}
	void StigmaBack::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void StigmaBack::Render()
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
	void StigmaBack::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cAnimIdx = _iState & 0xFF;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iAnimIdx = cAnimIdx;
	}
}