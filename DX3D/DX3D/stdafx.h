// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#include <assert.h>//프로세스 킬 용으로 쓰는 헤더
#include <vector>
#include <map>
#include <set>
#include <list>
#include <fstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <string>
#include <atlstr.h>

using namespace std;
using std::to_string;


extern HWND g_hWnd;
#include "BaseObject.h"
#include "GlobalDefinition.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Application.h"


//조명 헤더 추가하기
#include "D3DUtility.h"
#include "DeviceManager.h"
#include "Camera.h"
//
#include "Cube.h"

#include "Cubeman_Head.h"
#include "Cubeman_Left_leg.h"
#include "Cubeman_Right_leg.h"
#include "Cubeman_Left_arm.h"
#include "Cubeman_Right_arm.h"
#include "Grid.h"
#include "KeyboardManager.h"
#include "IMap.h"
#include "IUnitObject.h"

#include "IAction.h"
#include "Debug.h"

//----매니져 류들 --------------------

#include "MapManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ObjManager.h"
#include "FontManager.h"
#include "ItemManager.h"
#include "InventoryManager.h"
#include "UIOperator.h"
#include "UIManager.h"
//#include "CharacterStatus.h"
#include "IShader.h"
#include "Shaders.h"
#include "SoundManager.h"

//#define WINSIZEX 1560
//#define WINSIZEY 990

//
//#define WINSIZEX 960
//#define WINSIZEY 540
//
#define WINSIZEX 1600
#define WINSIZEY 900

//#define WINSIZEX 1920
//#define WINSIZEY 1080



#define OriginX 1584
#define OriginY 841