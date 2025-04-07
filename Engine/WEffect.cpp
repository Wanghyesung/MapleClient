#include "WEffect.h"
#include "WAnimator.h"
#include "WResources.h"
#include "WObject.h"
#include "WRenderer.h"

namespace W
{
	Effect::Effect():
		m_pOwner(nullptr),
		m_iDir(1)
	{

		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"effectMater", pMater);

		mr->SetMaterial(pMater);
	}

	Effect::~Effect()
	{

	}
	void Effect::Initialize()
	{
		
	}

	void Effect::Update()
	{
	
	}

	void Effect::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}

	void Effect::Render()
	{
		
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = m_iDir * -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Effect::CreateAnimation(std::shared_ptr<Texture> _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, UINT _iColumnLength,
		UINT _iRowLength, Vector2 _vDivisionSize, Vector2 _vOffset, float _fDuration)
	{
		Vector2 vTemLeftTop = _vLeftTop;
		Vector2 vTemSize = _vSize;

		Animator* pAnimator = AddComponent<Animator>();
		m_vOffset = _vOffset;

		pAnimator->Create(GetName() + L"Anim_left", _pAtlas, _vLeftTop, _vSize, _iColumnLength, _vDivisionSize, Vector2::Zero, _fDuration);
		_vLeftTop.x = _pAtlas->GetWidth() - _vSize.x;
		_vSize.x *= -1;
		pAnimator->Create(GetName() + L"Anim_right", _pAtlas, _vLeftTop, _vSize, _iColumnLength, _vDivisionSize, Vector2::Zero, _fDuration);

		for (int i = 1; i < _iRowLength; ++i)
		{
			_vLeftTop = vTemLeftTop;
			_vSize = vTemSize;

			_vLeftTop.y = i * _vSize.y;

			pAnimator->FindAnimation(GetName() + L"Anim_left")->Create(GetName() + L"Anim_left", _pAtlas, _vLeftTop,
				_vSize, _iColumnLength, _vDivisionSize, Vector2::Zero, _fDuration);

			_vLeftTop.x = _pAtlas->GetWidth() - _vSize.x;
			_vSize.x *= -1;

			pAnimator->FindAnimation(GetName() + L"Anim_right")->Create(GetName() + L"Anim_right", _pAtlas, _vLeftTop,
				_vSize, _iColumnLength, _vDivisionSize, Vector2::Zero, _fDuration);
		}

	}
	void Effect::StartEffect(int _iDir)
	{
		m_iDir = _iDir;
		
		Transform* pTr = GetComponent<Transform>();
		Vector3 vPosition;
		if (m_pOwner)
			vPosition = m_pOwner->GetComponent<Transform>()->GetPosition();
		else
			vPosition = pTr->GetPosition();

		//vPosition.x -= (m_vOffset.x * m_iDir);
		//vPosition.y += m_vOffset.y;
		pTr->SetPosition(vPosition);

		std::wstring strDir = _iDir > 0 ? L"_right" : L"_left";
		GetComponent<Animator>()->Play(GetName() + L"Anim" + strDir, true);
	}


}