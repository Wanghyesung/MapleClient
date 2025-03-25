#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillLoad : public SkillState
	{
	public:
		SkillLoad();
		virtual ~SkillLoad();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_load();
		void create_load();

	private:
		bool m_bCreate;

	};
}


