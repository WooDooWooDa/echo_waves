#pragma once
#include <SDL3/SDL_rect.h>
#include "CollisionResult.h"
#include "CollisionLayers.h"

class GameObject; // forward declare so compiler knows it exists

class CollisionComponent
{
private:
    std::string tag;
    GameObject* owner;
    ECollisionLayer layer = ECollisionLayer::LNone;
    vector2 bounds; //aka collider size

public:
    bool isTrigger = false;
    bool isCollidable = true;

    void SetOwner(GameObject* o) {
        owner = o;
    }

    void SetLayer(ECollisionLayer l) {
        layer = l;
    }

    void SetTag(std::string newTag) { tag = newTag; }
    const std::string& GetTag() const 
    { return tag; }

    void SetBounds(vector2 newBounds) { bounds = newBounds; }
    SDL_FRect GetBounds() const;

    ECollisionLayer GetLayer() const { return layer; }

    void OnTriggerEnter(GameObject*);
    void OnCollisionEnter(CollisionResult);
    bool IsTrigger() const { return isTrigger; }
    bool IsCollisionEnable() const { return isCollidable; }
    bool Intersects(const CollisionComponent&, SDL_FRect&);
};

