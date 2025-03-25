#include "WInputObject.h"
#include "WAnimator.h"
#include "WInputBackground.h"
#include "WRenderer.h"
#include "WInput.h"
namespace W
{
	InputObject::InputObject(eKeyCode _eKeyCode):
		m_eKeyCode(_eKeyCode),
		m_pOwner(nullptr),
		m_bRender(true),
		m_bActive(true)
	{
		std::wstring strDir = L"";
		switch (m_eKeyCode)
		{
		case W::eKeyCode::UP:
			strDir = L"up";
			break;
		case W::eKeyCode::DOWN:
			strDir = L"down";
			break;
		case W::eKeyCode::LEFT:
			strDir = L"left";
			break;
		case W::eKeyCode::RIGHT:
			strDir = L"right";
			break;
		}
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"InputMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Input"+ strDir);
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"clear", pAtlas, Vector2(0.0f, 0.0f), Vector2(80.f, 79.0f), 7, Vector2(100.f, 100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"failed", pAtlas, Vector2(0.0f, 79.0f), Vector2(89.f, 77.0f), 4, Vector2(100.f, 100.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"failed") = std::bind(&InputObject::failed, this);
		pAnim->CompleteEvent(L"clear") = std::bind(&InputObject::clear, this);

		pAnim->Play(L"clear", true);
		pAnim->Stop(true);
	}

	InputObject::~InputObject()
	{

	}

	void InputObject::Initialize()
	{

	}

	void InputObject::Update()
	{
		if (!m_bRender)
			return;

		if (m_bActive)
			check();

		GameObject::Update();
	}

	void InputObject::LateUpdate()
	{
		if (!m_bRender)
			return;

		GameObject::LateUpdate();
	}

	void InputObject::Render()
	{
		if (!m_bRender)
			return;

		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void InputObject::SetClear(bool _bClear)
	{
		std::wstring strAnim = L"";
		strAnim = _bClear == true ? L"clear" : L"failed";
		GetComponent<Animator>()->Stop(false);
		GetComponent<Animator>()->Play(strAnim, true);
	}

	void InputObject::check()
	{
		if (m_pOwner->GetCurIndex() != m_iIndex)
		{
			GameObject::Update();
			return;
		}
		bool m_bInput = false;
		bool m_bClear = false;

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			m_bInput = true;

			if (m_eKeyCode == eKeyCode::RIGHT)
				m_bClear = true;
		}

		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			m_bInput = true;

			if (m_eKeyCode == eKeyCode::LEFT)
				m_bClear = true;
		}

		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			m_bInput = true;

			if (m_eKeyCode == eKeyCode::UP)
				m_bClear = true;
		}

		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			m_bInput = true;

			if (m_eKeyCode == eKeyCode::DOWN)
				m_bClear = true;
		}

		//´­·¶´Ù¸é
		if (m_bInput)
		{
			if (m_bClear)
				m_pOwner->Next();

			SetClear(m_bClear);

			m_bActive = false;
		}

	}

	void InputObject::failed()
	{
		m_pOwner->Failed();
	}

	void InputObject::clear()
	{
		m_bRender = false;
	}
}