#pragma once
#include "WAbnormal.h"
namespace W
{
	class Confusion : public Abnormal
	{
	public:
		Confusion();
		virtual ~Confusion();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState) override;

	private:
	};

}

