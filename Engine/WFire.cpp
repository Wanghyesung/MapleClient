#include "WFire.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"
namespace W
{
	Fire::Fire() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"FireMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);
			
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Fire_left", nullptr, Vector2(0.0f, 0.0f), Vector2(111.f, 110.0f), 30, Vector2(110.f, 110.f), Vector2::Zero, Vector2(3330.f, 110.f), 0.15f);

		GetComponent<Transform>()->SetScale(1.1f, 1.1f, 0.f);
	}

	Fire::~Fire()
	{

	}

	void Fire::Initialize()
	{
		Animator* pAnim = GetComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"FireTex");
		pAnim->SetTexture(pAtlas);

		m_strCurStateName.clear();
	}

	void Fire::Update()
	{
		
	}

	void Fire::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Fire::Render()
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
	
	void Fire::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}
}