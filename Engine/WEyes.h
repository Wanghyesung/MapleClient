#pragma once

#include "WGameObject.h"
#include "WPlayer.h"

namespace W
{
	class PlayerHead;
	class Eyes : public GameObject
	{
	public:
		Eyes();
		virtual ~Eyes();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetEye(UINT _iNum);
		
	private:
	

		UINT m_iEyeNumber;
		

	};
}


