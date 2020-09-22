#include "Scene.h"
#include "Entity.h"

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
	entity->parent = this;
	entity->OnInit();
}

void Scene::Destroy(Entity* entity) {
	entity->Destroy();
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