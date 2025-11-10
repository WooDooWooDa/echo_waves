#pragma once
#include <SDL3/SDL_rect.h>
#include "CollisionResult.h"
#include "CollisionLayers.h"
#include <unordered_set>

class GameObject; // forward declare so compiler knows it exists

class CollisionComponent
{
private:
    std::string tag;
    GameObject* owner;
    ECollisionLayer layer = ECollisionLayer::LNone;
    vector2 bounds; //aka collider size

    std::unordered_set<GameObject*> currentOverlaps;

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

    std::unordered_set<GameObject*>& GetCurrentOverlaps() {
        return currentOverlaps;
    }
};

