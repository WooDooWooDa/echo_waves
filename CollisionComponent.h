#pragma once
#include <SDL3/SDL_rect.h>
#include "CollisionLayers.h"
#include "CollisionResult.h"

class GameObject; // forward declare so compiler knows it exists

class CollisionComponent
{
private:
    GameObject* owner;
    ECollisionLayer layer;

public:
    bool isTrigger = false;
    bool isCollidable = true;

    void SetOwner(GameObject* o) {
        owner = o;
    }
    void SetLayer(ECollisionLayer l) {
        layer = l;
    }
    ECollisionLayer GetLayer() { return layer; }

    void OnTriggerEnter(GameObject*);
    void OnCollisionEnter(CollisionResult);
    bool IsTrigger() const { return isTrigger; }
    bool IsCollisionEnable() const { return isCollidable; }
    bool Intersects(const GameObject&, SDL_FRect&);
};

