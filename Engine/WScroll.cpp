#include "WScroll.h"
#include "WInventory.h"
#include "WTransform.h"
#include "WInput.h"
namespace W
{
	Scroll::Scroll():
		m_iCurY(0),
		m_iMaxY(4),
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::Zero),
		m_eParentUI(eParentUI::None)
	{

		std::shared_ptr<Texture> pTex 
		= Resources::Load<Texture>(L"scroll1Tex", L"..\\Resources\\Texture\\UI\\InvenUI\\scroll1.png");

		pTex =
			Resources::Load<Texture>(L"scroll0Tex", L"..\\Resources\\Texture\\UI\\InvenUI\\scroll0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"scrollMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetPosition(0.84f, 1.11f, -0.1f);
		GetComponent<Transform>()->SetScale(0.423f * 0.3f, 1.f * 0.3f, 0.f);//0.423 : 1
		//0.84 : 1
	}
	Scroll::~Scroll()
	{
	}
	void Scroll::Initialize()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		m_vStartPos = Vector2(vPosition.x, vPosition.y);
	}
	void Scroll::Update()
	{
		UI::Update();
	}
	void Scroll::LateUpdate()
	{
		UI::LateUpdate();
	}
	void Scroll::Render()
	{
		UI::Render();
	}
	void Scroll::MouseOn()
	{		
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition();
			vPosisition.y += vDiff.y;

			if (vPosisition.y >= m_vCurStartPos.y)
				vPosisition.y = m_vCurStartPos.y;

			else if(vPosisition.y <= m_vCurEndPos.y)
				vPosisition.y = m_vCurEndPos.y;

			pTransform->SetPosition(vPosisition);

			m_vDragStartPos = Input::GetMousePos();

			check_pos();
		}

	}
	void Scroll::MouseLbtnDown()
	{
		m_bTargetOn = true;

		//부모 위치에 따라서 내 스크롤 위치도 바뀌게
		Vector3 vParentPos = GetParentUI()->GetComponent<Transform>()->GetPosition();
		Vector3 vPos = GetComponent<Transform>()->GetPosition();

		m_vCurStartPos.y = vParentPos.y + m_vStartPos.y;
		m_vCurEndPos.y = vParentPos.y + m_vEndPos.y;

		m_vDragStartPos = Input::GetMousePos();

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"scrollMater");
		pMater->SetTexture(Resources::Find<Texture>(L"scroll1Tex"));
	}
	void Scroll::MouseLbtnUp()
	{
		m_bTargetOn = false;

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"scrollMater");
		pMater->SetTexture(Resources::Find<Texture>(L"scroll0Tex"));
	}
	void Scroll::MouseLbtnClicked()
	{

	}
	void Scroll::check_pos()
	{
		Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
		//1.91
		float fLen = fabs(m_vCurStartPos.y) + fabs(m_vCurEndPos.y);
		float fCur = m_vCurStartPos.y - vPosisition.y;
		UINT Y = fCur / m_iMaxY * 10.f;

		if (m_iCurY != Y)
		{
			// 0 -> 1
			int iDir = Y > m_iCurY ? iDir = -1 : iDir = 1;

			switch (m_eParentUI)
			{
			case W::enums::eParentUI::Inventory:
			{
				Inventory* pInven = dynamic_cast<Inventory*>(GetParentUI());
				pInven->CheckPosition(iDir);
				pInven->SetScrollCurY(Y);
			}
			break;
			}
		}
		m_iCurY = Y;
	}
}