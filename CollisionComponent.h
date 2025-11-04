#pragma once
#include <SDL3/SDL_rect.h>
#include "CollisionLayers.h"

class GameObject; // forward declare so compiler knows it exists

class CollisionComponent
{
private:
    GameObject* owner;
    bool isTrigger = false;
    bool isCollidable = true;
    ECollisionLayer layer;

public:
    void SetOwner(GameObject* o) {
        owner = o;
    }
    void SetLayer(ECollisionLayer l) {
        layer = l;
    }
    ECollisionLayer GetLayer() { return layer; }

    void OnTriggerEnter(GameObject*);
    void OnCollisionEnter(GameObject*);
    bool IsTrigger() const { return isTrigger; }
    bool IsCollisionEnable() const { return isCollidable; }
    bool Intersects(const GameObject&, SDL_FRect&);
};

