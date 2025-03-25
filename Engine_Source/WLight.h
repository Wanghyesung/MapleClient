#pragma once
#include "WComponent.h"
#include "WGraphics.h"

namespace W
{
	using namespace graphics;
	class Light : public Component
	{
	public:
		Light();
		virtual ~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		LightAttribute GetAttribute() { return m_eAttribute; }
		void SetType(eLightType _eType) { m_eAttribute.type = _eType; }
		void SetRadius(float _fRadius) { m_eAttribute.radius = _fRadius; }
		void SetAngle(float _fAngle) { m_eAttribute.angle = _fAngle; }
		void SetColor(Vector4 _vColor) { m_eAttribute.color = _vColor; }
		
		Vector4 GetColor() { return m_eAttribute.color; }
		eLightType GetType() { return m_eAttribute.type; }
		float GetRadius() { return m_eAttribute.radius; }
		float GetAngle() { return m_eAttribute.angle; }


	private:
		LightAttribute m_eAttribute;

	};
}


