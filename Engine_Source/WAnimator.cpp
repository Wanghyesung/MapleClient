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


		for (auto& iter : m_mapEvent)
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
		if (m_pActiveAnimation == nullptr)
			return;

		if (m_bStop)
			return;

		if (m_pActiveAnimation->IsComplete() && m_bLoop)
		{
			Events* pEvents =
				FindEvents(m_pActiveAnimation->GetKey());

			if (pEvents)
				pEvents->tCompleteEvent();

			m_pActiveAnimation->Reset();
		}

		m_pActiveAnimation->LateUpdate();
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{

	}
	void Animator::Create(const std::wstring& _strName, std::shared_ptr<graphics::Texture> _pAtlas, Vector2 _vLeftTop, 
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

		Events* tEvents = FindEvents(_strName);
		if (tEvents != nullptr)
			return;

		//이벤트당 하나의 events가지기
		tEvents = new Events();
		m_mapEvent.insert(std::make_pair(_strName, tEvents));

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
	Animator::Events* Animator::FindEvents(const std::wstring& _strName)
	{
		std::map<std::wstring, Events*>::iterator iter =
			m_mapEvent.find(_strName);

		if (iter == m_mapEvent.end())
			return nullptr;

		return iter->second;
	}
	void Animator::Play(const std::wstring& _strName, bool _bLoop)
	{
		Animation* pPrevAnimation = m_pActiveAnimation;

		Events* pEvents;
		if (pPrevAnimation != nullptr)
		{
			pEvents = FindEvents(pPrevAnimation->GetKey());
			if (pEvents)
				pEvents->tEndEvent();
		}

		Animation* pAnimation = FindAnimation(_strName);

		if (pAnimation)
			m_pActiveAnimation = pAnimation;

		pEvents = FindEvents(m_pActiveAnimation->GetKey());
		if (pEvents)
			pEvents->tStartEvent();
		

		m_bLoop = _bLoop;
		m_pActiveAnimation->Reset();
	}
	void Animator::Binds()
	{
		if (m_pActiveAnimation == nullptr)
			return;
		
		m_pActiveAnimation->Binds();
	}
	std::function<void()>& Animator::StartEvent(const std::wstring _strKey)
	{
		Events* pEvents = FindEvents(_strKey);

		return pEvents->tStartEvent.m_Event;
		
	}
	std::function<void()>& Animator::CompleteEvent(const std::wstring _strKey)
	{
		Events* pEvents = FindEvents(_strKey);

		return pEvents->tCompleteEvent.m_Event;
	}
	std::function<void()>& Animator::EndEvent(const std::wstring _strKey)
	{
		Events* pEvents = FindEvents(_strKey);

		return pEvents->tEndEvent.m_Event;
	}
}