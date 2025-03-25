#include "WCameraScript.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WTime.h"
#include "WInput.h"
#include "WScene.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WTime.h"

namespace W
{
	CameraScript::CameraScript():
		m_pPlayer(nullptr),
		m_fEventCurTime(0.f),
		m_fEventEndTime(3.f),
		m_eCurEventType(eCameraEventType::None)
	{
		
	}
	CameraScript::~CameraScript()
	{

	}
	void CameraScript::Update()
	{
		if (m_pPlayer != nullptr)
			move_player();
		else
			move();

		switch (m_eCurEventType)
		{
		case W::CameraScript::eCameraEventType::Wave:
			wave();
			break;
		}
	}

	void CameraScript::wave()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();

		m_fEventCurTime += Time::DeltaTime();
		static UINT elapsedCount = 0.f;
		static int iDir = 1;
		float fCycle = m_fEventEndTime / 30.f;
		float fWaveValue = 60.f;

		if (m_fEventCurTime >= m_fEventEndTime)
		{
			m_fEventCurTime = 0.f;
			elapsedCount = 0.f;
			m_eCurEventType = eCameraEventType::None;
		}
		else
		{
			if (m_fEventCurTime >= fCycle * elapsedCount)
			{
				m_fEventCurTime = fCycle * elapsedCount;
				++elapsedCount;
				iDir *= -1;
			}
			float y = fWaveValue * iDir * Time::DeltaTime();
			Vector3 vWaveValue = Vector3(vPos.x, y, vPos.z);
			Vector3 vFinalPos = Vector3::Lerp(vPos, vWaveValue, 0.5f);
			
			pTr->SetPosition(vFinalPos);
		}
	}

	
	Vector3 CameraScript::check_map(Vector3 _vPosition)
	{
		Scene* pActiveScene = SceneManger::GetActiveScene();

		Scene::tMapSize tMapSize = pActiveScene->GetMapSize();

		Vector3 vPos = _vPosition;
		//¸Ê ¹üÀ§ Ã¼Å©
		float rx = tMapSize.RX; float ry = tMapSize.RY;
		float lx = tMapSize.LX; float ly = tMapSize.LY;

		if (!(lx <= vPos.x && vPos.x <= rx))
		{
			if (lx >= vPos.x)
				vPos.x = lx;
			else if (rx <= vPos.x)
				vPos.x = rx;
		}

		if (!(ly >= vPos.y && vPos.y >= ry))
		{
			if (ly <= vPos.y)
				vPos.y = ly;
			else if (ry >= vPos.y)
				vPos.y = ry;
		}

		return vPos;
	}

	void CameraScript::move()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();

		if (Input::GetKey(eKeyCode::W))
		{
			vPos.z += 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			vPos.z -= 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			vPos.x -= 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			vPos.x += 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			vPos.y -= 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			vPos.y += 5.0f * Time::DeltaTime();
		}
		vPos = check_map(vPos);

		pTr->SetPosition(vPos);
	}

	void CameraScript::move_player()
	{	

		Transform* pPlayerTr = m_pPlayer->GetComponent<Transform>();
		Transform* pTr = GetOwner()->GetComponent<Transform>();

		Vector3 vPlayerPos = pPlayerTr->GetPosition();
		Vector3 vStartPos = pTr->GetPosition();

		Vector2 PlayerPos = Vector2(vPlayerPos.x, vPlayerPos.y);
		Vector2 StartPos = Vector2(vStartPos.x, vStartPos.y);

		Vector2 vFinalPos = Vector2::Lerp(StartPos, PlayerPos, Time::DeltaTime() * 6);
		Vector3 vPos = Vector3(vFinalPos.x, vFinalPos.y, vStartPos.z);

		vPos = check_map(vPos);

		//Vector3 vPos = pTr->GetPosition();
		pTr->SetPosition(vPos);
	}
	
}