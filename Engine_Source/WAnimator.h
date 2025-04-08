#pragma once
#include "WComponent.h"
#include "WAnimation.h"

namespace W
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& _strName,
			std::shared_ptr<Texture> _pAtlas,
			Vector2 _vLeftTop,
			Vector2 _vSize,
			UINT _iColumnLength,
			Vector2 _vDivisionSize,
			Vector2 _vOffset = Vector2::Zero,
			float _fDuration = 0.3f
		);


		Animation* FindAnimation(const std::wstring& _strName);
		void Play(const std::wstring& _strName, int _iIndex);
		void Stop(bool _bStop) { m_bStop = _bStop; }
		bool IsStop() { return m_bStop; }
		void Binds();

	
		Animation* GetActiveAnimation() { return m_pActiveAnimation; }

	private:
		std::map<std::wstring, Animation*> m_mapAnimation;
		Animation* m_pActiveAnimation;

		bool m_bLoop;
		bool m_bStop;
	};
}


