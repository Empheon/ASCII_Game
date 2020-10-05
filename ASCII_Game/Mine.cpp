#include "Mine.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <AudioManager.h>

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

        if (lifeTime % blinkSpeed == 0) {
            AudioManager::Instance().Play(L"sounds/bip_bomb.mp3");
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
       if (lifeTime % blinkSpeed < (blinkSpeed / 4)) {
            renderer->DrawCircle(position.x, position.y, width / 2 + 1, L'\u2591', 0x0c, depth);
       }
    }
    
}

void Mine::OnCollision(Entity* other, const CollisionData* data) {
    if (other->GetType() == "Bullet" || other->GetType() == "Mine") { 
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
    parent->parent->renderer->DoScreenShake(1.2f);
    SetExplosionCollider();
    SpawnExplosionParticles();

    AudioManager::Instance().Play(L"sounds/mine_explosion.mp3");
}

void Mine::SpawnExplosionParticles() {
    const int partCount = (int) (0.6f * MINE_EXPLOSION_RANGE * MINE_EXPLOSION_RANGE);
    for (int i = 0; i < partCount; ++i) {
        if (i < partCount / 2) {
            parent->parent->particles.Emit(Mine::CreateSparkleParticle(), position);
        }
        ParticleInfo info = Mine::CreateSmokeParticle();
        Vector2 offset = { RandFloatRange(-width/2, width/2), RandFloatRange(-height/3, height/3) };
        parent->parent->particles.Emit(info, position + offset);
    }
}

ParticleInfo Mine::CreateSmokeParticle() {
    ParticleInfo part = PART_MINE_SMOKE_BASE;
    part.direction = Vector2(RandFloatRange(-1.0f, 1.0f), 0.0f).Angle();
    part.gravity *= RandFloatRange(0.2f, 1.0f);
    part.color = (rand() % 2 == 0) ? 0x07 : 0x08;
    part.character = PART_CHARS_SHRINKING_CIRCLE[rand() % 4];
    part.lifeTime += rand() % 40;
    return part;
}

ParticleInfo Mine::CreateSparkleParticle() {
    ParticleInfo part = PART_MINE_SPARKLE_BASE;
    part.direction = RandFloatRange(0.0f, 2.0f * M_PI);
    part.velocity += RandFloatRange(-0.2f, 0.2f);
    part.color = (rand() % 2 == 0) ? 0x0e : 0x0c;
    part.zVelocity *= RandFloatRange(0.6f, 1.0f);
    part.character = (rand() % 2 == 0) ? L'x' : L'.';
    part.lifeTime += rand() % 60;
    return part;
}