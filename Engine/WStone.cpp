#include "WStone.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
namespace W
{
	Stone::Stone()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

	
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"StoneTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"stone_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(69.0f, 106.0f), 3, Vector2(100.f, 100.f), Vector2::Zero, Vector2(552.f, 106.f), 0.2f);

		pAnim->Play(L"stone_left", true);

	}
	Stone::~Stone()
	{


	}

	void Stone::Initialize()
	{

	}

	void Stone::Update()
	{
		GameObject::Update();
	}
	void Stone::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Stone::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Stone::UpdateState(const wstring& _strStateName, int _iAnim)
	{
		bool bRender = (_iAnim >> 16) & 0xFF;
		UCHAR cDir = (_iAnim >> 8) & 0xFF;
		UCHAR cAnimIdx = _iAnim & 0xFF;

		SetRender(bRender);

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;
	}
}