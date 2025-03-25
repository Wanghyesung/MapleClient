#pragma once
#include "WSkillState.h"

namespace W
{
	class SkillBlast : public SkillState
	{
	public:
		SkillBlast();
		virtual ~SkillBlast();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_blast();
		void create_blast(const math::Vector3& _vPosition);

		void exit();
	private:
		bool m_bCreate;

		friend class SkillManager;
	};
}


