#pragma once
#include "Engine.h"

namespace W
{
#define LAYER_MAX (UINT)eLayerType::End 

	using namespace enums;
	class Collider2D;
	class CollisionManager
	{
	public:
		union ColliderID
		{
			struct
			{
				UINT m_iLeft;
				UINT m_iRight;
			};
			UINT64 ID;
		};

		static void Initialize();
		static void Update();
		static void LayerCollision(eLayerType _eLeft, eLayerType _eRight);
		static void ColliderCollision(Collider2D* _pLeft, Collider2D* _pRight);
		static bool Intersect(Collider2D* _pLeft, Collider2D* _pRight);

		static void SetLayer(eLayerType _eLeft, eLayerType _eRight, bool _bEnable);
		static void Clear();

	private:
		static void erase(ColliderID _tCollID);

	private:
		static std::bitset<LAYER_MAX> m_bitMatrix[LAYER_MAX];
		static std::map<UINT64, bool> m_mapCollision;

	};
}


