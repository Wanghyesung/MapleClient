#include "WAnimationManager.h"

namespace W
{
	std::map<std::wstring, std::vector<Sprite>>AnimationManager::m_mapSprite = {};
	
	const vector<Sprite>& AnimationManager::FindAnimtionSprtie(const wstring& _strName)
	{
		auto iter = m_mapSprite.find(_strName);
		if (iter == m_mapSprite.end())
			return {};

		return iter->second;
	}

	void AnimationManager::AddAnimationSprtie(Sprite& _pSprtie)
	{
		auto& vecSprtie = m_mapSprite[_pSprtie.GetKey()];  
		vecSprtie.push_back(_pSprtie);
	}
}

