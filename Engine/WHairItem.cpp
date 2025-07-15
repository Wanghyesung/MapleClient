#include "WHairItem.h"
#include "WHairItem.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WTransform.h"
#include "WEventManager.h"
namespace W
{
	HairItem::HairItem()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"hairItemTex", L"..\\Resources\\Texture\\UI\\ItemUI\\iconRaw1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"alixirMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.3f, 0.1f * 2.1f, 0.f);
		SetIconType(eIconType::Cash);
	}
	HairItem::HairItem(const HairItem& _pItem) :
		ItemUI(_pItem)
	{

	}
	HairItem::~HairItem()
	{
	}
	void HairItem::Initialize()
	{
		
	}
	void HairItem::Update()
	{
		ItemUI::Update();
	}
	void HairItem::LateUpdate()
	{
		ItemUI::LateUpdate();
	}
	void HairItem::Render()
	{
		ItemUI::Render();
	}
	void HairItem::MouseOn()
	{
		ItemUI::MouseOn();
	}
	void HairItem::MouseLbtnDown()
	{
		ItemUI::MouseLbtnDown();
	}
	void HairItem::MouseLbtnUp()
	{
		IconUI::MouseLbtnUp();
	}

	void HairItem::MouseLbtnClicked()
	{
		ItemUI::MouseLbtnClicked();
	}

	HairItem* HairItem::Create_Clone()
	{
		return new HairItem(*this);
	}

	void HairItem::Using()
	{
	
		Protocol::C_ITEM pkt;

		GameObject* pObj = SceneManger::FindPlayer();
		
		UINT iSceneID = SceneManger::GetActiveScene()->GetSceneID();
		int iITemID = GetItemID();

		pkt.set_scene_playerid_item_id((iSceneID<< 24) | (PLAYER_ID << 16) | iITemID);
		shared_ptr<SendBuffer> pBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pBuffer);


		DeleteParent();
		SetState(eState::Dead);
	}
	
}