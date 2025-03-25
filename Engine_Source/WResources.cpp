#include "WResources.h"

namespace W
{
	std::mutex Resources::m_mutex;
	std::map<std::wstring, std::shared_ptr<Resource>> Resources::m_mapResources;
}