#pragma once
#include "WComponent.h"
#include "WAnimation.h"

namespace W
{
	class Animator : public Component
	{
	public:
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

		Animator();
		virtual ~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& _strName,
			std::shared_ptr<graphics::Texture> _pAtlas,
			Vector2 _vLeftTop,
			Vector2 _vSize,
			UINT _iColumnLength,
			Vector2 _vDivisionSize,
			Vector2 _vOffset = Vector2::Zero,
			float _fDuration = 0.3f
		);


		Animation* FindAnimation(const std::wstring& _strName);
		Events* FindEvents(const std::wstring& _strName);
		void Play(const std::wstring& _strName, bool _bLoop);
		void Stop(bool _bStop) { m_bStop = _bStop; }
		bool IsStop() { return m_bStop; }
		void Binds();

		std::function<void()>& StartEvent(const std::wstring _strKey);
		std::function<void()>& CompleteEvent(const std::wstring _strKey);
		std::function<void()>& EndEvent(const std::wstring _strKey);

		Animation* GetActiveAnimation() { return m_pActiveAnimation; }

	private:
		std::map<std::wstring, Animation*> m_mapAnimation;
		std::map<std::wstring, Events*> m_mapEvent;
		Animation* m_pActiveAnimation;

		bool m_bLoop;
		bool m_bStop;
	};
}


