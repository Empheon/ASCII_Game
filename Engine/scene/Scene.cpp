#include "Scene.h"

Scene::Scene() {
}

void Scene::Update() {
	auto it = entities.begin();
	while (it != entities.end()) {
		if ((*it)->destroyed) {
			it = entities.erase(it);
		} else {
			(*it)->Update();
			++it;
		}
	}
	OnUpdate();
}

void Scene::Draw(Renderer* renderer) {
	auto it = entities.begin();
	OnPreDraw();
	while (it != entities.end()) {
		(*it)->Draw(renderer);
		++it;
	}
	OnPostDraw();
}

void Scene::CheckCollisions() {

}

void Scene::Instantiate(Entity* entity) {
	entities.push_back(entity);
	entity->OnInit();
}

void Scene::Destroy(Entity* entity) {
	entity->Destroy();
	entity->OnDestroy();
}