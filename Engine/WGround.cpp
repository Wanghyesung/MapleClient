#include "WGround.h"
#include "WCollider2D.h"
#include "WGroundScript.h"

namespace W
{
	Ground::Ground(bool _bFinalGround)
	{
		//기본적으로 충돌체 가지게
		AddComponent<Collider2D>();
		GroundScript* pScript = AddComponent<GroundScript>();
		if (_bFinalGround)
			pScript->SetFinalGround();
	}
	Ground::~Ground()
	{

	}
	void Ground::Initialize()
	{
	}
	void Ground::Update()
	{
		GameObject::Update();
	}
	void Ground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ground::Render()
	{
		GameObject::Render();
	}
}