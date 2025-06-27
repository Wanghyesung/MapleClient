#include "WBlast.h"
#include "WTransform.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WEventManager.h"
#include "WResources.h"

namespace W
{
	Blast::Blast()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"BlastMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"blast");
		pAnim->Create(L"left", pAtlas, Vector2(0.0f, 0.0f), Vector2(695.0f, 506.0f), 23, Vector2(700.f, 700.f), Vector2::Zero, Vector2(15985.f, 506.f), 0.03f);
		pAnim->Create(L"right", pAtlas, Vector2(15290.0f, 0.0f), Vector2(-695.0f, 506.0f), 23, Vector2(700.f, 700.f), Vector2::Zero, Vector2(15985.f, 506.f), 0.03f);


	}
	Blast::~Blast()
	{

	}
	void Blast::Initialize()
	{
		
	}
	void Blast::Update()
	{

	}
	void Blast::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Blast::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = m_iDir * -1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Blast::UpdateState(const wstring& _strStateName, int _iState)
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