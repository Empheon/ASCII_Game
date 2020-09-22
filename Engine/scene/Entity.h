#pragma once
#include "../render/Texture.h"
#include "../render/Renderer.h"
#include "Scene.h"

class Entity
{
    friend class Scene;
public:
    std::string tag;
    Texture texture;
    WORD attributes;
    float x;
    float y;
    float width;
    float height;

    uint8_t layer;
    uint8_t layerMask;

    bool destroyed;

    Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layermask, const float& width, const float& height);
    Entity() {};
    ~Entity();

    void Update();
    void Draw(Renderer* renderer);

    void SetTag(std::string tag);
    void Move(const float& x, const float& y);

    void Destroy();

    virtual void OnInit() {};
    virtual void OnDestroy() {};
    virtual void OnUpdate() {};
    virtual void OnDraw(Renderer* Renderer) {};
    virtual void OnCollision(Entity* other) {};

protected:
    Scene* parent;
};

