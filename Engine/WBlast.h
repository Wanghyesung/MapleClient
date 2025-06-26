#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Blast : public PlayerAttackObject
	{
	public:
		Blast();
		virtual ~Blast();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		
		void UpdateState(const wstring& _strStateName, int _iState);
		
		void SetDir(int _iDir);
	private:
		int m_iDir;

		
	};
}


