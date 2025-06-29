#include "WPinkBeanStone.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"
#include "WResources.h"
#include "WMonster.h"
namespace W
{
	PinkBeanStone::PinkBeanStone()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"PinkBeanStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"attack2", nullptr, Vector2(0.0f, 0.0f), Vector2(214.f, 555.0f), 27, Vector2(550.f, 550.f), Vector2::Zero, Vector2(5778.f, 555.f), 0.15f);
	
	}
	PinkBeanStone::~PinkBeanStone()
	{

	}
	void PinkBeanStone::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"PinkBean_attack2");
		GetComponent<Animator>()->SetTexture(pAtlas);
	}
	void PinkBeanStone::Update()
	{
		
	}
	void PinkBeanStone::LateUpdate()
	{
		

		GameObject::LateUpdate();
	}
	void PinkBeanStone::Render()
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
	void PinkBeanStone::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}
}