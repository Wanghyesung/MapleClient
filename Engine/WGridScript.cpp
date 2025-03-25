#include "WGridScript.h"
#include "WConstantBuffer.h"
#include "WCamera.h"
#include "WTransform.h"
#include "WApplication.h"
#include "WGameObject.h"
#include "WRenderer.h"

extern W::Application application;

namespace W
{
	GridScript::GridScript():
		m_pCamera(nullptr)
	{
	}
	GridScript::~GridScript()
	{
	}
	void GridScript::Initialize()
	{
	}
	void GridScript::Update()
	{
		//UI 카메라가 아니라 메인카메라를 받아야함
		if (m_pCamera == nullptr)
			return;

		GameObject* pGameObj = m_pCamera->GetOwner();

		Transform* pTr = pGameObj->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();

		//카메라 사이즈
		float fScale = m_pCamera->GetSize();

		//해상도
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 vResolution(width, height);

		graphics::ConstantBuffer* pConstBF =
			renderer::constantBuffer[(int)eCBType::Grid];

		renderer::GridCB data;
		data.m_vCameraPosition = Vector4(vPos.x, vPos.y, vPos.z, 1.f);
		data.m_vResolution = vResolution;
		data.m_vCameraScale = Vector2(fScale, fScale);

		pConstBF->SetData(&data);
		pConstBF->Bind(eShaderStage::VS);
		pConstBF->Bind(eShaderStage::PS);
	}
	void GridScript::LateUpdate()
	{

	}
	void GridScript::Render()
	{

	}
}