#pragma once
#include "WPlayerAttackObject.h"
namespace W
{
	class Wind : public PlayerAttackObject
	{
	public:
		Wind();
		virtual ~Wind();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetDir(int _iDir) { m_iDir = _iDir; }
	
	private:
		int m_iDir;
		
	};
}


