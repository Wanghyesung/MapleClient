#pragma once
#include "WSkillState.h"
namespace W
{
	class SkillQuad : public SkillState
	{
	public:
		SkillQuad();
		virtual ~SkillQuad();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_quad();
		void create_quad();

	private:
		UINT m_iCallStack;

		UINT m_iCreateCnt;
		UINT m_iMaxCnt;
	};
}
