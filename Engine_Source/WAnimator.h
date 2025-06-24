#pragma once
#include "WComponent.h"
#include "WAnimation.h"

namespace W
{
	struct Event
	{
		void operator=(std::function<void()> _func)
		{
			m_Event = std::move(_func);
		}

		void operator()()
		{
			if (m_Event)
				m_Event();
		}
		std::function<void()> m_Event;
	};

	struct Events
	{
		Event tStartEvent;
		Event tCompleteEvent;
		Event tEndEvent;
	};

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
			Vector2 _vAtlasSize = Vector2::Zero,
			float _fDuration = 0.3f
		);

		Animation* FindAnimation(const std::wstring& _strName);

		void Play(const std::wstring& _strName, int _iIndex);
		void PlayClientAnimation(const std::wstring& _strName, bool _bLoop);
		void Stop(bool _bStop) { m_bStop = _bStop; }

		bool IsStop() { return m_bStop; }
		void Binds();
	
		bool IsClientAnimation() { return m_bClientAnim; }
		void SetClientAnimation(bool _bClientAnim) { m_bClientAnim = _bClientAnim; }

		void SetTexture(const wstring& _strName, shared_ptr<Texture> _pTexture);
		void SetTexture(shared_ptr<Texture> _pTexture);
		Animation* GetActiveAnimation() { return m_pActiveAnimation; }

		Events* FindEvents(const std::wstring& _strName);
		std::function<void()>& StartEvent(const std::wstring _strKey);
		std::function<void()>& CompleteEvent(const std::wstring _strKey);
		std::function<void()>& EndEvent(const std::wstring _strKey);

		void Clear();

	private:
		std::map<wstring, Animation*> m_mapAnimtion;
		std::map<std::wstring, Events*> m_mapEvent;
		Animation* m_pActiveAnimation;

		//클라 전용 애니메이션
		bool m_bClientAnim;

		bool m_bLoop;
		bool m_bStop;

	};
}


