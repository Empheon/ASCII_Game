#pragma once

#include <Windows.h>

#include <scene/Entity.h>

#define MINE_MAX_LIFETIME 2.0

class Mine : public Entity
{
public:
	ENTITY_TYPE(Mine);

	Mine() 
		: Entity(0b00100000, 0b00000000, 8, 8, {-4, -4}) {

	}

private:
	int lifetime;
	WORD ownerColor;
};

