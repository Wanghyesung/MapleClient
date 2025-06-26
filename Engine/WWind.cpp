#include "WWind.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WTransform.h"

#include "WEventManager.h"
namespace W
{
	Wind::Wind()
	{
		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"WindMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"windTex"); 
		pAnim->Create(L"move_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f),0.06f);
		pAnim->Create(L"stop_left", pAtlas, Vector2(0.0f, 316.0f), Vector2(460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f), 0.06f);
		pAnim->Create(L"finish_left", pAtlas, Vector2(0.0f, 776.0f), Vector2(612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f), 0.06f);
		
		pAnim->Create(L"move_right", pAtlas, Vector2(10614.f, 0.0f), Vector2(-402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f), 0.06f);
		pAnim->Create(L"stop_right", pAtlas, Vector2(10556.f, 316.0f), Vector2(-460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f), 0.06f);
		pAnim->Create(L"finish_right", pAtlas, Vector2(10404.f, 776.0f), Vector2(-612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, Vector2(11016.f, 1356.f), 0.06f);

		
		mr->SetMaterial(pMater);

	}
	Wind::~Wind()
	{

	}
	void Wind::Initialize()
	{
		
		
	}
	void Wind::Update()
	{
		
	}

	void Wind::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void Wind::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = m_iDir * -1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
	
		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
	void Wind::UpdateState(const wstring& _strStateName, int _iState)
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