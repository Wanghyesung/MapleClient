#include "WAnimator.h"
#include "WResources.h"
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
		auto iter = m_mapAnimtion.begin();
		for (iter; iter != m_mapAnimtion.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
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
		//Resources에서 락을 걸면서 가져오기 부담
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
	
}