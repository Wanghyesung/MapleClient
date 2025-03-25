#pragma once

namespace W
{
	class SkillState;
	class PlayerSkill 
	{
	public:
		PlayerSkill();
		~PlayerSkill();

		void Update();
		void Initialize();

		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
		Player* GetPlayer() { return m_pPlayer; }

		bool IsSkillOn() { return m_bSkillOn; }
	private:

		SkillState* m_pActiveSkill;

		Player* m_pPlayer;
		bool m_bSkillOn;

		friend class SkillManager;
	};
	
}


