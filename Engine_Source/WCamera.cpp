#include "WCamera.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WApplication.h"
#include "WRenderer.h"
#include "WScene.h"
#include "WSceneManger.h"
#include "WMeshRenderer.h"
//씬 쪼개기

//메테리얼 바뀔때마다 해당 텍스쳐(shader와 바인딩된) 초기화 
//렌더러에서 메테리얼, 메쉬 그리고 clear

//orthographic 2차원 크기 똑같이
//perpective 뒤로 갈수록 작아지게
//near 절두체 앞(앞부분 짤라서 사용가능)
//far 절두체 뒤(시야)
//카메라는 이동, 회전행렬만
//오브젝트는 카메라의 이동반대방향으로 -pos
//카메라의 기저벡터를 활용해서 회전(오일러각X)
//createlookat함수도 가능 하지만 전자에 비해서 느림
//월드에서는 srt순으로 바꾸어야하지만 view에에서는 tr순서상관이없음 월드행렬은 회전부분행렬이 겹침
//투영행렬전에 종횡비세팅해야함 가로/ 세로
//LH왼손좌표계 앞으로갈수록 -
//perpective는 fov 시야각(라디안) 추가
//만든행렬을 상수버퍼로 shade로
//카메라 이동시 물체 반대편으로

extern W::Application application;

namespace W
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			<= b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}

	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera():
		Component(eComponentType::Camera),
		m_eType(eProjectionType::OrthoGraphic),
		m_fAspectRatio(1.f),
		m_fNear(1.f),
		m_fFal(1000.f),
		m_fSize(10.f),
		m_bitLayerMask{},
		m_vecOpaqueGameObjects{},
		m_vecCutOutGameObjects{},
		m_vecTransparentGameObjects{},
		m_mView{},
		m_mProjection{}
	{
		//레이어 마스크 전부 true로 초기화
		EnableLayerMasks();
	}
	Camera::~Camera()
	{
		
	}
	void Camera::Initialize()
	{
		
	}
	void Camera::Update()
	{	

	}
	void Camera::LateUpdate()
	{
		//lateupdate마다 내 카메라의 뷰행렬, 투영행렬 구하기
		CreateViewMatrix();
		CreateProjectionMatrix(m_eType);

		//업데이트마다 오브젝트에 카메라추가하고 그리기
		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		//각각의 카메라마다 다른 뷰,투영행렬
		View = m_mView;
		Projection = m_mProjection;

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();

		RenderOpaque();

		//불투명 먼저 그리고 같은 z값에 투명을 그리면 z값 우선순위에서 밀려서 안그려짐
		//z버퍼 끄기
		DisablDepthStencilState();
		//불투명 -> 반투명 -> 투명
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}
	
	void Camera::RegisterCameraInRenderer()
	{
		renderer::m_vecCameras.push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType _eType, bool _bEnable)
	{
		m_bitLayerMask.set((UINT)_eType, _bEnable);
	}

	void Camera::TurnUILayerMask()
	{
		for (UINT i = 0; i < (UINT)eLayerType::End; ++i)
		{
			if (i == (UINT)eLayerType::UI)
				continue;

			m_bitLayerMask.set(i, false);
		}

	}

	void Camera::AlphaSortGameObjects()
	{
		// 렌더링 되기 전에 다 지우고 다시 정렬
		//투명이 가장 뒤에 렌더링
		m_vecOpaqueGameObjects.clear();
		m_vecCutOutGameObjects.clear();
		m_vecTransparentGameObjects.clear();

		Scene* pScene = SceneManger::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			//레이어마스크 true인 오브젝트만 렌더링
			if (m_bitLayerMask[i] == true)
			{
				Layer& layer = pScene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> vecGameObjects =
					layer.GetGameObjects();

				DivideAlphaBlendGameObjects(vecGameObjects);
			}
		}
	}

	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(m_vecCutOutGameObjects.begin(),
			m_vecCutOutGameObjects.end(),
			CompareZSort);

		std::sort(m_vecTransparentGameObjects.begin(),
			m_vecTransparentGameObjects.end(),
			CompareZSort);

	}
	
	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> _vecGameObj)
	{
		for (GameObject* obj : _vecGameObj)
		{
			MeshRenderer* pMeshRender =
				obj->GetComponent<MeshRenderer>();

			if (pMeshRender == nullptr)
				continue;

			std::shared_ptr<Material> spMater = pMeshRender->GetMaterial();
			eRenderingMode eMode = spMater->GetRenderinMode();

			switch (eMode)
			{
			case eRenderingMode::Opaque:
				m_vecOpaqueGameObjects.push_back(obj);
				break;
			case eRenderingMode::CutOut:
				m_vecCutOutGameObjects.push_back(obj);
				break;
			case eRenderingMode::Transparent:
				m_vecTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}


	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : m_vecOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : m_vecCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : m_vecTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}

	bool Camera::CreateViewMatrix()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();

		m_mView = Matrix::Identity;
		m_mView *= Matrix::CreateTranslation(-vPos);//카메라의 반대로 물체가 이동
		
		Vector3 up = pTr->Up();
		Vector3 right = pTr->Right();
		Vector3 foward = pTr->Foward();

		//.을 활용하여 행렬 데이터에 접근
		//카메라의 기저벡터를 활용해서 회전(오일러각X)
		//createlookat함수도 가능 하지만 전자에 비해서 느림
		Matrix mViewRotate;
		mViewRotate._11 = right.x;	mViewRotate._12 = up.x;	mViewRotate._13 = foward.x;
		mViewRotate._21 = right.y;	mViewRotate._22 = up.y;	mViewRotate._23 = foward.y;
		mViewRotate._31 = right.z;	mViewRotate._32 = up.z;	mViewRotate._33 = foward.z;
		m_mView *= mViewRotate;

		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType _eType)
	{
		RECT tRect = {};
		GetClientRect(application.GetHwnd(), &tRect);
		float fWidth = tRect.right - tRect.left; //1400
		float fHeight = tRect.bottom - tRect.top; //750
		m_fAspectRatio = fWidth / fHeight; //가로 / 세로

		if (_eType == eProjectionType::OrthoGraphic)
		{
			//orthorgraphic비율
			float fOrthorGraphicRatio = m_fSize / 1000.f;
			fWidth *= fOrthorGraphicRatio;
			fHeight *= fOrthorGraphicRatio;

			//왼손좌표계 투영행렬
			m_mProjection = Matrix::CreateOrthographicLH(fWidth, fHeight, m_fNear, m_fFal);
		}
		else
		{
			m_mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.f, m_fAspectRatio, m_fNear, m_fFal);
		}


		return true;
	}
	
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::m_cpDepthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	void Camera::DisablDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::m_cpDepthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	
}
