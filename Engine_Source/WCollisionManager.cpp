#include "WCollisionManager.h"
#include "WGameObject.h"
#include "WScene.h"
#include "WSceneManger.h"
#include "WLayer.h"
#include "WCollider2D.h"
#include "WRenderer.h"
namespace W
{
	std::bitset<LAYER_MAX> CollisionManager::m_bitMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::m_mapCollision = {};

	void CollisionManager::Initialize()
	{

	}

	void CollisionManager::Update()
	{
		for (UINT column = 0 ;column < (UINT)eLayerType::End; ++column)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; ++row)
			{
				if (m_bitMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}

	}
	void CollisionManager::LayerCollision(eLayerType _eLeft, eLayerType _eRight)
	{
		Scene* pActiveScene = SceneManger::GetActiveScene();

		const std::vector<GameObject*>& vecLeftObj =
			pActiveScene->GetLayer(_eLeft).GetGameObjects();

		const std::vector<GameObject*>& vecRightObj =
			pActiveScene->GetLayer(_eRight).GetGameObjects();

		for (GameObject* pLObj : vecLeftObj)
		{
			Collider2D* pLeftCol = pLObj->GetComponent<Collider2D>();
			if (pLeftCol == nullptr)
				continue;
			if (!pLeftCol->IsActive())
				continue;
			if (pLObj->GetState() != GameObject::eState::Active)
				continue;


			for (GameObject* pRObj : vecRightObj)
			{
				Collider2D* pRightCol = pRObj->GetComponent<Collider2D>();
				if (pRightCol == nullptr)
					continue;
				if (!pRightCol->IsActive())
					continue;
				if (pRObj->GetState() != GameObject::eState::Active)
					continue;
				if (pRObj == pLObj)
					continue;

				ColliderCollision(pLeftCol,pRightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* _pLeft, Collider2D* _pRight)
	{
		ColliderID ID = {};
		ID.m_iLeft = _pLeft->GetColliderID();
		ID.m_iRight = _pRight->GetColliderID();

		std::map<UINT64, bool>::iterator iter =
			m_mapCollision.find(ID.ID);

		//처음 들어온 충돌체
		if (iter == m_mapCollision.end())
		{
			m_mapCollision.insert(std::make_pair(ID.ID, false));
			iter = m_mapCollision.find(ID.ID);
		}

		if (Intersect(_pLeft, _pRight))
		{
			if (iter->second == false)
			{
				_pLeft->OnCollisionEnter(_pRight);
				_pRight->OnCollisionEnter(_pLeft);
			}
			else
			{
				_pLeft->OnCollisionStay(_pRight);
				_pRight->OnCollisionStay(_pLeft);
			}
			iter->second = true;
		}
		else
		{
			if (iter->second == true)
			{
				_pLeft->OnCollisionExit(_pRight);
				_pRight->OnCollisionExit(_pLeft);
			}
			iter->second = false;
		}
	}
	bool CollisionManager::Intersect(Collider2D* _pLeft, Collider2D* _pRight)
	{

	//	//각각의 사각형의 축 2개 * 2
	//	GameObject* vLeftObj  = _pLeft->GetOwner();
	//	GameObject* vRightObj = _pRight->GetOwner();
	//	Transform* pLObjTr = vLeftObj->GetComponent<Transform>();
	//	Transform* pRObjTr = vRightObj->GetComponent<Transform>();
	//		
	//
	////Vector3 vPos = pLObjTr->GetPosition() + pLObjTr->Up()* pLObjTr->GetScale().y * 0.5f;
	//// 
	//	//두 오브젝트의 기준축(L벡터) 2*2 4번 검사
	//	Vector3 vLAxis[2] = { pLObjTr->Right(), pLObjTr->Up()};
	//	Vector3 vRAxis[2] = { pRObjTr->Right(), pRObjTr->Up()};
	//
	//	// R -> L 벡터 T
	//	Vector3 vDiffLen = pLObjTr->GetPosition() - pRObjTr->GetPosition();
	//
	//	if (vLAxis[0] == Vector3::Zero) return false;
	//	//왼쪽 오브젝트의 기준축으로 검사
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		// L dot T 
	//		Vector3 vAxisX = vLAxis[i];
	//
	//		//T에 투영된 L(기준축)벡터 (길이)
	//		float fDistance = abs(vDiffLen.Dot(vAxisX));
	//	
	//		//각각의 오브젝트 (내적(오브젝트의 업벡터 * 크기(반)) +  내적(오브젝트의 오른쪽벡터 * 크기(반)) 크기가 fDistance보다 작아야함
	//		//만약 fDistance가 더 크면 분리축이 존재
	//		float fDiff = 0.f;
	//		fDiff += abs(vAxisX.Dot(pLObjTr->Up() * pLObjTr->GetScale().y * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pLObjTr->Right() * pLObjTr->GetScale().x * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pRObjTr->Up() * pRObjTr->GetScale().y * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pRObjTr->Right() * pRObjTr->GetScale().x * 0.5f));
	//
	//		if (fDiff < fDistance)
	//			return false;
	//	}
	//	
	//	//오른쪽 오브젝트의 기준축으로 검사
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		// L dot T
	//		Vector3 vAxisX = vRAxis[i];
	//
	//		//T에 투영된 L벡터 (길이)
	//		float fDistance = abs(vDiffLen.Dot(vAxisX));
	//
	//		//각각의 오브젝트 (내적(오브젝트의 업벡터 * 크기(반)) +  내적(오브젝트의 오른쪽벡터 * 크기(반)) 크기가 fDistance보다 작아야함   
	//		float fDiff = 0.f;
	//		fDiff += abs(vAxisX.Dot(pLObjTr->Up() * pLObjTr->GetScale().y * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pLObjTr->Right() * pLObjTr->GetScale().x * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pRObjTr->Up() * pRObjTr->GetScale().y * 0.5f));
	//		fDiff += abs(vAxisX.Dot(pRObjTr->Right() * pRObjTr->GetScale().x * 0.5f));
	//
	//		if (fDiff < fDistance)
	//			return false;
	//	}
	//	
	//	return true;

		//내 정점 정보
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* pLeftTr = _pLeft->GetOwner()->GetComponent<Transform>();
		Transform* pRightTr = _pRight->GetOwner()->GetComponent<Transform>();


		Matrix mLeftMatrix = pLeftTr->GetMatrix();
		Matrix mRightMatrix = pRightTr->GetMatrix();

		//왼쪽 오른쪽 사각형 기준축
		Vector3 vAxis[4] = {};
		
		Vector3 vLeftScale = Vector3(_pLeft->GetSize().x, _pLeft->GetSize().y, 1.f);
		Vector3 vRightScale = Vector3(_pRight->GetSize().x, _pRight->GetSize().y, 1.f);

		Matrix mFinalLeft = Matrix::CreateScale(vLeftScale);//XMMatrixScaling
		mFinalLeft *= mLeftMatrix;

		Matrix mFinalRight = Matrix::CreateScale(vRightScale);
		mFinalRight *= mRightMatrix;

		//x, y축 기준축 벡터
		vAxis[0] = Vector3::Transform(arrLocalPos[1], mFinalLeft); //XMVector3TransformCoord(arrLocalPos[1], mFinalLeft);
		vAxis[1] = Vector3::Transform(arrLocalPos[3], mFinalLeft);
		vAxis[2] = Vector3::Transform(arrLocalPos[1], mFinalRight);
		vAxis[3] = Vector3::Transform(arrLocalPos[3], mFinalRight);
		
		vAxis[0] = vAxis[0] - Vector3::Transform(arrLocalPos[0], mFinalLeft);
		vAxis[1] = vAxis[1] - Vector3::Transform(arrLocalPos[0], mFinalLeft);
		vAxis[2] = vAxis[2] - Vector3::Transform(arrLocalPos[0], mFinalRight);
		vAxis[3] = vAxis[3] - Vector3::Transform(arrLocalPos[0], mFinalRight);

		for (UINT i = 0; i < 4; ++i)
			vAxis[i].z = 0.f;

		Vector3 vDiff;
		if(_pLeft->GetCenter() == Vector2::Zero && _pRight->GetCenter() == Vector2::Zero)
			vDiff = pLeftTr->GetPosition() - pRightTr->GetPosition();
		else
			vDiff = _pLeft->GetPosition() - _pRight->GetPosition();
		vDiff.z = 0.f;

		Vector3 vCenter = vDiff;

		for (UINT i = 0; i < 4; ++i)
		{
			Vector3 Axis = vAxis[i];
			float fProjDistance = 0.f;

			for (UINT j = 0; j < 4; ++j)
			{
				fProjDistance += fabsf(vAxis[j].Dot(Axis) / 2.f);
			}

			if(fProjDistance < fabsf(vCenter.Dot(Axis)))
				return false;
		}

		return true;
	}

	void CollisionManager::SetLayer(eLayerType _eLeft, eLayerType _eRight, bool _bEnable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)_eLeft;
		UINT iRight = (UINT)_eRight;


		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		m_bitMatrix[col][row] = _bEnable;
	}
	void CollisionManager::Clear()
	{
		for (int i = 0; i < m_bitMatrix->size(); ++i)
		{
			m_bitMatrix[i].reset();
		}

		m_mapCollision.clear();
	}

	void CollisionManager::erase(ColliderID _tCollID)
	{
		std::map<UINT64, bool>::iterator iter =
			m_mapCollision.find(_tCollID.ID);

		//처음 들어온 충돌체
		if (iter == m_mapCollision.end())
			return;

		m_mapCollision.erase(_tCollID.ID);
	}
}