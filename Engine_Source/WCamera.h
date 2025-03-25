#pragma once
#include "WComponent.h"
#include "WGraphics.h"

//UI카메라(이동X), 캐릭터 카메라 따로
//renderer render함수에서 카메라 렌더호출
//Scene, camerascript engine쪽으로 이동
//opaque 뷸투명 cutout 부분 부투명 transparnt투명 순으로 렌더 지금은 먼저 만들어진 순서대로
//렌더렁모드순서대로 정렬후 렌더타입 순서대로 렌더
//레이어마다 카메라를 따로 적용가능 
//SceneMgr -> camera(render)로 렌더순서대로 렌더링


//불투명 투명 순서를 정해도 깊이버퍼에선 똑같은 z값으로 먼저 그려진 
// 얘를 그리기 때문에 그 자리에 또 같은 z값의 물체를 그리지 않음
//z정렬 해서 그리는 순서를 맞춰야함ㅇ
namespace W
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpectivem,
			OrthoGraphic,
			None,
		};
		

		Camera();
		virtual ~Camera();

		static Matrix& GetGpuViewMatrix() { return View; }
		static Matrix& GetGpuProjectionMatrix() { return Projection; }
		static void SetGpuViewMatrix(Matrix _View) { View = _View; }
		static void SetGpuProjectionMatrix(Matrix _Projection) { Projection = _Projection; }

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType _eType);
		void RegisterCameraInRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		void TurnLayerMask(eLayerType _eType, bool _bEnable = true);
		void TurnUILayerMask();

		void EnableLayerMasks() { m_bitLayerMask.set(); }
		void DisableLayerMasks() { m_bitLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> _vecGameObj);
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisablDepthStencilState();

		float GetSize() { return m_fSize; }
		Matrix& GetViewMatrix() { return m_mView; }
		Matrix& GetProjectionMatrix() { return m_mProjection; }

	private:
		//월드행렬은 오브젝트마다 다르지만
		//뷰 공간과 투영행렬은 모든 오븍제트들에게 똑같이
		//적용되기 때문에 static으로
		Matrix m_mView;
		Matrix m_mProjection;

		static Matrix View;
		static Matrix Projection;

		eProjectionType m_eType;
		float m_fAspectRatio;//종횡비
		float m_fNear;
		float m_fFal;
		float m_fSize;
	

		//그리는 순서대로 오브젝트 정렬
		std::bitset<(UINT)eLayerType::End> m_bitLayerMask;
		std::vector<GameObject*> m_vecOpaqueGameObjects;
		std::vector<GameObject*> m_vecCutOutGameObjects;
		std::vector<GameObject*> m_vecTransparentGameObjects;
 	};
}


