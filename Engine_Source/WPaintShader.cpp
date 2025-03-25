#include "WPaintShader.h"
#include "WTexture.h"

namespace W::graphics
{
	void PaintShader::Binds()
	{
		m_pTarget->BindUnorderedAccessViews(0);

		m_iGroupX = m_pTarget->GetWidth() / m_iThreadGroupCountX + 1;
		m_iGroupY = m_pTarget->GetHeight() / m_iThreadGroupCountY + 1;
		m_iGroupZ = 1;

	}
	void PaintShader::Clear()
	{
		m_pTarget->ClearUnorderedAccessViews(0);
	}
}