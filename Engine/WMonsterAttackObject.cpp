#include "WMonsterAttackObject.h"

#include "WMonster.h"

#include "WEffect.h"
#include "WObject.h"

namespace W
{
	MonsterAttackObject::MonsterAttackObject() :
		m_pOwner(nullptr)
	{

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"pMonsterAttackMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


	}
	MonsterAttackObject::~MonsterAttackObject()
	{

	}

	void MonsterAttackObject::Initialize()
	{

	}

	void MonsterAttackObject::Update()
	{
		
	}

	void MonsterAttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void MonsterAttackObject::Render()
	{
		GameObject::Render();
	}


}