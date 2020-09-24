#include "Entity.h"

Entity::Entity(const Texture& texture, const WORD& attributes, const uint8_t layer, const uint8_t layerMask, const float width, const float height, const Vector2 hitboxOffset)
    : textured(true), texture(texture), attributes(attributes), layer(layer), layerMask(layerMask), width(width), height(height), destroyed(true), parent(nullptr), depth(0), hitboxOffset(hitboxOffset) {
}

Entity::Entity(const uint8_t layer, const uint8_t layerMask, const float width, const float height, const Vector2 hitboxOffset)
    : textured(false), layer(layer), layerMask(layerMask), width(width), height(height), destroyed(true), parent(nullptr), depth(0), hitboxOffset(hitboxOffset) {
}

Entity::~Entity() {
}

void Entity::SetTag(std::string tag) {
    this->tag = tag;
}

void Entity::SetStatic(bool st) {
    staticBody = st;
    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Entity::Move(const float& x, const float& y) {
    if (staticBody)
        return;
    prevPosition.x = this->position.x;
    prevPosition.y = this->position.y;
    this->position.x += x;
    this->position.y += y;
}

void Entity::Move(const Vector2& vec) {
    if (staticBody) 
        return;
    prevPosition.x = this->position.x;
    prevPosition.y = this->position.y;
    this->position.x += vec.x;
    this->position.y += vec.y;
}

void Entity::SetPosition(const Vector2& vec) {
    prevPosition.x = this->position.x;
    prevPosition.y = this->position.y;
    this->position.x = vec.x;
    this->position.y = vec.y;
}

void Entity::Destroy(bool free) {
    destroyed = true;
    toFree = free;
}

bool Entity::IsValidInstance()
{
    return !destroyed;
}

bool Entity::IsColliding(Entity* other, CollisionData* data) {
    if (!(other->layer & layerMask) || other == this 
            || !colliderEnabled || ! other->colliderEnabled) {
        return false;
    }

    float ox = hitboxOffset.x;
    float oy = hitboxOffset.y;
    float oox = other->hitboxOffset.x;
    float ooy = other->hitboxOffset.y;

    bool x = position.x + ox < other->position.x + other->width + oox &&
        position.x + width + ox > other->position.x + oox;
    bool y = position.y + oy < other->position.y + other->height + ooy &&
        position.y + height + oy > other->position.y + ooy;

    if (x && y) {
        if (data != nullptr) {
            // Collision direction check
            bool vert = (prevPosition.x + width + ox < other->prevPosition.x + oox
                && position.x + width + ox >= other->position.x + oox)
                || (prevPosition.x + ox >= other->prevPosition.x + other->width + oox
                    && position.x + ox < other->position.x + other->width + oox);

            bool hor = (prevPosition.y + height + oy < other->prevPosition.y + ooy
                && position.y + height + oy >= other->position.y + ooy)
                || (prevPosition.y + oy >= other->prevPosition.y + other->height + ooy
                    && position.y + oy < other->position.y + other->height + ooy);

            if (hor) data->direction = CollisionData::Direction::HOR;
            else if (vert) data->direction = CollisionData::Direction::VERT;
        }
        return true;
    }
    return false;
}

void Entity::EnableCollider(bool enable) {
    colliderEnabled = enable;
}

void Entity::SetOnLayer(uint8_t layerBit, bool state) {
    if (state) {
        layer |= 1 << layerBit;
    }
    else {
        layer &= ~(1 << layerBit);
    }
}

void Entity::SetCollisionLayer(uint8_t layerBit, bool state) {
    if (state) {
        layerMask |= 1 << layerBit;
    } else {
        layerMask &= ~(1 << layerBit);
    }
}

void Entity::Update() {
    if (destroyed)
        return;

    OnUpdate();
}

void Entity::Draw(Renderer* renderer) {
    if (destroyed)
        return;
    
    if (textured && visible)
        renderer->DrawTexture(position.x, position.y, texture, attributes, depth);
    
    OnDraw(renderer);

#ifdef _DEBUG
    if (debugCollider)
        DrawCollider(renderer);
#endif
}

#ifdef _DEBUG
void Entity::DrawCollider(Renderer* renderer) {
    if (parent->parent->GetAppTicks() % 60 > 20)
        return;
    wchar_t colliderChar = L'\u2593';
    WORD color = colliderEnabled ? 0xbc : 0xcb;
    renderer->DrawRect(position.x + hitboxOffset.x, position.y + hitboxOffset.y, width, height, colliderChar, color, 127);
}
#endif