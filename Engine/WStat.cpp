#include "WStat.h"
#include "WTransform.h"
#include "WInput.h"
#include "WAutoUI.h"
#include "WUpBtn.h"
namespace W
{
	Stat::Stat():
		m_bRenderOn(false),
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"StatUITex", L"..\\Resources\\Texture\\UI\\StatUI\\StatUI.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"StatUIMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	Stat::~Stat()
	{

	}

	void Stat::Initialize()
	{
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -4.f);
		pTransform->SetScale(0.568f * 3.8f, 1.f * 3.8f, 0.f); 

		AutoUI* pAuto = new AutoUI();
		pAuto->GetComponent<Transform>()->SetPosition(0.5f,-0.5f,-0.01f);
		pAuto->GetComponent<Transform>()->SetScale(1.971f * 0.38f, 1.f * 0.38f, 0.f);
		AddChildUI(pAuto);
		//1.971 : 1

		{
			UpBtn* pUpBtn = new UpBtn();
			pUpBtn->GetComponent<Transform>()->SetPosition(0.89f, -0.84f, -0.01f);
			pUpBtn->GetComponent<Transform>()->SetScale(0.3f * 0.38f, 0.3f * 0.38f, 0.f); //1 : 1
			AddChildUI(pUpBtn);
		}

		{
			UpBtn* pUpBtn = new UpBtn();
			pUpBtn->GetComponent<Transform>()->SetPosition(0.89f, -1.03f, -0.01f);
			pUpBtn->GetComponent<Transform>()->SetScale(0.3f * 0.38f, 0.3f * 0.38f, 0.f); //1 : 1
			AddChildUI(pUpBtn);
		}

		{
			UpBtn* pUpBtn = new UpBtn();
			pUpBtn->GetComponent<Transform>()->SetPosition(0.89f, -1.22f, -0.01f);
			pUpBtn->GetComponent<Transform>()->SetScale(0.3f * 0.38f, 0.3f * 0.38f, 0.f); //1 : 1
			AddChildUI(pUpBtn);
		}

		{
			UpBtn* pUpBtn = new UpBtn();
			pUpBtn->GetComponent<Transform>()->SetPosition(0.89f, -1.41f, -0.01f);
			pUpBtn->GetComponent<Transform>()->SetScale(0.3f * 0.38f, 0.3f * 0.38f, 0.f); //1 : 1
			AddChildUI(pUpBtn);
		}

	}

	void Stat::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}

	void Stat::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void Stat::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void Stat::MouseOn()
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
	void Stat::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void Stat::MouseLbtnUp()
	{
		m_bTargetOn = false;
	}
	void Stat::MouseLbtnClicked()
	{

	}
}