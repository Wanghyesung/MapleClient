#include "WAbnormal.h"
#include "WTime.h"
#include "WPlayer.h"


namespace W
{
	Abnormal::Abnormal() :
		m_pTarget(nullptr),
		m_bRender(false),
		m_bRenderPosUp(true),
		m_fDeleteTime(0.f),
		m_fCurTime(0.f)
	{

	}
	Abnormal::~Abnormal()
	{

	}
	void Abnormal::Initialize()
	{
	}
	void Abnormal::Update()
	{	
		
	}
	void Abnormal::LateUpdate()
	{	
		

		GameObject::LateUpdate();
	}
	void Abnormal::Restore()
	{

	}
	void Abnormal::Render()
	{	
		GameObject::Render();
	}

	void Abnormal::UpdateState(const wstring& _strStateName, int _iState)
	{
		UCHAR cDir = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;
	}

}