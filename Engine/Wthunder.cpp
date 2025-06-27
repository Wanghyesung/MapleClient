#include "WThunder.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"

namespace W
{
	Thunder::Thunder() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"FireMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

	
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Thunder_left", nullptr, Vector2(0.0f, 0.0f), Vector2(180.f, 845.0f), 30, Vector2(800.f, 800.f), Vector2::Zero, Vector2(5400.f, 845.f), 0.15f);

		
		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
	}

	Thunder::~Thunder()
	{

	}

	void Thunder::Initialize()
	{
		Animator* pAnim = GetComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"ThunderTex");
		pAnim->SetTexture(pAtlas);

		m_strCurStateName.clear();
	}

	void Thunder::Update()
	{
		
	}

	void Thunder::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Thunder::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = m_iDir;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void Thunder::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}
	
}