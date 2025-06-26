#pragma once
#include "WPlayerAttackObject.h"
namespace W
{
	class UltimateFog : public PlayerAttackObject
	{
	public:
		UltimateFog();
		virtual ~UltimateFog();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;
	private:


	};
}


