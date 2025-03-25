#pragma once
#include "WGameObject.h"
namespace W
{
	class StigmaCount : public GameObject
	{
	public:
		StigmaCount();
		virtual ~StigmaCount();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void set_count(UINT _iCount);

	private:
		UINT m_iNumber;
		GameObject* m_pOwner;

		friend class StigmaBack;
	};

}

