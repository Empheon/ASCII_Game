#pragma once

#include <Windows.h>

#include <scene/Entity.h>

#define MINE_MAX_LIFETIME 2.0

class Mine : public Entity
{
public:
	ENTITY_TYPE(Mine);

	Mine();

private:
	int lifetime;
	WORD ownerColor;
};

