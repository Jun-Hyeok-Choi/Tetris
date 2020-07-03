#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <algorithm>
#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include "resource2.h"

#pragma comment(lib,"winmm")

#include "Interface.h"
#include "Block.h"

#include <iostream>
using namespace std;

static const int FrameX = GetSystemMetrics(SM_CXFRAME);
static const int FrameY = GetSystemMetrics(SM_CYFRAME);
static const int CaptionY = GetSystemMetrics(SM_CYCAPTION);
static const int WindowX = 500 + (FrameX << 2);
static const int WindowY = 650 + (FrameY << 2) + CaptionY;
static const int WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - WindowX) / 2;
static const int WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - WindowY) / 2;

