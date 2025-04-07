#pragma once
#include "WResource.h"
#include "WTexture.h"

namespace W
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 vLeftTop;
			Vector2 vSize;
			Vector2 vOffset;
			Vector2 vAtlasSize;
			float fDuration;

			Sprite() :
				vLeftTop(Vector2::Zero),
				vSize(Vector2::Zero),
				vOffset(Vector2::Zero),
				vAtlasSize(Vector2::Zero),
				fDuration(0.f)
			{

			}

		};
		Animation();
		virtual ~Animation();

		virtual HRESULT Load(const std::wstring& _strPath) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring _strName,
			std::shared_ptr<graphics::Texture> _pAtlas,
			Vector2 _vLeftTop,
			Vector2 _vSize,
			UINT _iColumnLength,
			Vector2 _vDivisionSize,
			Vector2 _vOffset = Vector2::Zero,
			float _fDuration = 0.f
		);

		void Binds();

		int GetCurIndex() { return m_iIndex; }
		void SetIndex(int _iIndex) { m_iIndex = _iIndex; }

		void SetAnimator(Animator* _pAnim) { m_pAnimator = _pAnim; }
	private:
		std::weak_ptr<graphics::Texture> m_wpAtlas;
		Animator* m_pAnimator;
		std::vector<Sprite> m_vecSprites;
		int m_iIndex;
	};
}


