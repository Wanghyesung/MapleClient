#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"
#include "WMesh.h"
#include "WShader.h"
#include "WConstantBuffer.h"
#include "WCamera.h"
#include "WLight.h"


namespace renderer
{
	using namespace W;
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
		//ī�޶� ��ġ ī�޶� ������, �ػ� ũ��
		Vector4 m_vCameraPosition;
		Vector2 m_vCameraScale;
		Vector2 m_vResolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		//�̹��� �»��, ��������Ʈ ũ��, ��ũ����Ʈ ������, ��Ʋ��(�̹��� ��ü)ũ��
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


	extern W::ConstantBuffer* constantBuffer[(UINT)eCBType::END];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End];
	
	//�����Ͷ�����, �����ٽ�, ����
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerStates[(UINT)eRSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilStates[(UINT)eDSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> m_cpBlendStates[(UINT)eBSType::End];

	extern std::vector<W::Light*> m_vecLights;

	extern W::Camera* MainCamera;
	extern W::Camera* UICamera;
	extern std::vector<W::Camera*> m_vecCameras;
	
	extern Vector2 RectVertexsPos[4];
	extern Vector2 CircleVertexsPos[41];

	void Render();
	void Initialize();
	void BindLights();
	void Release();

}

