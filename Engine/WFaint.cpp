#include "WFaint.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WRigidbody.h"
#include "WPlayer.h"
#include "WBattleManager.h"
#include "WEventManager.h"
namespace W
{
	Faint::Faint()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"faintSkillMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"faintTex", L"..\\Resources\\Texture\\Abnormal\\faint.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"faintSkill", pAtlas, Vector2(0.0f, 0.0f), Vector2(66.0f, 18.0f), 3, Vector2(70.f, 70.f), Vector2::Zero, 0.3f);

		pAnim->Play(L"faintSkill", true);

		//GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 0.f));
	}
	Faint::~Faint()
	{

	}
	void Faint::Initialize()
	{

	}
	void Faint::Update()
	{
		Abnormal::Update();
	}
	void Faint::LateUpdate()
	{
		Abnormal::LateUpdate();
	}
	void Faint::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		Abnormal::Render();
	}

	void Faint::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::Faint);

	}


}