#include "WSlow.h"
#include "WAnimator.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	Slow::Slow(float _fAccStat):
		m_fAccValue(_fAccStat)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"slow2Mater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"slow2Tex", L"..\\Resources\\Texture\\Abnormal\\slow2.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"slow", pAtlas, Vector2(0.0f, 0.0f), Vector2(112.0f, 91.0f), 6, Vector2(110.f, 110.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"slow", true);
	}
	Slow::~Slow()
	{

	}
	void Slow::Initialize()
	{
		
	}
	void Slow::Update()
	{
		Abnormal::Update();
	}
	void Slow::LateUpdate()
	{
		Abnormal::LateUpdate();

	}
	void Slow::Render()
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
	void Slow::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::Slow, -m_fAccValue);
	}
}