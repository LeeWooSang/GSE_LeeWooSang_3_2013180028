#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
using namespace std;

#define WIDTH 500
#define HEIGHT 600

#define Window_Half_WIDTH WIDTH * 0.5f
#define Window_Half_HEIGHT HEIGHT * 0.5f

#define KING_TOWER_POS_X 0

#define RED_TEAM 0
#define BLUE_TEAM 1

#define MAX_OBJECTS_COUNT 300

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

#define ANIMATION_COOLTIME 0.1f

#define INIT_RED_TEAM_CHARACTER_TIME 1.f
#define INIT_BLUE_TEAM_CHARACTER_TIME 1.f

#define INIT_BULLET_TIME 1.f
#define INIT_ARROW_TIME 1.f