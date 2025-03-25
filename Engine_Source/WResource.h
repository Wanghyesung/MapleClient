#pragma once

#include "Engine.h"

namespace W
{
	class Resource
	{
	public:
		Resource(const enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& _strPath) = 0;

		const std::wstring& GetKey() { return m_strKey; }
		const std::wstring& GetPath() { return m_strPath; }
		void SetKey(const std::wstring& _strKey) { m_strKey = _strKey; }
		void SetPath(const std::wstring& _strPath) { m_strPath = _strPath; }

	private:
		const enums::eResourceType m_eType;
		std::wstring m_strKey;
		std::wstring m_strPath;
	};
}


