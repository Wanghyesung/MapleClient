#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillShadow : public SkillState
	{
	public:
		SkillShadow();
		virtual ~SkillShadow();

		virtual void Enter()override;
		virtual void Exit()override;

		virtual void Update()override;
		virtual void Initialize()override;

	private:
		void activeskill_shadow();
		void create_shadow();

	private:
		//std::shared_ptr<Texture> m_pEffectShadow;

		bool m_bCreate;
	};
}
