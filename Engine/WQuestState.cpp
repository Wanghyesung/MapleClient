#include "WQuestState.h"
#include "WInput.h"

#include "WQuestDetail.h"
namespace W
{
	QuestState::QuestState():
		m_bRenderOn(false),
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"questTex", L"..\\Resources\\Texture\\UI\\QuestUI\\quest.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"questMaer", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	QuestState::~QuestState()
	{

	}
	void QuestState::Initialize()
	{
		GetComponent<Transform>()->SetPosition(0.f,0.f,-4.f);
		GetComponent<Transform>()->SetScale(0.745f * 3.8f, 1.f * 3.8f , 0.f);

		QuestDetail* pQuestDetail = new QuestDetail();
		pQuestDetail->GetComponent<Transform>()->SetPosition(2.85f, 0.f, -0.01f);
		pQuestDetail->GetComponent<Transform>()->SetScale(0.747f * 3.8f, 1.f * 3.8f, 0.f); //0.747 : 1
		AddChildUI(pQuestDetail);
	}
	void QuestState::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}
	void QuestState::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void QuestState::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void QuestState::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void QuestState::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void QuestState::MouseLbtnUp()
	{
		m_bTargetOn = false;
	}
	void QuestState::MouseLbtnClicked()
	{

	}
}