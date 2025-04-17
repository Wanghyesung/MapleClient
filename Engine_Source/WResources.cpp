#include "WResources.h"

namespace W
{
	RWLock Resources::m_lock = {};
	std::mutex Resources::m_mutex = {};
	std::map<std::wstring, std::shared_ptr<Resource>> Resources::m_mapResources;
}