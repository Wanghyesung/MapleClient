#pragma once
#include "WGameObject.h"

namespace W
{
	class DamageFont :public GameObject
	{
	public:
		DamageFont();
		virtual ~DamageFont();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void UpdateState(const wstring& _strStateName, int _iState);

		void CheckDamage(UINT _iDamage);

	private:
		Vector4 m_vColor;
		int m_iDamage;

		static UINT FONTCOUNT;
	};
}



