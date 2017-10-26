#pragma once
#include "Object.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define MAX_OBJECTS_COUNT 50

class SceneManager
{
public:
	explicit SceneManager(void);
	virtual ~SceneManager(void);

public:
	void Update(void);
	void Collision(void);

public:
	Object* m_pObject[MAX_OBJECTS_COUNT];
};