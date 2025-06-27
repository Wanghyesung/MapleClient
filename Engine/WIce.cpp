#include "WIce.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"
namespace W
{
	Ice::Ice()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"IceMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Ice_left", nullptr, Vector2(0.0f, 0.0f), Vector2(216.f, 242.0f), 30, Vector2(220.f, 220.f), Vector2::Zero, Vector2(6480.f, 242.f), 0.15f);

		GetComponent<Transform>()->SetScale(2.1f, 2.1f, 0.f);
	}

	Ice::~Ice()
	{

	}

	void Ice::Initialize()
	{
		Animator* pAnim = GetComponent<Animator>();

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"IceTex");
		pAnim->SetTexture(pAtlas);

		m_strCurStateName.clear();
	}

	void Ice::Update()
	{
		
	}

	void Ice::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ice::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Ice::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}

}