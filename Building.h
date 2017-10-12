#pragma once
#include "Object.h"

class Building : public Object
{
public:
	explicit Building(void);
	virtual ~Building(void);

public:
	virtual bool Init(void);
	virtual void Output(void);
	virtual void Update(void);

private:
	void Release(void);
};