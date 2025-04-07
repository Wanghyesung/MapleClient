#pragma once

#include <vector>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <queue>
#include <memory>
#include <typeindex>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::wstring;
using std::string;
using std::unordered_map;
using std::pair;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::static_pointer_cast;

#include <functional>
#include <typeinfo>
#include <assert.h>
#include <random>
#include <string>

// FileSystem
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using namespace std::experimental;
using namespace std::experimental::filesystem;



#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>					// DirectX11
#include <d3dcompiler.h>			// Shader ÄÄÆÄÀÏ
#include <DirectXMath.h>			// DX Math
#include <DirectXPackedVector.h>	

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

