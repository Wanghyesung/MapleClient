#include "WGraphicDevice_Dx11.h"
#include "WApplication.h"
#include "WRenderer.h"

extern W::Application application;

namespace W::graphics
{
	//ram위에 gpu그래픽카드의 주소를 가르키는 변수를 올려둠
	//기본적으로 전부 포인터임
	//getaddres로 그 변수의 주소를 가져올 수 있음
	//이중버퍼를 통한 함수로 그 포인터에 값을 할당하고 나옴
	//desc 옵션기능 

	//스왑체인 안에 버퍼를 렌더타켓에 전달
	//엘리러싱
	//밉맵-> 미리 텍스쳐들의 크기별로 만들어두는법 ->그때그떄 연산을 할 필요가없다
	
	//바탕은 하늘, 회색으로 하기 -> 검은색이나 흰색이면 물체를 실수로 검은색으로 했을 떄 안보일 수 있음

	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		//Device, Context 생성
		HWND hwnd = application.GetHwnd();
		//이걸 해야지 디버그 모드로 돌릴 수 있음 배포용은 다른걸로
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		//d3d 드라이버 기능별 
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;
		//int a = 10;
		//int* b = &a;
		//int** c = &b;
		//**c;
		//ID3D11Device* pDevice = nullptr;
		//ID3D11DeviceContext* pContext = nullptr;
		//ID3D11DeviceContext** ppContext = &pContext;

