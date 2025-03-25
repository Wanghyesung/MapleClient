#pragma once
#include "WMonster.h"

namespace W
{
	class PinkBean;

	class MiniBean : public Monster
	{
	public:
		MiniBean();
		virtual ~MiniBean();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetOwner(PinkBean* _pOwner) { m_pOwner = _pOwner; }

	private:
		void setattack();

		void attack0();
		void attack1();
	
		//Vector2 get_dir();

	private:
		PinkBean* m_pOwner;
		//Vector2 m_vDir;
	};

}

