#pragma once
#include <unordered_map>
#include "GameObject.h"

// Needed ??
struct CellCoordHasher {
    std::size_t operator()(const vector2& c) const {
        // Fast hash, minimal collisions
        return (std::hash<int>()(c.X) * 73856093) ^
            (std::hash<int>()(c.Y) * 19349663);
    }
};

class AccelerationGrid
{
private:
	int cellSize;
    // This map is to get a list of all objs in a cell
    std::unordered_map<vector2, std::vector<GameObject*>, CellCoordHasher> cells;
    // This map is to recall in which cells the obj was
	std::unordered_map<GameObject*, std::vector<vector2>> objectCellMap;

public:
	AccelerationGrid(int size) : cellSize(size) {}

    void Insert(GameObject*);
    void Update(GameObject*);
    void Remove(GameObject*);
    void Query(GameObject*, std::vector<GameObject*>&) const;

private:
    void RemoveFromOldCells(GameObject*, std::vector<vector2>&);
    void AddToNewCells(GameObject*, std::vector<vector2>&);
    void GetOccupiedCells(const GameObject*, std::vector<vector2>&) const;
};

