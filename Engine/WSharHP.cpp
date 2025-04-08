#include "WSharHP.h"
#include "WResources.h"
#include "WMonsterBackHP.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	
	SharHP::SharHP():
		m_fHP(100.f)
	{
	
	}
	SharHP::~SharHP()
	{
	}
	void SharHP::Initialize()
	{
	}
	void SharHP::Update()
	{
		
	}
	void SharHP::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void SharHP::Render()
	{
		
		renderer::PlayerUICB PlayerUICB;
		PlayerUICB.vSize.x = m_fHP;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::PlayerUI];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerUICB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}