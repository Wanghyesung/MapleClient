#include "WPlayerAttackObject.h"
#include "WAttackScript.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
namespace W
{
	PlayerAttackObject::PlayerAttackObject():
		m_pPlayer(nullptr),
		m_pSoundClip(nullptr),
		m_mapSound{}
	{

	}
	PlayerAttackObject::~PlayerAttackObject()
	{
		
	}
	void PlayerAttackObject::Initialize()
	{
		AddComponent<AttackScript>()->SetDeleteTime(0.1f);

		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.4f, 0.2f));
	}
	void PlayerAttackObject::Update()
	{
		GameObject::Update();
	}
	void PlayerAttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayerAttackObject::Render()
	{
		GameObject::Render();
	}
	void PlayerAttackObject::Off()
	{
		GetScript<AttackScript>()->off();

		GetComponent<Collider2D>()->SetActive(false);


		if(m_pHitSoundClip)
			m_pHitSoundClip->Stop();
	}
	void PlayerAttackObject::PushObjectPool()
	{
		EventManager::AddPlayerPool(this);
	}
	void PlayerAttackObject::SetSound(const std::wstring& _strName, std::shared_ptr<AudioClip> clip, bool _bLoop)
	{
		std::map < std::wstring, std::shared_ptr<AudioClip>>::iterator iter =
			m_mapSound.find(_strName);
		if (iter != m_mapSound.end())
			return;

		m_mapSound.insert(std::make_pair(_strName, clip));
		m_pSoundClip = clip;
		m_pSoundClip->SetLoop(_bLoop);
		
	}
	void PlayerAttackObject::StartSound(const std::wstring& _strName)
	{
		std::map < std::wstring, std::shared_ptr<AudioClip>>::iterator iter =
			m_mapSound.find(_strName);
		if (iter == m_mapSound.end())
			return;

		if (m_pSoundClip)
		{
			m_pSoundClip->Stop();

			m_pSoundClip = iter->second;

			m_pSoundClip->Play();
		}
	}
	void PlayerAttackObject::SetHitSound(std::shared_ptr<AudioClip> clip, bool _bLoop)
	{
		m_pHitSoundClip = clip;
		m_pHitSoundClip->SetLoop(_bLoop);
	}
	void PlayerAttackObject::HitStartSound()
	{
		if (m_pHitSoundClip)
			m_pHitSoundClip->Play();
	}
}