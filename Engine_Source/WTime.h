#pragma once
#include "Engine.h"


namespace W
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return m_dDeltaTime; }

	private:
		static double m_dDeltaTime;
		static double m_dSecond;
		static LARGE_INTEGER m_lCpuFrequency;
		static LARGE_INTEGER m_lPrevFrequency;
		static LARGE_INTEGER m_lCurFrequency;

	};
}

