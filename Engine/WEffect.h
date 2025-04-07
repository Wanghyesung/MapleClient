#pragma once
#include "WGameObject.h"

namespace W
{
	class Effect : public GameObject
	{
	public:
		Effect();
		virtual ~Effect();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetOwner(GameObject* _pOwner) { m_pOwner = _pOwner; }
		void CreateAnimation(std::shared_ptr<Texture> _pAtlas, Vector2 _vLeftTop, Vector2 _vSize, UINT _iColumnLength,
			UINT _iRowLength, Vector2 _vDivisionSize, Vector2 _vOffset, float _fDuration);

		void StartEffect(int _iDir);
		
	private:
		int m_iDir;
		GameObject* m_pOwner;
		Vector2 m_vOffset;
	};

}

