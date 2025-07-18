#pragma once
#include "WResource.h"
#include "WTexture.h"

namespace W
{
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

	class Animator;
	class Animation : public Resource
	{
	public:
		Animation();
		virtual ~Animation();

		void SetTexture(shared_ptr<Texture> _pTexture) { m_wpAtlas = _pTexture; }
		virtual HRESULT Load(const std::wstring& _strPath) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();

		void Create(const std::wstring& _strName,
			std::shared_ptr<Texture> _pAtlas,
			Vector2 _vLeftTop,
			Vector2 _vSize,
			UINT _iColumnLength,
			Vector2 _vDivisionSize,
			Vector2 _vOffset = Vector2::Zero,
			Vector2 _vAtlasSize = Vector2::Zero,
			float _fDuration = 0.3f
		);

		void Reset();

		void Binds();
		void Clear();

		int GetCurIndex() { return m_iIndex; }
		void SetIndex(int _iIndex);

		void SetAnimator(Animator* _pAnim) { m_pAnimator = _pAnim; }
		bool IsComplete() { return m_bComplete; }
	private:
		std::weak_ptr<Texture> m_wpAtlas;
		Animator* m_pAnimator;
	
		Vector2 m_vAtlasSize;

		vector<Sprite> m_vecSprite;

		int m_iIndex;
		float m_fTime;

		bool m_bComplete;
	};
}


