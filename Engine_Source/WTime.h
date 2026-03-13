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
		static float GetFPS() { return m_fFPS; }
		__forceinline static double DeltaTime() { return m_dDeltaTime; }
		static double AccTime() { return m_dAccTime; }

	private:
		static double m_dDeltaTime;
		static double m_dSecond;
		static double m_dAccTime;
		static float m_fFPS;
		static LARGE_INTEGER m_lCpuFrequency;
		static LARGE_INTEGER m_lPrevFrequency;
		static LARGE_INTEGER m_lCurFrequency;

	};
}