		//null전달, 드라이버형식 타입, 드라이버가 HARDWARE일 경우 null,
		//런타입 계층, featruelevel의 수 D3D11_SDK_VERSION사용, 
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			deviceFlag, nullptr, 0, D3D11_SDK_VERSION,
			m_cpDevice.GetAddressOf(), &featureLevel,
			m_cpContext.GetAddressOf());


		//스왑체인 옵션 (백퍼버 표시 모드 설명)
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//버퍼 계수
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hwnd))
			return;

		m_cpRenderTarget = std::make_shared<Texture>();
		m_cpDepthStencil = std::make_shared<Texture>();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget = {};
		// 스왑체인에 있는 렌더타겟 가져오기
		if (FAILED(m_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)renderTarget.GetAddressOf())))
			return;
		m_cpRenderTarget->SetTexture(renderTarget);


		//렌더타겟뷰 생성
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
		m_cpDevice->CreateRenderTargetView((ID3D11Resource*)m_cpRenderTarget->GetTexture().Get()
			, nullptr, renderTargetView.GetAddressOf());
		m_cpRenderTarget->SetRTV(renderTargetView);

		//2d 텍스쳐 옵션(깊이버퍼)
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		//출력 병합 과정에서  깊이 스텐실 대상으로 바인딩합니다
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		//텍스처를 읽고 쓰는 방법을 식별하는 값입니다.
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;
		//24비트
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		//버퍼 해상도
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		//텍스처 배열의 텍스처 수입니다
		depthStencilDesc.ArraySize = 1;
	
		//픽셀당 다중 샘플 수입니다.
		//이미지 품질 수준입니다. 품질이 높을수록 성능이 떨어집니다 0 ~ 1
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MiscFlags = 0;
		//텍스처의 최대 Mipmap 수준 수입니다
		depthStencilDesc.MipLevels = 0;
		
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencolBuffer = nullptr;
		if (!CreateTexture2D(&depthStencilDesc, nullptr, depthStencolBuffer.GetAddressOf()))
			return;
		m_cpDepthStencil->SetTexture(depthStencolBuffer);

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView = nullptr;
		if (!CreateDepthStencilView(depthStencolBuffer.Get(), nullptr, DepthStencilView.GetAddressOf()))
			return;
		m_cpDepthStencil->SetDSV(DepthStencilView);


		//ndc좌표 -> window 좌표로 전환(뷰포트변환)(좌상단 우하단 크기, 
		//뷰포트도 계속 갱신해야 스크린이 바뀔때 같이 바뀜
		RECT winRect = {};
		GetClientRect(hwnd, &winRect);

		m_tViewPort =
		{
			0.f, 0.f,
			(float)(winRect.right - winRect.left),
			(float)(winRect.bottom - winRect.top),
			0.f,1.f
		};

		BindViewPort(&m_tViewPort);
		// 스텐실 버퍼를 출력-병합 단계에 바인딩합니다.
		m_cpContext->OMSetRenderTargets(1, m_cpRenderTarget->GetRTV().GetAddressOf(), m_cpDepthStencil->GetDSV().Get());

	}
	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{

	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd)
	{
		DXGI_SWAP_CHAIN_DESC dxGiDesc = {};

		//출력창 window핸들값
		dxGiDesc.OutputWindow = _hwnd;
		//출력창 모드인지
		dxGiDesc.Windowed = true;

		dxGiDesc.BufferCount = _desc->BufferCount;
		dxGiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

		//표면 또는 리소스를 출력 렌더링 대상으로 사용합니다.
		dxGiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxGiDesc.BufferDesc.Width = _desc->BufferDesc.Width;
		dxGiDesc.BufferDesc.Height = _desc->BufferDesc.Height;
		//888 rgb 32비트
		dxGiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxGiDesc.BufferDesc.RefreshRate.Numerator = 240;//최대 프레임
		dxGiDesc.BufferDesc.RefreshRate.Denominator = 1; //최소 프레임
		//지정된 모니터의 해상도에 맞게 이미지가 늘어나는 방식 (확대비율 지정) 
		dxGiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxGiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//픽셀당 다중 샘플 수, 이미지 품질 수준 0~1
		dxGiDesc.SampleDesc.Count = 1;
		dxGiDesc.SampleDesc.Quality = 0;

		//adapter = 모니터
		//GIdevice = 렌더타겟
		//factory = 전체화면처리
		Microsoft::WRL::ComPtr<IDXGIDevice> cpDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> cpDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> cpDXGIFactroy = nullptr;

		if (FAILED(m_cpDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)cpDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)cpDXGIAdapter.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)cpDXGIFactroy.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIFactroy->CreateSwapChain(m_cpDevice.Get(), &dxGiDesc, m_cpSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data)
	{
		//D3D11_BUFFER_DESC triangleDesc = {};
		//triangleDesc.ByteWidth = desc->ByteWidth;
		//triangleDesc.BindFlags = desc->BindFlags;
		//triangleDesc.CPUAccessFlags = desc->CPUAccessFlags;


		/*D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;*/

		if(FAILED(m_cpDevice->CreateBuffer(_desc,_data,_buffer)))
			return false;

		return true;
	}
	

	bool GraphicDevice_Dx11::CompileFromfile(const std::wstring& _wstrFileName, const std::string& _strFunName, const std::string& _strVersion, ID3DBlob** _ppCod)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(_wstrFileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_strFunName.c_str(), _strVersion.c_str(), 0, 0, _ppCod, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return true;
	}

	bool GraphicDevice_Dx11::CreateVertexShader(const void* _pShaderByteCode, 
		SIZE_T _BytecodeLength, 
		ID3D11VertexShader** _ppVertexShader)
	{
		if (FAILED(m_cpDevice->CreateVertexShader(_pShaderByteCode, _BytecodeLength, nullptr, _ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateGeometryShader(const void* _pShaderBytecode, SIZE_T _BytecodeLength, ID3D11GeometryShader** _ppGeometryShader)
	{
		if (FAILED(m_cpDevice->CreateGeometryShader(_pShaderBytecode, _BytecodeLength, nullptr, _ppGeometryShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreatePixelShader(const void* _pShaderByteCode, 
		SIZE_T _BytecodeLength, 
		ID3D11PixelShader** _ppPixelShader)
	{
		if (FAILED(m_cpDevice->CreatePixelShader(_pShaderByteCode, _BytecodeLength, nullptr, _ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateComputeShader(const void* _pShaderByteCode, SIZE_T _BytecodeLength, ID3D11ComputeShader** _ppComputeShader)
	{
		if (FAILED(m_cpDevice->CreateComputeShader(_pShaderByteCode, _BytecodeLength, nullptr, _ppComputeShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateSampler(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState)
	{
		if(FAILED(m_cpDevice->CreateSamplerState(_pSamplerDesc,_ppSamplerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateRasterizeState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState)
	{
		if(FAILED(m_cpDevice->CreateRasterizerState(_pRasterizerDesc,_ppRasterizerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc, ID3D11DepthStencilState** _ppDepthStencilState)
	{
		if (FAILED(m_cpDevice->CreateDepthStencilState(_pDepthStencilDesc, _ppDepthStencilState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBlendState(const D3D11_BLEND_DESC* _pBlendStateDesc, ID3D11BlendState** _ppBlendState)
	{
		if (FAILED(m_cpDevice->CreateBlendState(_pBlendStateDesc, _ppBlendState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateShaderResourceView(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc, ID3D11ShaderResourceView** _ppSRVView)
	{
		if (FAILED(m_cpDevice->CreateShaderResourceView(_pResource,_pDesc,_ppSRVView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, ID3D11DepthStencilView** _ppDepthStencilView)
	{
		if (FAILED(m_cpDevice->CreateDepthStencilView(_pResource, _pDesc, _ppDepthStencilView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, ID3D11RenderTargetView** _ppRTView)
	{
		if (FAILED(m_cpDevice->CreateRenderTargetView(_pResource, _pDesc, _ppRTView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateUnorderedAccessView(ID3D11Resource* _pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* _pDesc, ID3D11UnorderedAccessView** _ppUAView)
	{
		if (FAILED(m_cpDevice->CreateUnorderedAccessView(_pResource, _pDesc, _ppUAView)))
			return false;

		return true;
	}
	
	bool GraphicDevice_Dx11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* _desc, void* _pdata, ID3D11Texture2D** _ppTexture2D)
	{
		//2d 텍스쳐 옵션
		//D3D11_TEXTURE2D_DESC dxGiDesc = {};
		//dxGiDesc.BindFlags = _desc->BindFlags;
		//dxGiDesc.Usage = _desc->Usage;
		//dxGiDesc.CPUAccessFlags = 0;
		//
		//dxGiDesc.Format = _desc->Format;
		//dxGiDesc.Width = _desc->Width;
		//dxGiDesc.Height = _desc->Height;
		//dxGiDesc.ArraySize = _desc->ArraySize;
		//
		//dxGiDesc.SampleDesc.Count = _desc->SampleDesc.Count;
		//dxGiDesc.SampleDesc.Quality = 0;
		//
		//dxGiDesc.MipLevels = _desc->MipLevels;
		//dxGiDesc.MiscFlags = _desc->MiscFlags;

		//깊이버퍼
		//if (FAILED(m_cpDevice->CreateTexture2D(&dxGiDesc, nullptr, m_cpDepthStencilBuffer.ReleaseAndGetAddressOf())))
		//	return false;
		//
		////깊이버퍼 뷰
		//if (FAILED(m_cpDevice->CreateDepthStencilView(m_cpDepthStencilBuffer.Get(), nullptr, m_cpDepthStencilView.GetAddressOf())))
		//	return false;

		if (FAILED(m_cpDevice->CreateTexture2D(_desc, nullptr, _ppTexture2D)))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, 
		UINT _iNumElements, 
		ID3DBlob* _byteCode, 
		ID3D11InputLayout** _ppInputLayout)
	{
		if (FAILED(m_cpDevice->CreateInputLayout(_pInputElementDescs, _iNumElements,
			_byteCode->GetBufferPointer(),
			_byteCode->GetBufferSize(),
			_ppInputLayout)))
			return false;

		return true;
	}
	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* _viewPort)
	{
		//뷰포트 개수
		m_cpContext->RSSetViewports(1, _viewPort);

	}
	void GraphicDevice_Dx11::BindRasterizeState(ID3D11RasterizerState* _pRasterizerState)
	{
		m_cpContext->RSSetState(_pRasterizerState);
	}
	void GraphicDevice_Dx11::BindDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
	{
		m_cpContext->OMSetDepthStencilState(_pDepthStencilState,0);
	}
	void GraphicDevice_Dx11::BindBlendState(ID3D11BlendState* _pBlendState)
	{
		m_cpContext->OMSetBlendState(_pBlendState, nullptr, 0xffffffff);
	}
	void GraphicDevice_Dx11::CopyResource(ID3D11Resource* _pDstResource, ID3D11Resource* _pSrcResource)
	{
		m_cpContext->CopyResource(_pDstResource, _pSrcResource);
	}
	void GraphicDevice_Dx11::BindInputLayout(ID3D11InputLayout* _pInputLayout)
	{
		m_cpContext->IASetInputLayout(_pInputLayout);
	}
	void GraphicDevice_Dx11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
	{
		m_cpContext->IASetPrimitiveTopology(_Topology);
	}
	void GraphicDevice_Dx11::BindVertexBuffer(UINT _iStartSlot,
		ID3D11Buffer* const* _ppVertexBuffers, 
		const UINT* _pStrides, 
		const UINT* _pOffsets)
	{
		m_cpContext->IASetVertexBuffers(_iStartSlot, 1, _ppVertexBuffers, _pStrides, _pOffsets);
	}

	void GraphicDevice_Dx11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, 
		DXGI_FORMAT _Format, 
		UINT _iOffset)
	{
		m_cpContext->IASetIndexBuffer(pIndexBuffer, _Format, _iOffset);
	}

	void GraphicDevice_Dx11::BindVertexShader(ID3D11VertexShader* _pVertexShader)
	{
		m_cpContext->VSSetShader(_pVertexShader,0,0);
	}

	void GraphicDevice_Dx11::BindHullShader(ID3D11HullShader* _pHullShader)
	{
		m_cpContext->HSSetShader(_pHullShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindDomainShader(ID3D11DomainShader* _pDomainShader)
	{
		m_cpContext->DSSetShader(_pDomainShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindGeometryShader(ID3D11GeometryShader* _pGeometryShader)
	{
		m_cpContext->GSSetShader(_pGeometryShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindPixelShader(ID3D11PixelShader* _pPixelShader)
	{
		m_cpContext->PSSetShader(_pPixelShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindComputeShader(ID3D11ComputeShader* _pComputeShader)
	{
		m_cpContext->CSSetShader(_pComputeShader, 0, 0);
	}

	void GraphicDevice_Dx11::Dispatch(UINT _iThreadGroupX, UINT _iThreadGroupY, UINT _iThreadGroupZ)
	{
		m_cpContext->Dispatch(_iThreadGroupX, _iThreadGroupY, _iThreadGroupZ);
	}

	void GraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _iSize)
	{
		//cpu에서 받은 값을 gpu로 보내는 과정 연결후 연결 해제까지
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		//리소스는 쓰기용으로 매핑됩니다. 
		m_cpContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		//버퍼 복사
		memcpy(subRes.pData, _data, _iSize);
		//cpu와 gpu연결 해제
		m_cpContext->Unmap(_buffer, 0);//사용후 unmap
	}

	void GraphicDevice_Dx11::BindConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer)
	{
		switch (_eStage)
		{
		case eShaderStage::VS:
			//시작 슬롯 버퍼 개수 
			m_cpContext->VSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::HS:
			m_cpContext->HSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::DS:
			m_cpContext->DSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::GS:
			m_cpContext->GSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::PS:
			m_cpContext->PSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::CS:
			m_cpContext->CSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::BindBuffer(ID3D11Buffer* _pBuffer, void* _data, UINT _iSize)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		m_cpContext->Map(_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, _data, _iSize);
		m_cpContext->Unmap(_pBuffer, 0);
	}
	void GraphicDevice_Dx11::BindsConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer)
	{
		m_cpContext->VSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->HSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->DSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->GSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->PSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->CSSetConstantBuffers((UINT)_eType, 1, &_buffer);

	}
	void GraphicDevice_Dx11::BindShaderResource(eShaderStage _eStage, UINT _iStartSlot, ID3D11ShaderResourceView** _ppSRV)
	{
		switch (_eStage)
		{
		case eShaderStage::VS:
			m_cpContext->VSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::HS:
			m_cpContext->HSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::DS:
			m_cpContext->DSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::GS:
			m_cpContext->GSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::PS:
			m_cpContext->PSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::CS:
			m_cpContext->CSSetShaderResources(_iStartSlot, 1, _ppSRV);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::BinUnorderedAccess(UINT _iSolt, ID3D11UnorderedAccessView** _ppUnorderedAccessViews, const UINT* _pUAVInitialCounts)
	{
		m_cpContext->CSSetUnorderedAccessViews(_iSolt, 1, _ppUnorderedAccessViews,_pUAVInitialCounts);
	}
	void GraphicDevice_Dx11::BindSampler(eShaderStage _eStage, UINT _iStartSlot, ID3D11SamplerState** _ppSamplers)
	{
		switch (_eStage)
		{
		case eShaderStage::VS:
			m_cpContext->VSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::HS:
			m_cpContext->HSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::DS:
			m_cpContext->DSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::GS:
			m_cpContext->GSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::PS:
			m_cpContext->PSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::CS:
			m_cpContext->CSSetSamplers(_iStartSlot, 1, _ppSamplers);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, INT _iBaseVertexLocation)
	{
		m_cpContext->DrawIndexed(_iIndexCount, _iStartIndexLocation, _iBaseVertexLocation);
	}
	void GraphicDevice_Dx11::DrawIndexedInstanced(UINT _iIndexCountPerInstance, UINT _iInstanceCount,
		UINT _iStartIndexLocation, INT _iBaseVertexLocation, UINT _iStartInstanceLocation)
	{
		m_cpContext->DrawIndexedInstanced(_iIndexCountPerInstance, _iInstanceCount, _iStartIndexLocation,
			_iBaseVertexLocation, _iStartInstanceLocation);
	}
	void GraphicDevice_Dx11::ClearTarget()
	{				
		//회색
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 0.2f };
		//백버퍼 지우기
		m_cpContext->ClearRenderTargetView(m_cpRenderTarget->GetRTV().Get(), bgColor);
		//깊이버퍼 지우기
		m_cpContext->ClearDepthStencilView(m_cpDepthStencil->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		//하나 이상의 렌더링 대상을 원자성으로 바인딩하고 깊이 스텐실 버퍼를 출력-병합 단계에 바인딩합니다.
		m_cpContext->OMSetRenderTargets(1, m_cpRenderTarget->GetRTV().GetAddressOf(), m_cpDepthStencil->GetDSV().Get());
	}
	void GraphicDevice_Dx11::UpdateViewPort()
	{
		//뷰포트 업데이트
		HWND hWnd = application.GetHwnd();

		//임시
		//float fHeight = application.GetHeight();
		//float fWidth = application.GetWidth();

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		//float fDiffY = abs(fHeight - (float)(winRect.bottom - winRect.top));
		//float fDiffX = abs(fWidth - (winRect.right - winRect.left));

		m_tViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)// + fDiffX
			//,(float)750.f
			, (float)(winRect.bottom - winRect.top)// + fDiffY
			, 0.0f, 1.0f
		};
		BindViewPort(&m_tViewPort);
		
	}
	void GraphicDevice_Dx11::Draw()
	{	
		
		// input assembler 정점 데이터 지정
		//UINT vertexsize = sizeof(renderer::Vertex);
		//UINT offset = 0;
		//꼭짓점 버퍼 배열을 입력 어셈블러 단계에 바인딩합니다.
		//m_cpContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);

		//UINT바이트인덱스
		//m_cpContext->IASetIndexBuffer(renderer::triangleIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
		// 
		//퍼버 바인딩
		//renderer::mesh->BindBuffer();
		
		//m_cpContext->IASetInputLayout(renderer::shader->GetInputLayout());
		//토폴로지
		//W::graphics::GetDevice()->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//어떻게 그릴지
		//m_cpContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		//bind vs, ps
		//m_cpContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		//m_cpContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		//renderer::shader->Binds();

		//m_cpContext->Draw(3, 0);
		// ps에서 받은 정점들의 데이터들이 보간되기 때문에 픽셀이 중간값이 나옴
		//래스터라이저에서 뒷면제거 외적의 결과로 앞두ㅣ를 판결하기 떄문애 외적의 결과에(먀주보고있으면 뒷면) 따라서 나오는개 달라짐
		//m_cpContext->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		//레더타겟에 있는 이미지를 화면에 그려준다
		//m_cpSwapChain->Present(0, 0);
	}

	void GraphicDevice_Dx11::Present()
	{
		m_cpSwapChain->Present(0, 0);
	}


	

}
