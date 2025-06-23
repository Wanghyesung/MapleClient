#pragma once

#include "..\Engine_Source\Engine.h"
#include "..\Engine_Source\WAnimation.h"
namespace W
{
	struct Sprite : public Resource
	{
		Vector2 vLeftTop;
		Vector2 vSize;
		Vector2 vOffset;
		Vector2 vAtlasSize;
		float fDuration;

		Sprite():
			Resource(eResourceType::AnimationSprtie),
			vLeftTop(Vector2::Zero),
			vSize(Vector2::Zero),
			vOffset(Vector2::Zero),
			vAtlasSize(Vector2::Zero),
			fDuration(0.f)
		{

		}
		virtual HRESULT Load(const std::wstring& _strPath) { return S_OK; }
	};

	class AnimationManager
	{
	public:
		static const vector<Sprite>& FindAnimtionSprtie(const wstring& _strName);

		static void AddAnimationSprtie(Sprite& _pSprtie);
	private:
		static std::map<std::wstring, std::vector<Sprite>> m_mapSprite;

	};
}


