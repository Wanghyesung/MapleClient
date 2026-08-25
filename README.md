# MapleStory Multiplayer

<div align="center">

**2D 횡스크롤 멀티플레이어 액션 RPG**
자체 제작 DirectX11 엔진 + 자체 제작 IOCP 비동기 서버로 구현한 실시간 멀티플레이 게임입니다.
클라이언트와 서버가 한 저장소에 함께 들어 있으며, **본인 PC에서 서버를 직접 구동해야 플레이할 수 있는 개인 프로젝트**입니다.

</div>

---

## 목차

- [소개](#소개)
- [스크린샷](#스크린샷--보스-레이드)
- [주요 기능](#주요-기능)
- [조작법](#조작법)
- [기술 스택](#기술-스택)
- [아키텍처](#아키텍처)
- [서버 성능 최적화](#서버-성능-최적화)
- [프로젝트 구조](#프로젝트-구조)
- [빌드 & 실행](#빌드--실행)
- [트러블슈팅](#트러블슈팅)

---

## 소개

**MapleStory Multiplayer**는 2D 횡스크롤 MMORPG의 핵심 재미인 "여럿이서 함께 보스를 잡는 경험"을 처음부터 끝까지 1인 개발로 구현한 프로젝트입니다.

- 렌더링·입력·리소스 관리 등 클라이언트 엔진(`Engine`, `Engine_Source`)을 DirectX11 기반으로 직접 제작
- 실시간 동기화를 담당하는 게임 서버(`IOCP_SERVER`)를 IOCP 기반 비동기 네트워크 라이브러리(`IOCP`)로 제작
- 클라이언트 ↔ 서버 통신은 Protobuf로 직렬화한 패킷을 주고받는 구조
- 캐릭터 위치, 애니메이션, 스킬 판정 등은 서버 권위(server-authoritative) 방식으로 동기화

> 개발 기간: 2025.03 ~ 2025.08 · 개발 인원: 1인 · 개발 환경: Visual Studio 2022 (C++)

---

## 스크린샷 · 보스 레이드

현재 4종의 보스 레이드가 구현되어 있으며, 모두 멀티플레이로 동시에 도전할 수 있습니다.

| 혼테일 (Horntail) | 핑크빈 (Pink Bean) |
|:---:|:---:|
| ![Horntail](docs/screenshots/boss_horntail.jpg) | ![Pink Bean](docs/screenshots/boss_pinkbean.jpg) |

| 매그너스 (Magnus) | 데미안 (Damien) |
|:---:|:---:|
| ![Magnus](docs/screenshots/boss_magnus.jpg) | ![Damien](docs/screenshots/boss_damien.jpg) |

*(위 스크린샷은 실제 멀티플레이 플레이 영상에서 발췌한 인게임 화면입니다.)*

---

## 주요 기능

### 🎮 플레이어 액션
- **이동**: `A` `S` `D` `W` 키를 이용한 좌우 이동 및 사다리 상호작용
- **기본 공격**: `X` 키로 표창(수리검) 투척
- **스킬 시스템**: 화면의 스킬 UI를 클릭해 원하는 스킬을 1~5차 슬롯에 등록하면, 이후 매핑된 키보드 키만으로 즉시 사용 가능한 액션바 구조
- 점프, 매달리기, 엎드리기, 기절/실신 등 세분화된 플레이어 상태 머신(FSM) 기반 동작

### 👹 보스 레이드 (멀티플레이)
- 여러 클라이언트가 동시에 접속해 같은 보스를 동시에 공략
- **혼테일** — 다중 머리·즉사기 패턴을 가진 드래곤 레이드
- **핑크빈** — 소환수(미니빈)를 동반하는 광역 딜링 보스
- **매그너스** — 암흑룡 형상의 고속 이동형 보스
- **데미안** — 공중 부유 지형에서 진행되는 광역 패턴 보스

### 🌐 실시간 동기화
- 서버가 각 클라이언트의 Transform(위치)을 보간(Interpolation)하여 전달 → 끊김 없는 부드러운 이동 동기화
- 변경분만 전송하는 dirty-flag 방식으로 불필요한 패킷 트래픽 최소화

---

## 조작법

| 입력 | 동작 |
|---|---|
| `A` / `D` | 좌 / 우 이동 |
| `W` | 사다리·로프 상호작용 |
| `S` | 아래 방향 상호작용 (플랫폼 하강 등) |
| `Space` | 점프 |
| `X` | 기본 공격 (표창 투척) |
| `마우스로 스킬 장착 `| 스킬 UI에서 등록한 1~5차 스킬 사용 |
| 마우스 클릭 (스킬 UI) | 스킬을 원하는 키에 매핑/등록 |

---

## 기술 스택

| 영역 | 사용 기술 |
|---|---|
| 언어 | C++17 |
| 그래픽스 | DirectX11, FW1FontWrapper(폰트), FMOD(사운드) |
| 네트워크(서버) | Windows IOCP, 완전 비동기 Recv/Send, 워커 스레드 = CPU 코어 수 |
| 직렬화 | Google Protocol Buffers |
| 데이터베이스 | SQL Server LocalDB, ODBC Driver 17 |
| 동시성 제어 | 자체 제작 커스텀 Read-Write SpinLock, 자체 제작 Thread Pool |
| 메모리 관리 | 자체 제작 고정 크기 Memory Pool / Pool Allocator (동적 할당 최소화) |
| IDE / 툴체인 | Visual Studio 2022 (MSVC v143), Windows x64 |



## 서버 성능 최적화

포트폴리오 발표 자료에서 다룬 핵심 최적화 포인트입니다.

- **Memory Pool** — 패킷처럼 생성·소멸이 잦은 객체를 위해 헤더(`MemoryHeader`) + 고정 크기 블록 배열 기반의 자체 메모리 풀을 설계. 런타임 동적 할당 호출 자체를 제거해 할당/해제 비용과 단편화를 구조적으로 억제
- **ReadWrite SpinLock** — 32비트 원자 변수 하나를 상위 16비트(쓰기 스레드 ID) / 하위 16비트(읽기 카운트)로 분리해 락을 구현. STL 대기 기반 락 대비 컨텍스트 스위칭 비용이 큰 임계구역이 짧은 상황(메모리 풀 등)에 특화
- **Thread Pool** — 씬 전환 시 리소스 로딩을 워커 스레드 풀로 병렬화하여 대기 시간 단축
- **IOCP 워커 스레드** — 워커 스레드 수를 CPU 코어 수에 맞춰 고정, 컨텍스트 스위칭·락 경합을 최소화하며 대규모 동시 접속에 대응
- **Transform 동기화** — dirty-flag + 서버 측 보간으로 순간이동 없는 부드러운 위치 동기화

> 각 최적화 항목의 설계 배경과 Before/After 수치는 별도 포트폴리오 슬라이드에 상세히 정리되어 있습니다.

---

## 프로젝트 구조

```
MapleServer/
├─ Client/            # 게임 클라이언트 진입점 (WinMain), 실행 파일: Editor_Window.exe
├─ Engine/             # 게임플레이 로직 (플레이어 FSM, 보스 스크립트, 스킬, UI 등)
├─ Engine_Source/      # DirectX11 렌더링 · 입력 · 리소스 등 코어 엔진
├─ IOCP/               # 범용 IOCP 비동기 네트워크 라이브러리 (Memory Pool, RWLock, SendBuffer 등)
├─ IOCP_SERVER/        # 게임 서버 로직 (Session, PacketHandler, Room, DB 연동)
├─ Database/           # ServerDB 생성 스크립트 (CreateServerDb.sql)
├─ Resources/          # 게임 데이터, 사운드, 파티클 등 에셋
├─ Lib / External/     # 서드파티 라이브러리 (Protobuf, DirectXTex, FMOD, FW1FontWrapper 등)
└─ Engine_SERVER.sln   # 전체 빌드 솔루션
```

---

## 빌드 & 실행

### 1. 사전 준비물
- Visual Studio 2022 (C++ 데스크톱 개발 워크로드, MSVC v143)

```

### 2. 빌드
```
Engine_SERVER.sln 을 Visual Studio 2022로 열고 Debug|x64 (또는 Release|x64) 구성으로 전체 솔루션 빌드
```

### 3. 실행 순서 (중요)

> ⚠️ 이 프로젝트는 클라이언트-서버 구조이므로, **로컬 PC에서 서버(IOCP_SERVER)가 먼저 켜져 있어야** 클라이언트가 접속·플레이됩니다. 별도의 상시 운영 서버는 없으며, 저장소를 내려받아 실행하는 사람 본인의 컴퓨터가 곧 서버입니다.

1. 빌드된 서버(클라이언트 실행 파일 내 IOCP_SERVER 로직)가 DB 연결에 성공하며 기동
2. 이후 `x64/Debug/Editor_Window.exe` (클라이언트)를 실행해 `127.0.0.1:7777`로 접속
3. 여러 개의 클라이언트 인스턴스를 동시에 실행하면 멀티플레이로 함께 플레이 가능


<div align="center">

**왕혜성** · Solo Developer
[GitHub Repository](https://github.com/Wanghyesung/MapleClient)

</div>
