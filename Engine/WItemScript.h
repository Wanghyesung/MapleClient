#pragma once
#include "WScript.h"

namespace W
{
	class ItemScript : public Script
	{
	public:
		ItemScript();
		virtual ~ItemScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);


	};

}

