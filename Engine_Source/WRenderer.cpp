#include "WRenderer.h"
//#include "WApplication.h"

//extern W::Application application;
#include "WResources.h"
#include "WTexture.h"
#include "WMaterial.h"
#include "WStructedBuffer.h"
#include "WPaintShader.h"
#include "WParticleShader.h"




namespace renderer
{
	using namespace W;
	using namespace W::graphics;

	W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};

	
	
	//텍스쳐 이미지 없으면 albedo
	//출력병합단계에서 깊이테스트, 알파테스트 과정
	//레스터라이저 (컬링 모드 : 물체가 뒷면(메쉬제외 앞면제거할지 뒷면제거할지) solidback 뒷면제거 , front앞 none(제거 x), wireframeNone(mesh보이게)
	// 스카이박스 (ex::front 앞면을 지움 카메라와같은 방향이지만 뒷면이 보임)
	//뎁스 스테이트 (깊이 ex: z값이 작은수로할지 큰수로할지 앞뒤판별, 반투명물체 석을때) (less더 작은걸 앞에, greater 큰거, none X 
	// 런더타켓의 픽셀들의 깊이정보를 비교하여 픽셀셰이더에서 작은걸로 비교(less) (스텐실버퍼 -> 공판화 틀?)
	//블렌드 스테이트 (알파 블렌딩) default , alphablend(투명값적용) 
	//bindpixle 때 어떤 레스터라이저, 뎁스, 블랜드 스테이더로 할지 결정
	//셰이더에서 상태값 변수로
	//om->깊이상태,블랜드
	//텍스쳐에서 샘플러 
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_cpBlendStates[(UINT)eBSType::End] = {};

	//light
	std::vector<W::Light*> m_vecLights = {};
	StructedBuffer* m_pLightsBuffer = nullptr;

	W::Camera* MainCamera = nullptr;
	W::Camera* UICamera = nullptr;
	std::vector<W::Camera*> m_vecCameras = {};
	std::vector<DebugMesh> m_vecDebugMeshs = {};

	Vector2 RectVertexsPos[4] = {};
	Vector2 CircleVertexsPos[41] = {};
	void SetupState()
	{
#pragma region InputLayout
		//Iinput layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};
		
		//3바이트
		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		//4바이트
		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		//2바이트
		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> pShader = W::Resources::Find<Shader>(L"TriangleShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());
		
		pShader = W::Resources::Find<Shader>(L"GridShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"SpriteShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());


		pShader = W::Resources::Find<Shader>(L"BackgroundShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"ObjectShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"UIShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"DebugShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"PlayerShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"SpriteAnimationShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"MonsterShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"ObjectAnimShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"LightShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"PlayerUIShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"ParticleShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, pShader->GetVSCode()
			, pShader->GetInputLayoutAddressOf());


#pragma endregion

#pragma region Sampler State
		//smapler state 어떻게 그릴지 옵션
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&samplerDesc, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&samplerDesc, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC tRasterizerDesc = {};
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//꼭짓점에서 형성된 삼각형을 채웁니다. 인접한 꼭짓점이 그려지지 않습니다.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;//뒷면제거
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;// 꼭짓점에서 형성된 삼각형을 채웁니다.인접한 꼭짓점이 그려지지 않습니다.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;//앞면제거
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//꼭짓점에서 형성된 삼각형을 채웁니다. 인접한 꼭짓점이 그려지지 않습니다.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;//제거X
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;//꼭짓점을 연결하는 선을 그립니다. 인접한 꼭짓점이 그려지지 않습니다.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;//뒷면제거
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());	
#pragma endregion

#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc = {};

		//z값이 작은쪽이 안보이게
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.StencilEnable = false; //틀

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::Less].GetAddressOf());
		
		//z값이 큰 쪽이 보이게
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.StencilEnable = false; //틀

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;//깊이 스텐실 버퍼에 대한 쓰기를 끕니다.
		tDepthStencilDesc.StencilEnable = false; //틀

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		tDepthStencilDesc.DepthEnable = false;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		tDepthStencilDesc.StencilEnable = false; //틀

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion

