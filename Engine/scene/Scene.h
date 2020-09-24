#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "../Vector2.h"
#include "../Application.h"

class Entity;

class Scene
{
	friend class Application;
public:
	Scene();
	virtual ~Scene();
	void Instantiate(Entity* entity, const Vector2 position = {0, 0});
	void Destroy(Entity* entity, bool free = false);
	std::vector<Entity*> FindByTag(std::string tag);
	
	Application* parent;

private:
	std::vector<Entity*> entitiesToInit;

	void Update();
	void CheckCollisions();
	void Draw(Renderer* renderer);

protected:
	virtual void OnLoad() {};
	virtual void OnUpdate() {};
	virtual void OnPreDraw(Renderer* renderer) {}; // Draw on screen before entity drawing
	virtual void OnPostDraw(Renderer* renderer) {}; // Draw on screen after entity drawing

	std::vector<Entity*> entities;
};

