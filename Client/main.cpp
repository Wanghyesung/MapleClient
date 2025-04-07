//정적라이브러리 추가 1. 소스코드  2. 비주얼스튜디오 옵션
//정적라이브러리에 들어가기 위한 헤더파일 include 

//참조 -> 엔진소수 추가


//정적라이브러리의 commoninclude헤더파일 include해야 알수있음
//#include "..\Client_Source\CommonInclude.h"

////하나하나 전부 해줄 수 없기 때문에
//#include "CommonInclude.h"
//
////디버그일떄 Debug파일에 정적라이브러리를 참조하고 Release일때는 Release파일에 정적라이브러리 참조
#ifdef _DEBUG
#pragma comment (lib,"..\\x64\\Debug\\Engine.lib")
#pragma comment(lib, "IOCP\\Debug\\IOCP.lib")
#pragma comment(lib, "ProtoBuf\\Debug\\libprotobufd.lib")

#else
#pragma comment (lib, "..\\x64\\Release\\Engine.lib")
#pragma comment(lib, "IOCP\\Release\\IOCP.lib")
#pragma comment(lib, "ProtoBuf\\Release\\libprotobufd.lib")

#endif


//공유 항목 프로젝트는 어느 플랫폼이여도 사용가능하기 때문에
//빌드 중속성 굳이 하나하나 빌드가 아니라 하나를 돌리면 같이 빌드되게
//engine -> editer
//기존 클래스 복사 -> 기존항복에 추가 
//c++ 버전 20으로
#include "framework.h"
#include "Client.h"
#include "..\Engine_Source\WApplication.h"
#include "..\Engine_Source\WRenderer.h"
#include "..\Engine_Source\WResources.h"

#include "..\Engine_Source/WFmod.h"
#include "..\Engine_Source\WFontWrapper.h"
#include "..\Engine\LoadScene.h"
#include "..\Engine_Source\WThreadPool.h"

#include "guiEditor.h"

//셰이더 만들어진 후 셋팅
//layout 설정 -> setpustate에서 레이아웃 속성설정 
//레이아웃 설정할 떄 vertexbuffer2진코드 덩어리 필요 
//레아이웃 셰이더에 묶어서 
//상수버퍼는 class안에 묶어서 -> 자주 사용하기 때문에, cpu에 데이터를 gpu로 보내야하기 떄문
//구조화 버퍼는 배열같은 큰 데이터를 보내는 용도
//버퍼를 만들때 ㅏ용하는 id3d11buffer클래스는 밖에 따로 뺴둠
//따로 만든 버퍼 struct를 모든 버퍼 부모로 사용 (똑같이 사용하는 id3d11buffer 보관)
//wrl
//gpu연결 -> shader 연결
//상수버퍼 만들때 데이터 크기(vertex)만 인자값으로 넣고 안에 옵션은 고정
//constbuffer 생성자에 무슨 타입인지 실행중에 바뀌면 안되기 때문
//ecs 기존의 컴포넌트 방식이 아니라 시스템이 가지고있는 데이터만 업데이트들 돌리기 , 헬스라는 데이터를
//가지고있지않으면 업데이트를 하지않음 연속적으로 데이터(주소)를 가지고있자 
//헬스는 헬스대로 트렌스폼은 프랜스폼대로 배열로 가지고있자
//컴포넌트는 다른 컴포넌트의 주소를 가져와서 바꿀 수 있지만 ecs는 예외처리를 많이 해야함 한 배열에 다 묶여있기때문
//스크립트도 유니티 compont 처럼 끌어서 쓸 수 있도록

//gpu(buffer)와 cpu 데이터를 묶음 subresourec와 buffer 엮고 
//데이터전달 후 unmap
//마이크로소프트 texture github다운
//directXtex빌드 둘다 빌드, 데스크톱 2-22 win10 x64 
//내 폴더에 external  directXTex ->lib정적라이브러리(릴리스, 디버그)에 (두개)lib넣기, (실행에필요한 헤더파일)include Tex.h, Tex.inl 넣기
//헤더 인라인 include, lib파일 추가(#pragma)모드 따로해서


//샘플링작업을 해주지않아도 비주얼스튜디오에서 알아서 보간처리를 해줌
//안티에일리어싱 (계단현상을 없애기) 샘플링 알고리즘
//Point 픽셀 그대로 가져오기
//비등방성
//만든 샘플링도 다른 texutre와 똑같이 shader와 묶어준다
//메테리얼, 렌더패스 텍스쳐를 셰이더러를 통해서 어떻게 그릴지 정함
//텍스쳐 쉐이더 전부 메테리얼이 가지고있게
//상수버퍼또한 위치기반만있는것이아니라 다른 정보도 넘겨줄수있게 배열로
//오브젝트 생성시 mesh, meshrender초기화
//메테리얼을 만들때마다 shader, texture또한 만들어서 넣어주기

//스킬립트형 component 배열로 컴포넌트 추가할때 따로 푸쉬
//둘중에 먼저 update될지 순서를 설정
//오브젝트 로직은 스크립트에서
//std라이브러리의 자료형을 캐스팅하기 위해서는 pointcast로
//리소스 관련한 데이터는 sharedptr로

//게임안의 모든 벡터의 중심은 월드좌표계(0,0)를 기준으로
//cos함수 비용이 많이 들기 때문에 벡터 두개(단위벡터) 내적해서 각도를 구하는게 비용이 싸다
//cos구하고 acos을 통해서 각도를 구할수있음
//SRT(월드행렬)


//alignas(16)16바이트로만 사용
//transform에서 월드행렬, 카메라에서 뷰행렬 투영행렬 관리
//view porjection은 똑같이 
//srt의 순서아 맞춰서 달라지면 공전
//
W::Application application;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(27098);
    // TODO: 여기에 코드를 입력합니다.
    
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 게임 로직이 돌아가야한다.
            application.Run();
            gui::Editor::Run();

            application.Present();
        }
    }

    renderer::Release();
    //W::Resources::Release();//전부 shadered_ptr로 바꿈 알아서 해제

    W::ThreadPool::Shutdown();
    W::SceneManger::Release();
    //W::BattleManager::Release();
    W::Fmod::Release();
    W::FontWrapper::Release();
    gui::Editor::Release();

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;// MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1400, 750, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    application.SetWindow(hWnd, 1400, 750);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    application.Initialize();
    W::InitializeScenes();
    gui::Editor::Initialize();

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
