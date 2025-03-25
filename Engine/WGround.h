#pragma once
#include "WGameObject.h"
namespace W
{
	class Ground : public GameObject
	{
	public:
		Ground(bool _bFinalGround = false);
		virtual ~Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:


	};
}


