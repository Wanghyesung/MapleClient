#include "WMonster.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WObjectPoolManager.h"
namespace W
{
	Monster::Monster():
		m_iDir(0)
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

}