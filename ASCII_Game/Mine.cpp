#include "Mine.h"

void Mine::OnInit() {
    depth = -20;
    lifeTime = (int) (MINE_MAX_LIFETIME * parent->parent->targetFPS);
    blinkSpeed = MINE_SLOW_BLINK_SPEED;
    exploaded = false;
    ResetCollider();
}

void Mine::OnUpdate() {
    lifeTime--;
    if (!exploaded) {
        if (lifeTime < 40 && blinkSpeed == MINE_SLOW_BLINK_SPEED) {
            blinkSpeed = MINE_FAST_BLINK_SPEED;
        }

        if (lifeTime <= 0) {
            Kaboom();
        }
    } else { // KABOOM
        if (lifeTime <= 0) {
            Destroy();
        }
    }
}

void Mine::OnDraw(Renderer* renderer) {
    if (!exploaded) {
        renderer->DrawChar(position.x, position.y, L'\u25b2', color, depth);
        if (lifeTime % blinkSpeed < (blinkSpeed / 3)) {
            renderer->DrawTexture(position.x - 1, position.y - 1, TEX_MINE_WARNING, 0x0f, 40);
        }
    } else {
        if (lifeTime % (blinkSpeed/2) < (blinkSpeed / 4)) {
            renderer->DrawCircle(position.x, position.y, width / 2 + 1, L'@', 0x0e, 40);
        }
    }
    
}

void Mine::OnCollision(Entity* other, const CollisionData* data) {
    if (other->GetType() == "Bullet" || other->GetType() == "Mine") {
        std::wstringstream ss;
        ss << "[COLLISION] " << std::endl;
        OutputDebugString(ss.str().c_str());
        Kaboom();
    } else if (other->GetType() == "Tank" && other->tag != ownerTag) {
        Kaboom();
    }
}

void Mine::SetExplosionCollider() {
    width = MINE_EXPLOSION_RANGE;
    height = MINE_EXPLOSION_RANGE;
    hitboxOffset = { -MINE_EXPLOSION_RANGE/2, -MINE_EXPLOSION_RANGE/2 };

    SetCollisionLayer(LAYER_BULLETS, false);
    SetCollisionLayer(LAYER_PLAYERS, false);
    SetCollisionLayer(LAYER_EXPLOSIONS, false);
    SetOnLayer(LAYER_EXPLOSIONS);
}

void Mine::ResetCollider() {
    width = 1;
    height = 1;
    hitboxOffset = { 0, 0 };

    SetCollisionLayer(LAYER_BULLETS);
    SetCollisionLayer(LAYER_EXPLOSIONS);
    SetCollisionLayer(LAYER_PLAYERS);
    SetOnLayer(LAYER_EXPLOSIONS, false);
}

void Mine::Kaboom() {
    exploaded = true;
    lifeTime = (int)(MINE_EXPLOSION_DURATION * parent->parent->targetFPS);
    blinkSpeed = MINE_FAST_BLINK_SPEED;
    SetExplosionCollider();
}