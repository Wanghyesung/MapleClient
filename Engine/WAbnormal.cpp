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

}