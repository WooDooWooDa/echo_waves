#pragma once
#include <SDL3/SDL_rect.h>
#include "CollisionResult.h"
#include "CollisionLayers.h"
#include <unordered_set>
#include "CollisionType.h"

class GameObject; // forward declare so compiler knows it exists

class CollisionComponent
{
private:
    std::string tag;
    GameObject* owner;
    ECollisionLayer layer = ECollisionLayer::LNone;
    ECollisionType type = ECollisionType::STATIC;
    vector2 bounds; //aka collider size

    std::unordered_set<GameObject*> currentOverlaps;

public:
    bool isTrigger = false;
    bool isCollidable = true;

    void SetOwner(GameObject* o) {
        owner = o;
    }

    ECollisionLayer GetLayer() const { return layer; }
    CollisionComponent* SetLayer(ECollisionLayer l) {
        layer = l;
        return this;
    }

    ECollisionType GetCollisionType() const { return type; }
    CollisionComponent* SetCollisionType(ECollisionType t) {
        type = t;
        return this;
    }

    void SetTag(std::string newTag) { tag = newTag; }
    const std::string& GetTag() const 
    { return tag; }

    void SetBounds(vector2 newBounds) { bounds = newBounds; }
    SDL_FRect GetBounds() const;

    void OnTriggerEnter(GameObject*);
    void OnTriggerStay(GameObject*);
    void OnTriggerExit(GameObject*);
    void OnCollisionEnter(CollisionResult);
    bool IsTrigger() const { return isTrigger; }
    bool IsCollisionEnable() const { return isCollidable; }
    bool Intersects(const CollisionComponent&, SDL_FRect&);

    void RegisterOverlap(GameObject* other) {
        currentOverlaps.insert(other);
    }

    bool IsOverlapping(GameObject* other) const {
        return currentOverlaps.find(other) != currentOverlaps.end();
    }

    void ClearOverlap(GameObject* other) {
        currentOverlaps.erase(other);
    }

    void ClearAllOverlaps() {
        currentOverlaps.clear();
    }

    std::unordered_set<GameObject*>& GetCurrentOverlaps() {
        return currentOverlaps;
    }
};

