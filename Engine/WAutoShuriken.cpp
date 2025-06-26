#include "WAutoShuriken.h"
#include "WSceneManger.h"
#include "WLayer.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WPlayer.h"
#include "WEventManager.h"
namespace W
{
	AutoShuriken::AutoShuriken()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//¿©±â ¹Ù²ñ
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		Resources::Insert(L"shurikenMater", pMater);

		mr->SetMaterial(pMater);


		Animator* pAnimator = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"shurikenTex");
		pAnimator->Create(L"shuriken_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(48.0f, 9.f), 2, Vector2(100.f, 100.f), Vector2::Zero, Vector2(96.f, 9.f), 0.05f);
		pAnimator->Create(L"shuriken_right", pAtlas, Vector2(48.0f, 0.0f), Vector2(-48.0f, 9.f), 2, Vector2(100.f, 100.f), Vector2::Zero, Vector2(96.f, 9.f), 0.05f);
	}

	AutoShuriken::~AutoShuriken()
	{

	}

	void AutoShuriken::Initialize()
	{
		
	}

	void AutoShuriken::Update()
	{
		
	}
	void AutoShuriken::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void AutoShuriken::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vDir.x = m_iDir * -1;
		PlayerCB.vColor = Vector4::One;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void AutoShuriken::UpdateState(const wstring& _strStateName, int _iState)
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