#pragma region Blend State
		D3D11_BLEND_DESC tBlendDesc = {};

		//default
		m_cpBlendStates[(UINT)eBSType::Default] = nullptr;

		//alpha blend
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;
		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&tBlendDesc,
			m_cpBlendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		//one one
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&tBlendDesc,
			m_cpBlendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		//PointMesh
		Vertex v = {};
		v.Pos = Vector3(0.f, 0.f, 0.f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear();

		//RECT
		vertexes.resize(4);
		vertexes[0].Pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].UV = Vector2(0.0f, 0.0f);

		vertexes[1].Pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].UV = Vector2(1.0f, 0.0f);

		vertexes[2].Pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].UV = Vector2(1.0f, 1.0f);

		vertexes[3].Pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].UV = Vector2(0.0f, 1.0f);

		for (UINT i = 0; i < 4; ++i)
		{
			RectVertexsPos[i] = Vector2(vertexes[i].Pos.x, vertexes[i].Pos.y);
		}

		// Vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());



		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.Pos = Vector3(0.0f, 0.0f, 0.0f);
		center.Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.Pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.Color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);

		}

		//정점정보 저장
		for (UINT i = 0; i < 41; ++i)
		{
			CircleVertexsPos[i] = Vector2(vertexes[i].Pos.x, vertexes[i].Pos.y);
		}


		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());

	}

	void LoadBuffer()
	{

		//constant buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
		
		//grid buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		constantBuffer[(UINT)eCBType::Player] = new ConstantBuffer(eCBType::Player);
		constantBuffer[(UINT)eCBType::Player]->Create(sizeof(PlayerCB));

		constantBuffer[(UINT)eCBType::Monster] = new ConstantBuffer(eCBType::Monster);
		constantBuffer[(UINT)eCBType::Monster]->Create(sizeof(MonsterCB));

		constantBuffer[(UINT)eCBType::PlayerUI] = new ConstantBuffer(eCBType::PlayerUI);
		constantBuffer[(UINT)eCBType::PlayerUI]->Create(sizeof(PlayerUICB));

		constantBuffer[(UINT)eCBType::Object] = new ConstantBuffer(eCBType::Object);
		constantBuffer[(UINT)eCBType::Object]->Create(sizeof(ObjectCB));

		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		m_pLightsBuffer = new StructedBuffer();
		m_pLightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr,true);
	}

	void LoadShader()
	{
		//application.GetDevice().get()->CreateShader();
		//W::graphics::GetDevice()->CreateShader();

		std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
		pShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		pShader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
		W::Resources::Insert(L"TriangleShader", pShader);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> pSpriteShader = std::make_shared<Shader>();
		pSpriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		pSpriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		W::Resources::Insert(L"SpriteShader", pSpriteShader);

		std::shared_ptr<Shader> pBackShader = std::make_shared<Shader>();
		pBackShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pBackShader->Create(eShaderStage::PS, L"BackgroundPS.hlsl", "main");
		W::Resources::Insert(L"BackgroundShader", pBackShader);

		std::shared_ptr<Shader> pObjcetShader = std::make_shared<Shader>();
		pObjcetShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pObjcetShader->Create(eShaderStage::PS, L"ObjectPS.hlsl", "main");
		W::Resources::Insert(L"ObjectShader", pObjcetShader);

		std::shared_ptr<Shader> pUIShader = std::make_shared<Shader>();
		pUIShader->Create(eShaderStage::VS, L"UIVS.hlsl", "main");
		pUIShader->Create(eShaderStage::PS, L"UIPS.hlsl", "main");
		W::Resources::Insert(L"UIShader", pUIShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		W::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<Shader> pPlayerShader = std::make_shared<Shader>();
		pPlayerShader->Create(eShaderStage::VS, L"PlayerVS.hlsl", "main");
		pPlayerShader->Create(eShaderStage::PS, L"PlayerPS.hlsl", "main");
		W::Resources::Insert(L"PlayerShader", pPlayerShader);

		std::shared_ptr<Shader> pSpriteAniShader = std::make_shared<Shader>();
		pSpriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		pSpriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		W::Resources::Insert(L"SpriteAnimationShader", pSpriteAniShader);
	
		std::shared_ptr<Shader> pMonsterShader = std::make_shared<Shader>();
		pMonsterShader->Create(eShaderStage::VS, L"MonsterVS.hlsl", "main");
		pMonsterShader->Create(eShaderStage::PS, L"MonsterPS.hlsl", "main");
		W::Resources::Insert(L"MonsterShader", pMonsterShader);

		std::shared_ptr<Shader> pObjectAnimShader = std::make_shared<Shader>();
		pObjectAnimShader->Create(eShaderStage::VS, L"ObjectAnimVS.hlsl", "main");
		pObjectAnimShader->Create(eShaderStage::PS, L"ObjectAnimPS.hlsl", "main");
		W::Resources::Insert(L"ObjectAnimShader", pObjectAnimShader);

		std::shared_ptr<Shader> pLightShader = std::make_shared<Shader>();
		pLightShader->Create(eShaderStage::VS, L"LightVS.hlsl", "main");
		pLightShader->Create(eShaderStage::PS, L"LightPS.hlsl", "main");
		W::Resources::Insert(L"LightShader", pLightShader);

		std::shared_ptr<Shader> pPlayerUIShader = std::make_shared<Shader>();
		pPlayerUIShader->Create(eShaderStage::VS, L"PlayerUIVS.hlsl", "main");
		pPlayerUIShader->Create(eShaderStage::PS, L"PlayerUIPS.hlsl", "main");
		W::Resources::Insert(L"PlayerUIShader", pPlayerUIShader);

		std::shared_ptr<PaintShader> pPaintShader = std::make_shared<PaintShader>();
		pPaintShader->Create(L"PaintCS.hlsl", "main");
		W::Resources::Insert(L"PaintShader", pPaintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		W::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		W::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTexture()
	{
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		W::Resources::Insert(L"PaintTexuture", uavTexture);

		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"RedParticle", L"..\\Resources\\particle\\redparticle.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		//Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}

	void LoadMaterial()
	{
#pragma region background
		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"LeafreTex", L"..\\Resources\\Texture\\background\\Leafre_2.png");
			std::shared_ptr<Material> pBackgroundMater = std::make_shared<Material>();
			pBackgroundMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pBackgroundMater->SetTexture(pTex);
			Resources::Insert(L"LeafeMater", pBackgroundMater);

			//
			

			std::shared_ptr<Texture> pValleyTex2 =
				Resources::Load<Texture>(L"dragonValleyTex2", L"..\\Resources\\Texture\\background\\dragonValley_2.png");
			std::shared_ptr<Material> pValleyMater2 = std::make_shared<Material>();
			pValleyMater2->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pValleyMater2->SetTexture(pValleyTex2);
			Resources::Insert(L"dragonValleyMater2", pValleyMater2);


			std::shared_ptr<Texture> pWoodCaveTex =
				Resources::Load<Texture>(L"WoodCaveTex", L"..\\Resources\\Texture\\background\\woodCave_tem3.png");
			std::shared_ptr<Material> pWoodMater = std::make_shared<Material>();
			pWoodMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pWoodMater->SetTexture(pWoodCaveTex);
			Resources::Insert(L"WoodCaveMater", pWoodMater);

			std::shared_ptr<Texture> pTempleTex =
				Resources::Load<Texture>(L"TempleTex", L"..\\Resources\\Texture\\background\\Temple.png");
			std::shared_ptr<Material> pTempleMater = std::make_shared<Material>();
			pTempleMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleMater->SetTexture(pTempleTex);
			Resources::Insert(L"TempleMater", pTempleMater);

			std::shared_ptr<Texture> pTempleTex2 =
				Resources::Load<Texture>(L"TempleTex2", L"..\\Resources\\Texture\\background\\temple_2.png");
			//pTempleTex2->BindShader(eShaderStage::PS, 0);
			std::shared_ptr<Material> pTempleMater2 = std::make_shared<Material>();
			pTempleMater2->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleMater2->SetTexture(pTempleTex2);
			Resources::Insert(L"TempleMater2", pTempleMater2);

			std::shared_ptr<Texture> pTempleBossTex =
				Resources::Load<Texture>(L"TempleBossTex", L"..\\Resources\\Texture\\background\\temple_boss.png");
			std::shared_ptr<Material> pTempleBossMater = std::make_shared<Material>();
			pTempleBossMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleBossMater->SetTexture(pTempleBossTex);
			Resources::Insert(L"TempleBossMater", pTempleBossMater);

			std::shared_ptr<Material> pParticleMater = std::make_shared<Material>();
			pParticleMater->SetShader(Resources::Find<Shader>(L"ParticleShader"));
			pParticleMater->SetRenderinMode(eRenderingMode::Transparent);
			std::shared_ptr<Texture> particleTex
				= Resources::Find<Texture>(L"RedParticle");
			pParticleMater->SetTexture(particleTex);
			Resources::Insert(L"ParticleMaterial", pParticleMater);
		}
#pragma endregion
		//두 오브젝트 둘다 똑같은 메테리얼로 셋팅
		
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		///////////////////////////////////
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"PlayerShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"PlayerMaterial", pMater);
		

		 pTex = Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader((Resources::Find<Shader>(L"LightShader")));
		material->SetTexture(pTex);
		Resources::Insert(L"SpriteMaterial", material);

		
		//pTex = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		pTex = Resources::Find<Texture>(L"PaintTexuture");
		pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		pMater->SetTexture(pTex);
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", pMater);
		
		std::shared_ptr<Shader> girdShader = Resources::Find<Shader>(L"GridShader");
		pMater = std::make_shared<Material>();
		pMater->SetShader(girdShader);
		Resources::Insert(L"GridMaterial", pMater);

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		pMater = std::make_shared<Material>();
		pMater->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", pMater);


		material = std::make_shared<Material>();
		material->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		material->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimaionMaterial", material);

		//material = std::make_shared<Material>();
		//material->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		//material->SetRenderinMode(eRenderingMode::Transparent);
		//Resources::Insert(L"MonsterMaterial", material);
	}
	

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
		
	}
	void BindLights()
	{
		std::vector<LightAttribute> vecLightsAttributes = {};
		for (Light* light : m_vecLights)
		{
			LightAttribute attribute = light->GetAttribute();
			vecLightsAttributes.push_back(attribute);
		}

		if (vecLightsAttributes.size() == 0)
			return;

		m_pLightsBuffer->SetData(vecLightsAttributes.data(), vecLightsAttributes.size());
		m_pLightsBuffer->BindSRV(eShaderStage::VS, 13);
		m_pLightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> spTex=
			Resources::Find<Texture>(L"Noise01");

		spTex->BindShaderResource(eShaderStage::VS, 15);
		spTex->BindShaderResource(eShaderStage::HS, 15);
		spTex->BindShaderResource(eShaderStage::DS, 15);
		spTex->BindShaderResource(eShaderStage::GS, 15);
		spTex->BindShaderResource(eShaderStage::PS, 15);
		spTex->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* pCB = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.vSize.x = spTex->GetWidth();
		data.vSize.y = spTex->GetHeight();

		pCB->SetData(&data);
		pCB->Bind(eShaderStage::VS);
		pCB->Bind(eShaderStage::GS);
		pCB->Bind(eShaderStage::PS);
		pCB->Bind(eShaderStage::CS);
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();
		for (Camera* cam : m_vecCameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}
		//물체 그리고 벡터 지우기
		m_vecCameras.clear();
		m_vecLights.clear();
	}

	void Release()
	{
		
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete m_pLightsBuffer;
		m_pLightsBuffer = nullptr;
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		m_vecDebugMeshs.push_back(mesh);
	}

}