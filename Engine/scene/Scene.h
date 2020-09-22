#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "Entity.h"
#include "../Application.h"

class Scene
{
	friend class Application;
public:
	Scene();
	
	Application* parent;

private:

	void Update();
	void CheckCollisions();
	void Draw(Renderer* renderer);

protected:
	void Instantiate(Entity* entity);
	void Destroy(Entity* entity);

	virtual void OnLoad() {};
	virtual void OnUpdate() {};
	virtual void OnPreDraw() {}; // Draw on screen before entity drawing
	virtual void OnPostDraw() {}; // Draw on screen after entity drawing

	std::vector<Entity*> entities;
};

