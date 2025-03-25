#include "WComponent.h"

namespace W
{
	Component::Component(eComponentType _eType) :
		m_eType(_eType)
	{
	}
	Component::Component(const Component& _pOrigin) :
		m_eType(_pOrigin.m_eType),
		m_pOwner(nullptr)
	{
	}
	Component::~Component()
	{

	}
	void Component::Initialize()
	{

	}
	void Component::Update()
	{

	}
	void Component::LateUpdate()
	{

	}

	void Component::Render()
	{

	}
}