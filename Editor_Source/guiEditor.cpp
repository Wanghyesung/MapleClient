#include "guiEditor.h"
#include "..\Engine\WGridScript.h"
#include "..\Engine_Source\WMesh.h"
#include "..\Engine_Source\WResources.h"
#include "..\Engine_Source\WTransform.h"
#include "..\Engine_Source\WMeshRenderer.h"
#include "..\Engine_Source\WMaterial.h"
#include "..\Engine_Source\WRenderer.h"


namespace gui
{
	using namespace W::enums;
	std::vector<Widget*> Editor::m_vecWidgets = {};
	std::vector<EditorObject*> Editor::m_vecEditorObjects = {};
	std::vector<DebugObject*> Editor::m_vecDebugOjbects = {};


	void Editor::Initialize()
	{
		m_vecDebugOjbects.resize((UINT)eColliderType::End);
		
		std::shared_ptr<W::Mesh> mesh
			= W::Resources::Find<W::Mesh>(L"DebugRect");
		std::shared_ptr<W::Material> material
			= W::Resources::Find<W::Material>(L"DebugMaterial");
		
		m_vecDebugOjbects[(UINT)eColliderType::Rect] = new DebugObject();
		m_vecDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<W::Transform>();
		W::MeshRenderer* mr
			= m_vecDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<W::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);
		
		
		//EditorObject* grid = new EditorObject();
		//grid->SetName(L"Grid");
		//
		//mr = grid->AddComponent<W::MeshRenderer>();
		//mr->SetMesh(W::Resources::Find<W::Mesh>(L"RectMesh"));
		//mr->SetMaterial(W::Resources::Find<W::Material>(L"GridMaterial"));
		//W::GridScript* gridSc = grid->AddComponent<W::GridScript>();
		//gridSc->SetCamera(renderer::m_vecCameras[0]);//메인카메라가 0번 인덱스
		//
		//m_vecEditorObjects.push_back(grid);

	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : m_vecEditorObjects)
		{
			obj->Render();
		}

		for (const W::graphics::DebugMesh& mesh
			: renderer::m_vecDebugMeshs)
		{
			DebugRender(mesh);
		}
		renderer::m_vecDebugMeshs.clear();
	}

	void Editor::Release()
	{
		for (auto widget : m_vecWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : m_vecEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : m_vecDebugOjbects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const W::graphics::DebugMesh& _mesh)
	{
		//collider들 가진 물체의 위치와 크기 회전을 가져와서 그 물체 위에 그림
		//미리 말든어둔 사각형 원 메쉬가진 디버그 오브젝트를 사용
		if (m_vecDebugOjbects.size() == 0)
			return;

		if (_mesh.active == false)
			return;

		DebugObject* debugObj = m_vecDebugOjbects[(UINT)_mesh.type];
		
		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		W::Transform* debugTr = debugObj->GetComponent<W::Transform>();

		//메쉬 포지션 스케일 가져오고 디버그 오브젝트 월드행렬 바인드
		Vector3 vPos = _mesh.position;
		vPos.z -= 0.01f;

		debugTr->SetPosition(vPos);
		debugTr->SetScale(_mesh.scale);
		debugTr->SetRotation(_mesh.rotation);

		//행렬 계산
		debugTr->LateUpdate();

		W::Camera* pMainCamera = renderer::MainCamera;

		//renderer에서 render하고 카메라를 전부 지우기 때문에 메인카메라
		//가져와서 메인카메라로 셋팅

		W::Camera::SetGpuViewMatrix(pMainCamera->GetViewMatrix());
		W::Camera::SetGpuProjectionMatrix(pMainCamera->GetProjectionMatrix());
		
		debugObj->Render();
	}

}