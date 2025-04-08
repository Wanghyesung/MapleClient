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
		Animator* pAnim = nullptr;
		std::vector<std::wstring> vecDir = { L"up" ,L"down" ,L"left" , L"right" };
		for (std::wstring& strDir : vecDir)
		{
			std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Input" + strDir);
			pAnim = AddComponent<Animator>();
			pAnim->Create(L"clear", pAtlas, Vector2(0.0f, 0.0f), Vector2(80.f, 79.0f), 7, Vector2(100.f, 100.f), Vector2::Zero, 0.15f);
			pAnim->Create(L"failed", pAtlas, Vector2(0.0f, 79.0f), Vector2(89.f, 77.0f), 4, Vector2(100.f, 100.f), Vector2::Zero, 0.15f);
		}
		
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"InputMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

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
}