#include "WGameObjectManager.h"
#include "WGameObject.h"
#include "ObjectHeader.h"

#define REGISTER_OBJECT_FACTORY(name, id)               \
{                                                       \
    name::SetCreateID(id);                              \
    m_hashObject[id] = []() -> GameObject* {            \
        return new name();                              \
    };                                                  \
};


namespace W
{
	std::unordered_map <UINT, std::function<GameObject* ()>> GameObjectManager::m_hashObject = {};

	void GameObjectManager::Initialize()
	{
		REGISTER_OBJECT_FACTORY(GameObject			 , 0  )
		REGISTER_OBJECT_FACTORY(Abnormal			 , 1  )
		REGISTER_OBJECT_FACTORY(Ariel				 , 2  )
		REGISTER_OBJECT_FACTORY(ArielLaser			 , 3  )
		REGISTER_OBJECT_FACTORY(ArielStone			 , 4  )
		REGISTER_OBJECT_FACTORY(AttackUp			 , 5  )
		REGISTER_OBJECT_FACTORY(AutoShuriken		 , 6  )
		REGISTER_OBJECT_FACTORY(Aven				 , 7  )
		REGISTER_OBJECT_FACTORY(Blast				 , 8  )
		REGISTER_OBJECT_FACTORY(Cage				 , 9  )
		REGISTER_OBJECT_FACTORY(CloneMegnus			 , 10 )
		REGISTER_OBJECT_FACTORY(Confusion			 , 11 )
		REGISTER_OBJECT_FACTORY(DefenseUp			 , 12 )
		REGISTER_OBJECT_FACTORY(Demian				 , 13 )
		REGISTER_OBJECT_FACTORY(DemianCircle		 , 14 )
		REGISTER_OBJECT_FACTORY(DemianEntireAttack	 , 15 )
		REGISTER_OBJECT_FACTORY(DemianExplode		 , 16 )
		REGISTER_OBJECT_FACTORY(DemianFire0			 , 17 )
		REGISTER_OBJECT_FACTORY(DemianFire1			 , 18 )
		REGISTER_OBJECT_FACTORY(DemianFire2			 , 19 )
		REGISTER_OBJECT_FACTORY(DemianKeyAttack		 , 20 )
		REGISTER_OBJECT_FACTORY(DemianPhase2		 , 21 )
		REGISTER_OBJECT_FACTORY(DemianSpear0		 , 22 )
		REGISTER_OBJECT_FACTORY(DemianSpear1		 , 23 )
		REGISTER_OBJECT_FACTORY(DemianSword			 , 24 )
		REGISTER_OBJECT_FACTORY(DemianVine			 , 25 )
		REGISTER_OBJECT_FACTORY(Effect				 , 26 )
		REGISTER_OBJECT_FACTORY(Eyes				 , 27 )
		REGISTER_OBJECT_FACTORY(Faint				 , 28 )
		REGISTER_OBJECT_FACTORY(Fire				 , 29 )
		REGISTER_OBJECT_FACTORY(Groggy				 , 30 )
		REGISTER_OBJECT_FACTORY(Ground				 , 31 )
		REGISTER_OBJECT_FACTORY(Horntail			 , 32 )
		REGISTER_OBJECT_FACTORY(HorntailHeadA		 , 33 )
		REGISTER_OBJECT_FACTORY(HorntailHeadB		 , 34 )
		REGISTER_OBJECT_FACTORY(HorntailHeadC		 , 35 )
		REGISTER_OBJECT_FACTORY(HorntailLeftHand	 , 36 )
		REGISTER_OBJECT_FACTORY(HorntailLeg			 , 37 )
		REGISTER_OBJECT_FACTORY(HorntailRightHand	 , 38 )
		REGISTER_OBJECT_FACTORY(HorntailTail		 , 39 )
		REGISTER_OBJECT_FACTORY(HorntailWing		 , 40 )
		REGISTER_OBJECT_FACTORY(Ice					 , 41 )
		REGISTER_OBJECT_FACTORY(Ignore				 , 42 )
		REGISTER_OBJECT_FACTORY(InputBackground		 , 43 )
		REGISTER_OBJECT_FACTORY(InputObject			 , 44 )
		REGISTER_OBJECT_FACTORY(Jenesis				 , 45 )
		REGISTER_OBJECT_FACTORY(Ladder				 , 46 )
		REGISTER_OBJECT_FACTORY(Load				 , 47 )
		REGISTER_OBJECT_FACTORY(Megnus				 , 48 )
		REGISTER_OBJECT_FACTORY(MegnusAttack		 , 49 )
		REGISTER_OBJECT_FACTORY(MegnusStone			 , 50 )
		REGISTER_OBJECT_FACTORY(MiniBean			 , 51 )
		REGISTER_OBJECT_FACTORY(MiniBeanAttack		 , 52 )
		REGISTER_OBJECT_FACTORY(MobZone				 , 53 )
		REGISTER_OBJECT_FACTORY(Monster				 , 54 )
		REGISTER_OBJECT_FACTORY(MonsterAttackObject  , 55 )
		REGISTER_OBJECT_FACTORY(MonsterBackHP		 , 56 )
		REGISTER_OBJECT_FACTORY(MonsterHP			 , 57 )
		REGISTER_OBJECT_FACTORY(MonsterMoveAttack	 , 58 )
		REGISTER_OBJECT_FACTORY(Munin				 , 59 )
		REGISTER_OBJECT_FACTORY(MuninStone			 , 60 )
		REGISTER_OBJECT_FACTORY(PinkBean			 , 61 )
		REGISTER_OBJECT_FACTORY(PinkBeanStone		 , 62 )
		REGISTER_OBJECT_FACTORY(Player				 , 63 )
		REGISTER_OBJECT_FACTORY(PlayerArm			 , 64 )
		REGISTER_OBJECT_FACTORY(PlayerAttackObject	 , 65 )
		REGISTER_OBJECT_FACTORY(PlayerBody			 , 66 )
		REGISTER_OBJECT_FACTORY(PlayerBottom		 , 67 )
		REGISTER_OBJECT_FACTORY(PlayerHair			 , 68 )
		REGISTER_OBJECT_FACTORY(PlayerHat			 , 69 )
		REGISTER_OBJECT_FACTORY(PlayerHead			 , 70 )
		REGISTER_OBJECT_FACTORY(PlayerShoes			 , 71 )
		REGISTER_OBJECT_FACTORY(PlayerTop			 , 72 )
		REGISTER_OBJECT_FACTORY(PlayerWeapon		 , 73 )
		REGISTER_OBJECT_FACTORY(PullObject			 , 74 )
		REGISTER_OBJECT_FACTORY(Reflex				 , 75 )
		REGISTER_OBJECT_FACTORY(Rex					 , 76 )
		REGISTER_OBJECT_FACTORY(RexThunder			 , 77 )
		REGISTER_OBJECT_FACTORY(RoccatBean			 , 78 )
		REGISTER_OBJECT_FACTORY(SealSkill			 , 79 )
		REGISTER_OBJECT_FACTORY(Shadow				 , 80 )
		REGISTER_OBJECT_FACTORY(SharHP				 , 81 )
		REGISTER_OBJECT_FACTORY(Shuriken			 , 82 )
		REGISTER_OBJECT_FACTORY(Skelegon			 , 83 )
		REGISTER_OBJECT_FACTORY(SleepGas			 , 84 )
		REGISTER_OBJECT_FACTORY(Slow				 , 85 )
		REGISTER_OBJECT_FACTORY(SolThunder			 , 86 )
		REGISTER_OBJECT_FACTORY(Solomon				 , 87 )
		REGISTER_OBJECT_FACTORY(SpawnMonsterAttack	 , 88 )
		//REGISTER_OBJECT_FACTORY	(SpawnUltimate		 , 89 )
		REGISTER_OBJECT_FACTORY(Spear				 , 90 )
		REGISTER_OBJECT_FACTORY(Stigma				 , 91 )
		REGISTER_OBJECT_FACTORY(StigmaBack			 , 92 )
		REGISTER_OBJECT_FACTORY(StigmaCount			 , 93 )
		REGISTER_OBJECT_FACTORY(Stone				 , 94 )
		REGISTER_OBJECT_FACTORY(Stop				 , 95 )
		REGISTER_OBJECT_FACTORY(SwordExplode		 , 96 )
		REGISTER_OBJECT_FACTORY(Temptation			 , 97 )
		REGISTER_OBJECT_FACTORY(Thunder				 , 98 )
		REGISTER_OBJECT_FACTORY(UltimateBackground	 , 99 )
		REGISTER_OBJECT_FACTORY(UltimateFog			 , 100)
		REGISTER_OBJECT_FACTORY(UltimateObject		 , 101)
		REGISTER_OBJECT_FACTORY(UltimateShuriken	 , 102)
		REGISTER_OBJECT_FACTORY(Undead				 , 103)
		REGISTER_OBJECT_FACTORY(UpStat				 , 104)
		REGISTER_OBJECT_FACTORY(Variation			 , 105)
		REGISTER_OBJECT_FACTORY(Whiggin				 , 106)
		REGISTER_OBJECT_FACTORY(White				 , 107)
		REGISTER_OBJECT_FACTORY(Wind				 , 108)
	}

	GameObject* GameObjectManager::GetMonsterOfID(UINT _ID)
	{
		if (m_hashObject.find(_ID) == m_hashObject.end())
			return nullptr;
		return m_hashObject[_ID]();
	}

	
	


}

