#include "WSharHP.h"
#include "WResources.h"
#include "WMonsterBackHP.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	
	SharHP::SharHP()
	{
	
	}
	SharHP::~SharHP()
	{

	}
	void SharHP::Initialize()
	{
		GetComponent<Transform>()->SetScale(1.2f * 7.6f, 1.2f * 0.4f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f, 3.5f, -2.f);

		MeshRenderer* pRenderer = GetComponent<MeshRenderer>();
		pRenderer->GetMaterial()->SetTexture(Resources::Find<Texture>(L"BossHP"));
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
		MonsterHP::Render();
	}
	void SharHP::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterHP::UpdateState(_strStateName, _iState);
	}
}