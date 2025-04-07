#include "WPathManager.h"
#include "Engine.h"

namespace W
{
	wchar_t		PathManager::m_szContentPath[256] = {};
	void PathManager::Initialize()
	{
		GetCurrentDirectory(256, m_szContentPath);

		// 상위폴더로 감
		int iLen = (int)wcslen(m_szContentPath);

		for (int i = iLen - 1; i >= 0; --i)
		{
			if (L'\\' == m_szContentPath[i])
			{
				m_szContentPath[i] = 0;
				break;
			}
		}
		//wcscat_s(m_szContentPath, L"\\bin\\content\\");
	}
}

