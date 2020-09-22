#pragma once
#include "render/Texture.h"
#include "render/Renderer.h"

#include "Application.h"

class Entity
{
public:
    Texture texture;
    WORD attributes;
    float posX;
    float posY;
    float width;
    float height;

    uint8_t layer;
    uint8_t layerMask;

    Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layermask, const float& width, const float& height);
    Entity() {};
    ~Entity();

    void Move(const float& x, const float& y);
    bool CollisionCheck(Entity* other);
    void Draw();

    virtual void Update() = 0;
    virtual void OnCollision(Entity* other) = 0;
};

