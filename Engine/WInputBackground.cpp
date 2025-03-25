#include "WInputBackground.h"
#include "WResources.h"
#include "WObject.h"
#include "WGroggy.h"
#include "WInputObject.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WSceneManger.h"

namespace W
{
	InputBackground::InputBackground():
		m_pOwner(nullptr),
		m_vecInput{},
		m_iCurIndex(0)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"DefenseMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainInputBack");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(2.5f * 1.8f, 2.5f * 0.5f, 0.f);
	}
	InputBackground::~InputBackground()
	{
		for (int i = 0; i < m_vecInput.size(); ++i)
		{
			
			delete m_vecInput[i];
			m_vecInput[i] = nullptr;
		}
	}
	void InputBackground::Initialize()
	{
		Vector3 vTargetPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		vTargetPos.y += 1.f;
		vTargetPos.z += 1.f;

		UINT iIndex = 0;
		GetComponent<Transform>()->SetPosition(vTargetPos);
		for (int i = -2; i < 3; ++i)
		{
			UINT iStart = (UINT)eKeyCode::UP;
			UINT iEnd = (UINT)eKeyCode::RIGHT;

			std::random_device rDiv;
			std::mt19937 en(rDiv());
			std::uniform_int_distribution<int> num(iStart, iEnd);
			int iNum = (int)num(en);
		
			InputObject* pObj = new InputObject((eKeyCode)iNum);
			pObj->SetOwner(this);
			pObj->SetIndex(iIndex);

			float x = vTargetPos.x + (i * 0.8f);
			Vector3 vPos = Vector3(x, vTargetPos.y, vTargetPos.z - 0.2f);
			pObj->GetComponent<Transform>()->SetPosition(vPos);

			m_vecInput.push_back(pObj);
			++iIndex;
		}
	}
	void InputBackground::Update()
	{
		if(m_bNext)
			next_button();
	
		GameObject::Update();

		for (int i = 0; i < m_vecInput.size(); ++i)
		{
			
			m_vecInput[i]->Update();
		}

	}
	void InputBackground::LateUpdate()
	{

		GameObject::LateUpdate();

		for (int i = 0; i < m_vecInput.size(); ++i)
		{

			m_vecInput[i]->LateUpdate();
		}

	}
	void InputBackground::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();

		for (int i = 0; i < m_vecInput.size(); ++i)
		{
			m_vecInput[i]->Render();
		}
	}

	void InputBackground::Failed()
	{
		object::Destroy(this);
		dynamic_cast<Groggy*>(m_pOwner)->SetTime(12.f);
	}

	void InputBackground::Next()
	{
		m_bNext = true;
	}

	void InputBackground::next_button()
	{
		++m_iCurIndex;
		if (m_iCurIndex >= m_vecInput.size())
		{
			dynamic_cast<Groggy*>(m_pOwner)->SetTime(0.f);
			object::Destroy(this);
		}

		m_bNext = false;
	}
}