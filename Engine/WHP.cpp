#include "WHP.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WInfo.h"
#include "WRenderer.h"

namespace W
{
	HP::HP():
		m_pPlayerScript(nullptr)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"HPTex", L"..\\Resources\\Texture\\UI\\Interface\\HP.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"PlayerUIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"HPMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	HP::~HP()
	{

	}
	void HP::Initialize()
	{
		std::vector<GameObject*> vecObj = SceneManger::GetActiveScene()->GetLayer(eLayerType::Player).GetGameObjects();
		Player* pPlayer = dynamic_cast<Player*>(vecObj[0]);

		m_pPlayerScript = pPlayer->GetScript<PlayerScript>();
	}
	void HP::Update()
	{
		UI::Update();
	}
	void HP::LateUpdate()
	{
		UI::LateUpdate();
	}
	void HP::Render()
	{
		const tObjectInfo& tObjectInfo = m_pPlayerScript->GetObjectInfo();
		float fSize = tObjectInfo.fHP;
		
		renderer::PlayerUICB PlayerUICB;
		PlayerUICB.vSize.x = fSize;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::PlayerUI];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerUICB);
		pConstBuffer->Bind(eShaderStage::PS);

		UI::Render();
	}
	void HP::MouseOn()
	{
	}
	void HP::MouseLbtnDown()
	{
	}
	void HP::MouseLbtnUp()
	{
	}
	void HP::MouseLbtnClicked()
	{
	}
}