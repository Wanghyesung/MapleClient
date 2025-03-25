#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "Enums.h"
#include "WMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
//16바이트로만 만들게
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

//0번 슬롯 위치
#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				2
#define CBSLOT_ANIMATION2D		3
#define CBSLOT_PARTICLE			4
#define CBSLOT_PLAYER			5
#define CBSLOT_MONSTER			6
#define CBSLOT_PLAYERUI			7
#define CBSLOT_OBJECT			8
#define CBSLOT_NOISE			9

namespace W::graphics
{

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		END,
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Animator,
		Particle,
		Player = 5,
		Monster = 6,
		PlayerUI = 7,
		Object = 8,
		Noise = 9,
		END = 10,
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		End,
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};

	enum class eViewType
	{
		None,
		SRV,
		UAV,
		End,
	};

	enum class eSRVType
	{
		None,
		End,
	};

	//버퍼의 공통적으로 받는 ID3D11buffer, 옵션 다 받을 수 있게
	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer() :
			buffer(nullptr),
			desc{}
		{

		}

		//기본 소멸자
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;

		bool active;
	};

	//13
	struct LightAttribute
	{
		math::Vector4 color;
		math::Vector4 position;
		math::Vector4 direction;

		enums::eLightType type;
		float radius;
		float angle;
		int pad;
	};

	//14
	struct Particle
	{
		math::Vector4 position;
		math::Vector4 direction;

		float endTime;
		float time;
		float speed;
		UINT active;
	};
	//15
	struct ParticleShared
	{
		UINT sharedActiveCount;
	};
}