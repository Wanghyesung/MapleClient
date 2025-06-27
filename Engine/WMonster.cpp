#include "WMonster.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WObjectPoolManager.h"
namespace W
{
	Monster::Monster()
	{

	}
	Monster::~Monster()
	{
		
	}
	void Monster::Initialize()
	{
		
	}
	void Monster::Update()
	{
		
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Monster::Render()
	{
		
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = m_iDir * -1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Monster::UpdateState(const wstring& _strStateName, int _iState)
	{
		bool bRender = (_iState >> 16) & 0xFF;
		UCHAR cDir = (_iState >> 8) & 0xFF;
		UCHAR cAnimIdx = _iState & 0xFF;

		SetRender(bRender);

		if (m_strCurStateName != _strStateName)
		{
			m_strCurStateName = _strStateName;
			GetComponent<Animator>()->Play(m_strCurStateName, true);
		}

		m_iDir = cDir > 0 ? 1 : -1;
		m_iAnimIdx = cAnimIdx;
	}

}