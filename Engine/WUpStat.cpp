#include "WUpStat.h"
#include "WRenderer.h"
#include "WMonster.h"
#include "WObject.h"
#include "WTime.h"
#include "WMonsterScript.h"
#include "WBattleManager.h"
namespace W
{
	UpStat::UpStat(float _fAccStat):
		m_fCurTime(0.f),
		m_fAccStat(_fAccStat)
	{

	}
	UpStat::~UpStat()
	{

	}
	void UpStat::Initialize()
	{

	}
	void UpStat::Update()
	{
		GameObject::Update();
	}
	void UpStat::LateUpdate()
	{
		m_fCurTime += Time::DeltaTime();

		if (m_fCurTime >= m_fDeleteTime ||
			m_pTarget->GetState() == GameObject::Paused)
		{
			object::Destroy(this);
			BattleManager::Buff_Stat(m_pTarget, m_eType, -m_fAccStat);
			return;
		}

		Vector3 vPosition = m_pTarget->GetComponent<Collider2D>()->GetPosition();
		vPosition.y += 0.5f;
		vPosition.z -= 0.2f;

		GetComponent<Transform>()->SetPosition(vPosition);

		GameObject::LateUpdate();
	}
	void UpStat::Render()
	{

		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}