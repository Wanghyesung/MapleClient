#include "WHorntail.h"
#include "WAnimator.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WHorntailHeadA.h"
#include "WHorntailHeadB.h"
#include "WHorntailHeadC.h"
#include "WHorntailLeftHand.h"
#include "WHorntailRightHand.h"
#include "WHorntailLeg.h"
#include "WHorntailWing.h"
#include "WHorntailTail.h"
#include "WSceneManger.h"
#include "WObject.h"
#include "WCameraScript.h"

//수동으로 exe파일에 넣어주기
//속성 -> 빌드이벤트 -> 복사해서 넘기기
namespace W
{
	Horntail::Horntail()
	{
		m_vecMonster.resize(8);

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HorntailStartTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		//pAnim->Create(L"HorntailStart", pAtlas, Vector2(5316.f, 2673.f), Vector2(886.f, 891.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 0.f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 891.0f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 1782.f), Vector2(886.f, 891.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailStart")->Create(L"HorntailStart", pAtlas, Vector2(0.0f, 2673.f), Vector2(886.f, 891.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
		pAtlas = Resources::Find<Texture>(L"HorntailDead");
		pAnim->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 0.f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailDead")->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 643.0f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"HorntailDead")->Create(L"HorntailDead", pAtlas, Vector2(0.0f, 1286.f), Vector2(731.f, 643.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}

	Horntail::~Horntail()
	{

	}

	void Horntail::Initialize()
	{

	}

	void Horntail::Update()
	{
		
	}

	void Horntail::LateUpdate()
	{
		
		Monster::LateUpdate();
	}

	void Horntail::Render()
	{
	
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
}
