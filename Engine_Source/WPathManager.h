#pragma once
namespace W
{
	class PathManager
	{
	public:
		static void Initialize();
		static const wchar_t* GetContentPath() { return m_szContentPath; }

	private:
		static wchar_t		m_szContentPath[256];
	};
}


