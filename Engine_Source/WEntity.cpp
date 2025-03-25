#include "WEntity.h"

namespace W
{
	Entity::Entity()
	{

	}
	Entity::Entity(const Entity& _pOrigin):
		m_strName(_pOrigin.m_strName)
	{
	}
	Entity::~Entity()
	{

	}
}