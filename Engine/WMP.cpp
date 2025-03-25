#include "WMP.h"
#include "WRenderer.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WSceneManger.h"

namespace W
{
	MP::MP():
		m_pPlayerScript(nullptr)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"MPTex", L"..\\Resources\\Texture\\UI\\Interface\\MP.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"PlayerUIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"MPMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	MP::~MP()
	{

	}
	void MP::Initialize()
	{
		std::vector<GameObject*> vecObj = SceneManger::GetActiveScene()->GetLayer(eLayerType::Player).GetGameObjects();
		Player* pPlayer = dynamic_cast<Player*>(vecObj[0]);

		m_pPlayerScript = pPlayer->GetScript<PlayerScript>();
	}
	void MP::Update()
	{
		UI::Update();
	}
	void MP::LateUpdate()
	{
		UI::LateUpdate();
	}
	void MP::Render()
	{
		const tObjectInfo& tObjectInfo = m_pPlayerScript->GetObjectInfo();
		float fSize = tObjectInfo.fMP;

		renderer::PlayerUICB PlayerUICB;
		PlayerUICB.vSize.x = fSize;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::PlayerUI];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerUICB);
		pConstBuffer->Bind(eShaderStage::PS);

		UI::Render();
	}
	void MP::MouseOn()
	{
	}
	void MP::MouseLbtnDown()
	{
	}
	void MP::MouseLbtnUp()
	{
	}
	void MP::MouseLbtnClicked()
	{
	}
}