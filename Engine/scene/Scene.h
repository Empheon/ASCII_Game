#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "../Application.h"

class Entity;

class Scene
{
	friend class Application;
public:
	Scene();
	void Instantiate(Entity* entity);
	void Destroy(Entity* entity);
	std::vector<Entity*> FindByTag(std::string tag);
	
	Application* parent;

private:

	void Update();
	void CheckCollisions();
	void Draw(Renderer* renderer);

protected:
	virtual void OnLoad() {};
	virtual void OnUpdate() {};
	virtual void OnPreDraw() {}; // Draw on screen before entity drawing
	virtual void OnPostDraw() {}; // Draw on screen after entity drawing

	std::vector<Entity*> entities;
};

