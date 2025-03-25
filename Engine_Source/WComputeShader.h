#pragma once
#include "WResource.h"
#include "WGraphics.h"

//파티클 만들때마다 상속받아서
namespace W::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		ComputeShader(UINT _ix, UINT _iY , UINT _iZ);
		virtual ~ComputeShader();

		bool Create(const std::wstring& _strName, const std::string& _strMethdName);
		virtual HRESULT Load(const std::wstring& _strPath) { return S_FALSE; }
		void OnExcute();

		virtual void Binds();
		virtual void Clear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> m_cpCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_cpCS;

		UINT m_iThreadGroupCountX;
		UINT m_iThreadGroupCountY;
		UINT m_iThreadGroupCountZ;

		UINT m_iGroupX;
		UINT m_iGroupY;
		UINT m_iGroupZ;

	};
}


