#include "Entity.h"

Entity::Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layerMask, const float& width, const float& height)
    : texture(texture), attributes(attributes), layer(layer), layerMask(layerMask), width(width), height(height), destroyed(false), posX(0), posY(0) {
}

Entity::~Entity() {
}

void Entity::Move(const float& x, const float& y) {
    posX += x;
    posY += y;

    /*if (tmpX < 0) posX = 0;
    else if (tmpX + width >= Application::width) posX = Application::width - width;

    if (tmpY < 0) posY = 0;
    else if (tmpY + height >= Application::height) posY = Application::height - height;*/
}

void Entity::Destroy() {
    destroyed = true;
}

//bool Entity::CheckCollisions(Entity* other) {
//    if (!(other->layer & layerMask)) {
//        return false;
//    }
//
//    if (posX < other->posX + other->width &&
//        posX + width > other->posX &&
//        posY < other->posY + other->height &&
//        posY + height > other->posY) {
//        return true;
//    }
//    return false;
//}

void Entity::Update() {
    if (destroyed)
        return;

    OnUpdate();
}

void Entity::Draw(Renderer* renderer) {
    if (destroyed)
        return;
    
    renderer->DrawSprite(posX, posY, texture, attributes);
    OnDraw(renderer);
}
