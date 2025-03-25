#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"
#include "WMesh.h"
#include "WShader.h"
#include "WConstantBuffer.h"
#include "WCamera.h"
#include "WLight.h"

using namespace W::math;
using namespace W::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 Color;
		Vector2 UV;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix m_mWorld;
		Matrix m_mView;
		Matrix m_mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		//카메라 위치 카메라 사이즈, 해상도 크기
		Vector4 m_vCameraPosition;
		Vector2 m_vCameraScale;
		Vector2 m_vResolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		//이미지 좌상단, 스프라이트 크기, 스크라이트 오프셋, 아틀라스(이미지 전체)크기
		Vector2 vSpriteLeftTop;
		Vector2 vSprteSize;
		Vector2 vSprteOffset;
		Vector2 vAtlasSize;
		UINT iAnimationType;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		float deltaTime;
		int padd2;
	};

	CBUFFER(PlayerCB, CBSLOT_PLAYER)
	{
		Vector4 vDir;
		Vector4 vColor;
	};

	CBUFFER(MonsterCB, CBSLOT_MONSTER)
	{
		Vector4 vMonsterDir;
	};

	CBUFFER(PlayerUICB, CBSLOT_PLAYERUI)
	{
		Vector4 vSize;
	};

	CBUFFER(ObjectCB, CBSLOT_OBJECT)
	{
		Vector4 vObjectDir;
		Vector4 vObjectColor;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 vSize;
	};

	//extern Vertex vertexes[];
	//extern ID3D11InputLayout* triangleLayout;
	//extern ID3D11Buffer* triangleBuffer;
	//extern ID3D11Buffer* triangleIdxBuffer;
	//extern W::Mesh* mesh;
	//extern ID3DBlob* errorBlob;
	//extern ID3DBlob* triangleVSBlob;
	//extern ID3D11VertexShader* triangleVSShader;
	//extern ID3DBlob* trianglePSBlob;
	//extern W::Shader* shader;
	//extern ID3D11PixelShader* trianglePSShader;

	extern W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End];
	
	//레스터라이저, 뎁스텐실, 블렌드
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerStates[(UINT)eRSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilStates[(UINT)eDSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> m_cpBlendStates[(UINT)eBSType::End];

	extern std::vector<W::Light*> m_vecLights;

	extern W::Camera* MainCamera;
	extern W::Camera* UICamera;
	extern std::vector<W::Camera*> m_vecCameras;
	extern std::vector<DebugMesh> m_vecDebugMeshs;

	extern Vector2 RectVertexsPos[4];
	extern Vector2 CircleVertexsPos[41];

	void Render();
	void Initialize();
	void BindLights();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}

