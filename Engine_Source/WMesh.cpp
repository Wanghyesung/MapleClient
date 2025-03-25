#include "WMesh.h"
#include "WRenderer.h"
//mesh란 그물처럼 도이었는 정점들의 집합으로 index와 vertex 버퍼로 구성
//mesh를 cpu에서 load 후 gpu로 보낸후 셰이더에서 처리
//들어온 정점데이터를 어떻게 처리할지를 셰이더라표현 셰이더, 매시 전부 리소스로 구분
//셰이더, 블롭, 
// gpu에 이미지마다 다른 vb ib가 있기 때문에 파이프라인에 셋팅해줘서 바꿔야한다
// 때문에 바꾸고 그리고를 연달아 파이프라인에서 처리
// 버퍼셋팅해준 후 shader셋팅 후 파이프라인에 묶기

namespace W
{
    Mesh::Mesh() :
        Resource(enums::eResourceType::Mesh),
        m_cpVertexBuffer(nullptr),
        m_cpIndexBuffer(nullptr),
        m_tVBDesc{},
        m_tIBDesc{},
        m_iIndexCount(0)
    {
        
    }

    Mesh::~Mesh()
    {
        
    }

    HRESULT Mesh::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    bool Mesh::CreateVertexBuffer(void* _data, UINT _iCount)
    {
        m_tVBDesc.ByteWidth = sizeof(renderer::Vertex) * _iCount;
        m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
        m_tVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;//GPU에서 읽기 및 쓰기 액세스가 필요한 리소스입니다.
        m_tVBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sub = {};//서브 리소스
        sub.pSysMem = _data;
        
        //내 버퍼의 주소의 주소값
        if(!GetDevice()->CreateBuffer(m_cpVertexBuffer.GetAddressOf(),&m_tVBDesc,&sub))
            return false;

        return true;
    }

    bool Mesh::CreateIndexBuffer(void* _data, UINT _iCount)
    {
        m_iIndexCount = _iCount;
        m_tIBDesc.ByteWidth = sizeof(UINT) * _iCount;
        m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
        m_tIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        m_tIBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sub = {};
        sub.pSysMem = _data;

        if (!GetDevice()->CreateBuffer(m_cpIndexBuffer.GetAddressOf(), &m_tIBDesc, &sub))
            return false;

        return true;
    }

    void Mesh::BindBuffer()
    {
        //하나의 꼭짓점 버퍼의 크기
        UINT iStride = sizeof(renderer::Vertex);
        //버퍼 시작 위치
        UINT iOffset = 0;

        //시작 슬롯
        GetDevice()->BindVertexBuffer(0, m_cpVertexBuffer.GetAddressOf(), &iStride, &iOffset);
        GetDevice()->BindIndexBuffer(m_cpIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }
    void Mesh::Render()
    {
        GetDevice()->DrawIndexed(m_iIndexCount, 0, 0);
    }
    void Mesh::RenderInstanced(UINT _iStartindexLocation)
    {
        GetDevice()->DrawIndexedInstanced(m_iIndexCount, _iStartindexLocation,0,0,0);
    }
}

