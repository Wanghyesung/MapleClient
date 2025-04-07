#pragma once
#include "WGameObject.h"
#include "WPlayer.h"

namespace W
{
	class PlayerHead;
	class PlayerHair : public GameObject
	{
	public:
		PlayerHair();
		virtual ~PlayerHair();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetHair(UINT _iNum);
	private:
		
		UINT m_iHairNum;


	};
}


