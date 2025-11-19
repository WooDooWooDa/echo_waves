#include "AccelerationGrid.h"

void AccelerationGrid::Insert(GameObject* obj)
{
    // Check if already in grid
    auto found = objectCellMap.find(obj);
    if (found != objectCellMap.end()) return;

    std::vector<vector2> inCells;
    GetOccupiedCells(obj, inCells);

    // Save in which cells this obj is
    objectCellMap[obj] = inCells;

    AddToNewCells(obj, inCells);
}

void AccelerationGrid::Update(GameObject* obj)
{
    std::vector<vector2> newCells;
    GetOccupiedCells(obj, newCells);

    auto& oldCells = objectCellMap[obj];

    // No change? skip (fast path)
    if (oldCells == newCells)
        return;

    RemoveFromOldCells(obj, oldCells);

    AddToNewCells(obj, newCells);

    //objectCellMap[obj] = inCells; SAME as vvv since oldCells is a ref&
    oldCells = newCells;
}

void AccelerationGrid::Remove(GameObject* obj)
{
    auto& oldCells = objectCellMap[obj];
    //auto it = objectCellMap.find(obj);
    //if (it == objectCellMap.end()) return;

    RemoveFromOldCells(obj, oldCells);

    objectCellMap.erase(obj);
}

void AccelerationGrid::Query(GameObject* obj, std::vector<GameObject*>& results) const
{
    results.clear();

    //std::vector<vector2> inCells;
    //GetOccupiedCells(obj, inCells);
    // .find() is faster by a small margin
    auto inCells = objectCellMap.find(obj);
    if (inCells == objectCellMap.end()) return;

    for (auto& cell : inCells->second) {
        auto found = cells.find(cell);
        if (found == cells.end()) continue;
        
        for (auto& objInCell : found->second) {
            results.push_back(objInCell);
        }
    }
}

void AccelerationGrid::RemoveFromOldCells(GameObject* obj, std::vector<vector2>& oldCells)
{
    for (const auto& cell : oldCells) {
        auto& objsInCell = cells[cell];
        objsInCell.erase(std::remove(objsInCell.begin(), objsInCell.end(), obj), objsInCell.end());
    }
}

void AccelerationGrid::AddToNewCells(GameObject* obj, std::vector<vector2>& newCells)
{
    for (auto& c : newCells) {
        auto& objsInCell = cells[c];
        // Check if not already in cell
        if (std::find(objsInCell.begin(), objsInCell.end(), obj) != objsInCell.end())
            continue;
        objsInCell.push_back(obj);
    }
}

void AccelerationGrid::GetOccupiedCells(const GameObject* obj, std::vector<vector2>& outCells) const
{
    auto bounds = obj->GetBounds();
    int x0 = (int)floor(bounds.x / cellSize);
    int y0 = (int)floor(bounds.y / cellSize);
    int x1 = (int)floor((bounds.x + bounds.w) / cellSize);
    int y1 = (int)floor((bounds.y + bounds.h) / cellSize);

    outCells.clear();

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            outCells.push_back(vector2(x, y));
        }
    }
}
