#include "Entity.h"

Entity::Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layerMask, const float& width, const float& height)
    : textured(true), texture(texture), attributes(attributes), layer(layer), layerMask(layerMask), width(width), height(height), destroyed(false), parent(nullptr) {
}

Entity::Entity(const uint8_t& layer, const uint8_t& layerMask, const float& width, const float& height)
    : textured(false), layer(layer), layerMask(layerMask), width(width), height(height), destroyed(false), parent(nullptr) {
}

Entity::~Entity() {
}

void Entity::SetTag(std::string tag) {
    this->tag = tag;
}

void Entity::Move(const float& x, const float& y) {
    prevPosition.x = this->position.x;
    prevPosition.y = this->position.y;
    this->position.x += x;
    this->position.y += y;
}

void Entity::Move(const Vector2& vec) {
    prevPosition.x = this->position.x;
    prevPosition.y = this->position.y;
    this->position.x += vec.x;
    this->position.y += vec.y;
}

void Entity::Destroy() {
    destroyed = true;
}

bool Entity::IsColliding(Entity* other) {
    if (!(other->layer & layerMask) || other == this) {
        return false;
    }

    if (position.x < other->position.x + other->width &&
        position.x + width > other->position.x &&
        position.y < other->position.y + other->height &&
        position.y + height > other->position.y) {
        return true;
    }
    return false;
}

void Entity::Update() {
    if (destroyed)
        return;

    OnUpdate();
}

void Entity::Draw(Renderer* renderer) {
    if (destroyed)
        return;
    
    if (textured)
        renderer->DrawSprite(position.x, position.y, texture, attributes);
    
    OnDraw(renderer);

#ifdef _DEBUG
    if (debugCollider)
        DrawCollider(renderer);
#endif
}

#ifdef _DEBUG
void Entity::DrawCollider(Renderer* renderer) {
    wchar_t colliderChar = L'\u2593';
    renderer->DrawRect(position.x, position.y, width, height, colliderChar, 0xbc);
}
#endif