#include "WEyeItem.h"
#include "WHairItem.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WTransform.h"
namespace W
{
	EyeItem::EyeItem()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"eyeItemTex", L"..\\Resources\\Texture\\UI\\ItemUI\\iconRaw0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		//pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"eyeitemMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(0.1f * 3.5f, 0.1f * 2.9f, 0.f);
		SetIconType(eIconType::Cash);
	}
	EyeItem::EyeItem(const EyeItem& _pItem):
		ItemUI(_pItem)
	{
	}
	EyeItem::~EyeItem()
	{
	}
	void EyeItem::Initialize()
	{

	}
	void EyeItem::Update()
	{
		ItemUI::Update();
	}
	void EyeItem::LateUpdate()
	{
		ItemUI::LateUpdate();
	}
	void EyeItem::Render()
	{
		ItemUI::Render();
	}
	void EyeItem::MouseOn()
	{
		ItemUI::MouseOn();
	}
	void EyeItem::MouseLbtnDown()
	{
		ItemUI::MouseLbtnDown();
	}
	void EyeItem::MouseLbtnUp()
	{
		IconUI::MouseLbtnUp();
	}
	void EyeItem::MouseLbtnClicked()
	{
		ItemUI::MouseLbtnClicked();
	}

	EyeItem* EyeItem::Create_Clone()
	{
		return new EyeItem(*this);
	}

	void EyeItem::Using()
	{
		Protocol::C_ITEM pkt;

		GameObject* pObj = SceneManger::FindPlayer();

		UINT iSceneID = SceneManger::GetActiveScene()->GetSceneID();
		int iITemID = GetItemID();

		pkt.set_scene_playerid_itemid((iSceneID << 24) | (PLAYER_ID << 16) | iITemID);
		shared_ptr<SendBuffer> pBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pBuffer);

		DeleteParent();
		SetState(eState::Dead);
	}

}