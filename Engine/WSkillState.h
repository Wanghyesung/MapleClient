#pragma once
#include "WPlayer.h"
#include "WPlayerSkill.h"
#include "WInfo.h"
#include "WAudioSource.h"
namespace W
{
	class Effect;
	class PlayerAttackObject;
	class SkillState
	{
	public:
		SkillState();
		~SkillState();

		virtual void Enter();
		virtual void Exit();

		virtual void Update();
		virtual void Initialize();

		void SetSkillType(Player::ePlayerSkill _eSkill) { m_eSkill = _eSkill; }
		Player::ePlayerSkill GetPlayerSkill() { return m_eSkill; }


		void SetStateName(const std::wstring& _strName) { m_strStateName = _strName; }
		const std::wstring& GetStateName() { return m_strStateName; }

		void SetOnwer(PlayerSkill* _pSkill) { m_pOwner = _pSkill; }
		PlayerSkill* GetSkill() { return m_pOwner; }

		const tSkillTime& GetCoolTime() { return m_tSKillTime; }
		void SetCoolTime(const tSkillTime& _tTime) { m_tSKillTime = _tTime; }

		Player* GetPlayer();

		void SetSound(std::shared_ptr<AudioClip> clip, bool _bLoop);
		void StartSound();
		void EndSound();

	protected:
		Effect* CreateEffet(std::shared_ptr<Texture> _pAtlas, std::wstring _strName, Vector2 _vLeftTop, Vector2 _vSize, 
			UINT _iColumnLength, UINT _iRowLength, Vector2 _vDivisionSize, Vector2 _vOffset, float _fDuration);
		void StartEffect(Effect* _pEffect);

		void AddDamage(PlayerAttackObject* _pAttackObject);

	protected:
		std::shared_ptr<Texture> m_pEffectAtlas;
		std::shared_ptr<Texture> m_pHitEffectAtlas;

	private:
		std::wstring m_strStateName;
		Player::ePlayerSkill m_eSkill;

		PlayerSkill* m_pOwner;

		//기본 사운드
		std::shared_ptr<AudioClip> m_pSoundClip;

		tSkillTime m_tSKillTime;
		float m_fAddDamage;
	};
}


