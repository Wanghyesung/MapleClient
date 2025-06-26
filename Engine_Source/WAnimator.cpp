#include "WAnimator.h"
#include "WResources.h"
#include "WGameObject.h"
namespace W
{

	Animator::Animator() :
		Component(eComponentType::Animator),
		m_bStop(false),
		m_bClientAnim(false),
		m_bLoop(false),
		m_pActiveAnimation(nullptr)
	{
		
	}
	Animator::~Animator()
	{
		for (auto& iter : m_mapAnimtion)
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
		if (m_bClientAnim == false || m_pActiveAnimation == nullptr)
			return;

		if (m_bStop)
			return;	

		if (m_pActiveAnimation->IsComplete())
		{
			Events* pEvents =
				FindEvents(m_pActiveAnimation->GetKey());

			if (pEvents)
				pEvents->tCompleteEvent();

			if (m_bLoop)
				m_pActiveAnimation->Reset();
			else
				m_bClientAnim = false;
		}

		m_pActiveAnimation->Update();
	}
	void Animator::LateUpdate()
	{
		
	}
	void Animator::Render()
	{

	}
	void Animator::Create(const std::wstring& _strName, std::shared_ptr<Texture> _pAtlas, Vector2 _vLeftTop, 
		Vector2 _vSize, UINT _iColumnLength, Vector2 _vDivisionSize, Vector2 _vOffset, Vector2 _vAtlasSize, float _fDuration)
	{
		Animation* pAnimation = FindAnimation(_strName);
		
		if (pAnimation != nullptr)
			return;

		pAnimation = new Animation();
		pAnimation->SetKey(_strName);

		pAnimation->Create(_strName,
			_pAtlas, _vLeftTop, _vSize, _iColumnLength, _vDivisionSize, _vOffset, _vAtlasSize, _fDuration);
		

		m_mapAnimtion.insert(make_pair(_strName, pAnimation));

		Events* tEvents = new Events();
		m_mapEvent.insert(std::make_pair(_strName, tEvents));

		pAnimation->SetAnimator(this);
	}
	
	Animation* Animator::FindAnimation(const std::wstring& _strName)
	{
		//리소스 매니저에서 락을 걸기 부담 따로 보관
		auto iter = m_mapAnimtion.find(_strName);
		if (iter == m_mapAnimtion.end())
			return nullptr;

		return iter->second;
	}

	
	void Animator::Play(const std::wstring& _strName, int _iIndex)
	{
		m_bClientAnim = false;

		auto iter = m_mapAnimtion.find(_strName);
		if (iter == m_mapAnimtion.end())
			assert(nullptr);

		Animation* pAnimation = iter->second;

		if (pAnimation)
		{
			m_pActiveAnimation = pAnimation;
			m_pActiveAnimation->SetIndex(_iIndex);
		}
	}

	void Animator::PlayClientAnimation(const std::wstring& _strName, bool _bLoop)
	{
		Animation* pPrevAnimation = m_pActiveAnimation;

		Events* pEvents;
		if (pPrevAnimation != nullptr)
		{
			pEvents = FindEvents(pPrevAnimation->GetKey());
			if (pEvents)
				pEvents->tEndEvent();
		}

		m_pActiveAnimation = FindAnimation(_strName);

		if (m_pActiveAnimation)
		{
			pEvents = FindEvents(m_pActiveAnimation->GetKey());
			if (pEvents)
				pEvents->tStartEvent();

			m_pActiveAnimation->Reset();

			m_bClientAnim = true;
			m_bLoop = _bLoop;
		}
	}

	void Animator::Binds()
	{
		if (m_pActiveAnimation == nullptr)
			return;
		
		m_pActiveAnimation->Binds();
	}

	void Animator::SetTexture(const wstring& _strName, shared_ptr<Texture> _pTexture)
	{
		auto iter =m_mapAnimtion.find(_strName);
		if (iter == m_mapAnimtion.end())
			return;

		iter->second->SetTexture(_pTexture);
	}

	void Animator::SetTexture(shared_ptr<Texture> _pTexture)
	{
		auto iter = m_mapAnimtion.begin();

		for (iter; iter != m_mapAnimtion.end(); ++iter)
			iter->second->SetTexture(_pTexture);
	}

	void Animator::Clear()
	{
		if (m_pActiveAnimation == nullptr)
			return;

		m_pActiveAnimation->Clear();
	}

	Events* Animator::FindEvents(const std::wstring& _strName)
	{
		std::map<std::wstring, Events*>::iterator iter =
			m_mapEvent.find(_strName);

		if (iter == m_mapEvent.end())
			return nullptr;

		return iter->second;
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