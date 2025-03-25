#pragma once
#include "WGameObject.h"
#include "WAudioClip.h"
namespace W
{
	class Player;
	class Effect;
	class PlayerAttackObject : public GameObject
	{
	public:
		PlayerAttackObject();
		virtual ~PlayerAttackObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Player* GetPlayer() { return m_pPlayer; }
		void SetPlayer(Player* _pPlayer){ m_pPlayer = _pPlayer;}

		virtual void Off();
		void PushObjectPool();

		void SetSound(const std::wstring& _strName, std::shared_ptr<AudioClip> clip, bool _bLoop);
		void StartSound(const std::wstring& _strName);

		void SetHitSound(std::shared_ptr<AudioClip> clip, bool _bLoop);
		void HitStartSound();
		
	private:
		Player* m_pPlayer;

		std::shared_ptr<AudioClip> m_pSoundClip;
		std::shared_ptr<AudioClip> m_pHitSoundClip;

		std::map <std::wstring, std::shared_ptr<AudioClip>> m_mapSound;
	};
}


