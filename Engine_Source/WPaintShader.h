#pragma once
#include "WComputeShader.h"

namespace W::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		virtual void Binds()override;
		virtual void Clear()override;

		void SetTarget(std::shared_ptr<class Texture> _pTarget) {m_pTarget = _pTarget;}

	private:
		std::shared_ptr<class Texture> m_pTarget;
	};
}
