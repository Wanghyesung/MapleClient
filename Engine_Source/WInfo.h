#pragma once

namespace W
{
	enum class eAttackType
	{
		Knockback,
		SuperKnockback,
		End,
	};

	struct tHitInfo
	{
		//맞은 공격 타입
		eAttackType eAttType;

		float fHitDir; //맞는 방향
		float fHitRcnt;//맞으면 날라갈 양
		float fHitUpperRcnt; //맞으면 띄어질 양
		float fHitRigidityTime; //경직 시간
	};

	struct tAttackInfo
	{
		tAttackInfo():
			fAttack(5.f),
			fMaxAttack(5.f),
			fDex(10.f),
			iDamageCount(0),
			eAttType(eAttackType::Knockback)
		{}

		//기본 공격력, dex, 데미지
		float fAttack;
		float fMaxAttack;
		float fDex;
		float fAttackDamage; //데미지

		float fAttRcnt;//맞으면 날라갈 양 X
		float fAttUpperRcnt; //맞으면 띄어질 양 Y
		float fAttRigidityTime; //경직 시간

		//폰트 나오는 갯수
		UINT iDamageCount;
		eAttackType eAttType;
	};

	struct tObjectInfo
	{
		tObjectInfo()
		{
			fHP = 100.f;
			fMaxHP = fHP;
			fMP = 100.f;
			fMaxMP = fMP;
			fDefense = 1.f;
		}

		float fMaxHP;
		float fHP;
		float fMaxMP;
		float fMP;
		float fEXP;
		float fSpeed;
		float fJumpValue;
		float fDefense;
	};

	struct tSkillTime
	{
		float fCurTime;
		float fCoolTime;
		float fActiveTime;
		float fCurActiveTime;
	};

	

	struct tMonsterAttack
	{
		tMonsterAttack():
			vOffset(math::Vector2::Zero)
		{
			bSkill = false;
			tTime.fCoolTime = 4;
			tTime.fCurTime = 0;

			tAttackInfo.fAttRigidityTime = 0.f;
			tAttackInfo.fAttRcnt = 1.2f;
			tAttackInfo.fAttUpperRcnt = 1.5f;
		}
		tSkillTime tTime;

		tAttackInfo tAttackInfo;

		std::function<void()> pFunction;

		math::Vector2 vScale;
		math::Vector2 vOffset;
		math::Vector3 vPosition;
		math::Vector3 vRoatate;

		//공격시작 프레임 끝나는 프레임
		UINT iStartFrame;
		UINT iEndFrame;

		//스킬(ex : 소환 오브젝트)
		bool bSkill;
	};
}