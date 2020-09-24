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
    struct CollisionData {
        enum class Direction { VERT, HOR };
        Direction direction;
        float penDistance;
    };

    virtual std::string GetType() const = 0;

    std::string tag;
    Texture texture;
    WORD attributes;
    int8_t depth;

    Vector2 position;
    Vector2 prevPosition;
    Vector2 hitboxOffset;
    float width;
    float height;

    uint8_t layer;
    uint8_t layerMask;
    bool staticBody = false;

    bool textured = false;
    bool destroyed;

    Entity(const Texture& texture, const WORD& attributes, const uint8_t layer, const uint8_t layermask, const float width, const float height, const Vector2 hitboxOffset = {0.0f, 0.0f});
    Entity(const uint8_t layer, const uint8_t layerMask, const float width, const float height, const Vector2 hitboxOffset = { 0.0f, 0.0f });
    Entity() {};
    virtual ~Entity();

    void Update();
    void Draw(Renderer* renderer);

    void SetTag(std::string tag);
    void SetStatic(bool st = true);
    void Move(const float& x, const float& y);
    void Move(const Vector2& vec);
    void SetPosition(const Vector2& vec);

    void Destroy();
    bool IsColliding(Entity* other, CollisionData* data = nullptr);

    virtual void OnInit() {};
    virtual void OnDestroy() {};
    virtual void OnUpdate() {};
    virtual void OnDraw(Renderer* renderer) {};
    virtual void OnCollision(Entity* other, const CollisionData* data) {};

#ifdef _DEBUG
    bool debugCollider = true;
    void DrawCollider(Renderer* renderer);
#endif

protected:
    Scene* parent;
};

