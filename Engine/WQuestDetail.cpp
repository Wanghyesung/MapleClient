#include "WQuestDetail.h"

namespace W
{
	QuestDetail::QuestDetail()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"quest_detailTex", L"..\\Resources\\Texture\\UI\\QuestUI\\quest_detail.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"quest_detailMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	QuestDetail::~QuestDetail()
	{

	}

	void QuestDetail::Initialize()
	{

	}

	void QuestDetail::Update()
	{
		UI::Update();
	}
	void QuestDetail::LateUpdate()
	{
		UI::LateUpdate();
	}
	void QuestDetail::Render()
	{
		UI::Render();
	}
	void QuestDetail::MouseOn()
	{

	}
	void QuestDetail::MouseLbtnDown()
	{

	}
	void QuestDetail::MouseLbtnUp()
	{

	}
	void QuestDetail::MouseLbtnClicked()
	{

	}
}