#include "WUpStat.h"
#include "WRenderer.h"
#include "WMonster.h"
#include "WObject.h"
#include "WTime.h"

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
		
	}
	void UpStat::LateUpdate()
	{
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