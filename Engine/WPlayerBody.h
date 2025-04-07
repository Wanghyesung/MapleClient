#pragma once
#include "WGameObject.h"
#include "WPlayer.h"
namespace W
{	
	class PlayerTop;
	class PlayerBottom;
	class PlayerShoes;

	class PlayerBody : public GameObject
	{
	public:
		PlayerBody();
		virtual ~PlayerBody();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		
	};
}


