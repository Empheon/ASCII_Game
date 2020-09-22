#pragma once
#include "../render/Texture.h"
#include "../render/Renderer.h"
#include "Scene.h"
#include "../Vector2.h"

#define ENTITY_TYPE(x) virtual std::string GetType() const { return #x; }

class Entity
{
    friend class Scene;
public:
    virtual std::string GetType() const = 0;

    std::string tag;
    Texture texture;
    WORD attributes;
    Vector2 position;
    Vector2 prevPosition;
    float yPrev;
    float width;
    float height;

    uint8_t layer;
    uint8_t layerMask;

    bool textured = false;
    bool destroyed;

    Entity(const Texture& texture, const WORD& attributes, const uint8_t& layer, const uint8_t& layermask, const float& width, const float& height);
    Entity(const uint8_t& layer, const uint8_t& layerMask, const float& width, const float& height);
    Entity() {};
    virtual ~Entity();

    void Update();
    void Draw(Renderer* renderer);

    void SetTag(std::string tag);
    void Move(const float& x, const float& y);
    void Move(const Vector2& vec);

    void Destroy();
    bool IsColliding(Entity* other);

    virtual void OnInit() {};
    virtual void OnDestroy() {};
    virtual void OnUpdate() {};
    virtual void OnDraw(Renderer* renderer) {};
    virtual void OnCollision(Entity* other) {};

protected:
    Scene* parent;
};

