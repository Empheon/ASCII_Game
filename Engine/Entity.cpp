#include "Entity.h"

Entity::Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layerMask, const float& width, const float& height)
    : texture(texture), attributes(attributes), layer(layer), layerMask(layerMask), width(width), height(height)
{
}

Entity::~Entity()
{
}

void Entity::Move(const float& x, const float& y)
{
    float tmpX = posX + x;
    float tmpY = posY + y;

    /*if (tmpX < 0) posX = 0;
    else if (tmpX + width >= Application::width) posX = Application::width - width;

    if (tmpY < 0) posY = 0;
    else if (tmpY + height >= Application::height) posY = Application::height - height;*/
}

bool Entity::CollisionCheck(Entity* other) {
    if (!(other->layer & layerMask)) {
        return false;
    }

    if (posX < other->posX + other->width &&
        posX + width > other->posX &&
        posY < other->posY + other->height &&
        posY + height > other->posY) {
        return true;
    }
}

void Entity::Draw()
{
    Application::renderer->DrawSprite(posX, posY, texture, attributes);
}
