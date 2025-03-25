#pragma once

#include "..\Engine_Source\Common.h";
#include "..\Engine_Source\Engine.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"
#include "..\Engine_Source\WGraphics.h"

//colldier 내 onwer 정보를 디버그메쉬에 전달하고 디버그 오브젝트에서 콜라이더를 그림
//디버그오브젝트가 UI카메라 행렬를 받아서 같이 움직임
//0번 main카메라로 셋팅해서 0번 메인카메라의 뷰 투영 행렬로 그림
// 원 콜라이더 만들기

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const W::graphics::DebugMesh& _mesh);

	private:
		static std::vector<Widget*> m_vecWidgets;
		static std::vector<EditorObject*> m_vecEditorObjects;
		static std::vector<DebugObject*> m_vecDebugOjbects;
	};
}


