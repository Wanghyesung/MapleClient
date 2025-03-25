#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillLuck : public SkillState
	{
	public:
		SkillLuck();
		virtual ~SkillLuck();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_luck();
		void create_luck();

	private:
		UINT m_iCallStack;

		UINT m_iCreateCnt;
		UINT m_iMaxCnt;
	};
}


