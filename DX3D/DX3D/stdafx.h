// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>//���μ��� ų ������ ���� ���
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

#include "Mouse.h"
#include "Keyboard.h"

#include "BaseObject.h"
#include "Application.h"
#include "GlobalDefinition.h"


//���� ��� �߰��ϱ�
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

//----�Ŵ��� ���� --------------------

#include "MapManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ObjManager.h"
#include "FontManager.h"
#include "SoundManager.h"

#define WINSIZEX 1560
#define WINSIZEY 990