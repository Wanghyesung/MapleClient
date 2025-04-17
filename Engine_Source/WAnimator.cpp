#include "WAnimator.h"

namespace W
{
	Animator::Animator() :
		Component(eComponentType::Animator),
		m_bStop(false),
		m_pActiveAnimation(nullptr)
	{

	}
	Animator::~Animator()
	{
		for (auto& iter : m_mapAnimation)
		{
			delete iter.second;
			iter.second = nullptr;
		}

	}
	void Animator::Initialize()
	{

	}
	void Animator::Update()
	{
		
	}
	void Animator::LateUpdate()
	{
	
	}
	void Animator::Render()
	{

	}
	void Animator::Create(const std::wstring& _strName, std::shared_ptr<Texture> _pAtlas, Vector2 _vLeftTop, 
		Vector2 _vSize, UINT _iColumnLength, Vector2 _vDivisionSize, Vector2 _vOffset, float _fDuration)
	{
		Animation* pAnimation = FindAnimation(_strName);

		if (pAnimation != nullptr)
			return;

		pAnimation = new Animation();
		pAnimation->SetKey(_strName);

		pAnimation->Create(_strName,
			_pAtlas, _vLeftTop, _vSize, _iColumnLength,  _vDivisionSize, _vOffset, _fDuration);

		m_mapAnimation.insert(std::make_pair(_strName, pAnimation));
		
		pAnimation->SetAnimator(this);
	}
	Animation* Animator::FindAnimation(const std::wstring& _strName)
	{
		std::map<std::wstring, Animation*>::iterator iter =
			m_mapAnimation.find(_strName);

		if (iter == m_mapAnimation.end())
			return nullptr;
		return iter->second;
		
	}
	
	void Animator::Play(const std::wstring& _strName, int _iIndex)
	{
		Animation* pAnimation = FindAnimation(_strName);

		if (pAnimation)
		{
			m_pActiveAnimation = pAnimation;

			m_pActiveAnimation->SetIndex(_iIndex);
		}
	}
	void Animator::Binds()
	{
		if (m_pActiveAnimation == nullptr)
			return;
		
		m_pActiveAnimation->Binds();
	}
	
}