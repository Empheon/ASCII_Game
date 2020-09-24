#include "Scene.h"
#include "Entity.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::Update() {
	auto it = entities.begin();
	while (it != entities.end()) {
		if ((*it)->destroyed) {
			Entity* e(*it);
			it = entities.erase(it);
			if (e->toFree)
				delete e;
		} else {
			(*it)->Update();
			++it;
		}
	}
	CheckCollisions();
	OnUpdate();

	for (auto& e : entitiesToInit) {
		entities.push_back(e);
		e->parent = this;
		e->destroyed = false;
		e->OnInit();
		
	}
	entitiesToInit.clear();
}

void Scene::Draw(Renderer* renderer) {
	auto it = entities.begin();
	OnPreDraw(renderer);
	while (it != entities.end()) {
		(*it)->Draw(renderer);
		++it;
	}
	OnPostDraw(renderer);
}

void Scene::CheckCollisions() {
	auto itY = entities.begin();
	
	while (itY != entities.end()) {
		auto itX = entities.begin();
		while (itX != entities.end()) {
			Entity::CollisionData data;
			if ((*itY)->IsColliding(*itX, &data)) {
				(*itY)->OnCollision(*itX, &data);
			}
			++itX;
		}
		++itY;
	}
}

void Scene::Instantiate(Entity* entity, const Vector2 position) {
	entity->SetPosition(position);
	entitiesToInit.push_back(entity);
}

void Scene::Destroy(Entity* entity, bool free) {
	entity->Destroy(free);
	entity->parent = nullptr;
	entity->OnDestroy();
}

std::vector<Entity*> Scene::FindByTag(std::string tag) {
	std::vector<Entity*> filtered;
	/*auto it = std::copy_if(entities.begin(), entities.end(), filtered.begin(), [tag](Entity* e) {
		return e->tag == tag; 
	});
	filtered.resize(std::distance(filtered.begin(), it));*/
	for (auto& e : entities) {
		if (e->tag == tag) {
			filtered.push_back(e);
		}
	}
	return filtered;
}

// TODO: Add a find by type