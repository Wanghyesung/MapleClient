#include "WInputObject.h"
#include "WAnimator.h"
#include "WInputBackground.h"
#include "WRenderer.h"
#include "WInput.h"
#include "WResources.h"

namespace W
{
	InputObject::InputObject()
	{

	}

	InputObject::~InputObject()
	{

	}

	void InputObject::Initialize()
	{
		shared_ptr<Texture> pText = Resources::Find<Texture>(GetName());
		GetComponent<Animator>()->SetTexture(pText);

		Vector3 vTargetPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		vTargetPos.y += 1.f;
		vTargetPos.z += 1.f;

		float x = GetComponent<Transform>()->GetPosition().x;
		vTargetPos.x = vTargetPos.x + x;

		GetComponent<Transform>()->SetDirectPosition(vTargetPos);

		m_strCurStateName.clear();
		SetRender(true);
	}

	void InputObject::Update()
	{

	}
	void InputObject::CreateInputObject(eKeyCode _eKeyCode)
	{
		std::wstring strDir = GetWDir(_eKeyCode);

		SetName(L"Input" + strDir);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Input" + strDir);

		Animator* pAnim = AddComponent<Animator>();

		pAnim->Create(L"clear", nullptr, Vector2(0.0f, 0.0f), Vector2(80.f, 79.0f), 7, Vector2(100.f, 100.f), Vector2::Zero, Vector2(560.f, 156.f), 0.15f);
		pAnim->Create(L"failed", nullptr, Vector2(0.0f, 79.0f), Vector2(89.f, 77.0f), 4, Vector2(100.f, 100.f), Vector2::Zero, Vector2(560.f, 156.f), 0.15f);

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"InputMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

	}
	wstring InputObject::GetWDir(eKeyCode _eKeyCode)
	{
		switch (_eKeyCode)
		{
		case W::eKeyCode::UP:
			return L"up";
		case W::eKeyCode::DOWN:
			return L"down";
		case W::eKeyCode::LEFT:
			return L"left";
		case W::eKeyCode::RIGHT:
			return L"right";
		}
	}

	void InputObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void InputObject::Render()
	{

		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void InputObject::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cAnimIdx = _iState & 0xFF;
		bool bRender = (_iState >> 8) & 0xFF;

		SetRender(bRender);

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iAnimIdx = cAnimIdx;
	}

	
}