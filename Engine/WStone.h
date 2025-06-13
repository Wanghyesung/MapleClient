#pragma once
#include "WGameObject.h"

namespace W
{
	class Stone : public GameObject
	{
	public:
		Stone();
		virtual ~Stone();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iAnim)override;

	private:

	};
}


