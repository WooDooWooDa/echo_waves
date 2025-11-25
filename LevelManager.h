#pragma once
#include <vector>
#include "Level.h"
#include <typeindex>

class LevelManager
{
private:
	// inline declaration & definition, possible with c++ 17
	inline static std::shared_ptr<Level> currentLevel = nullptr;
	inline static std::unordered_map<std::type_index, std::vector<GameObject*>> currentLevelObjectsCache;

	bool levelLoaded = false;
	int nbLevels = 10;
	std::vector<std::shared_ptr<Level>> levels;

public:
	Level* LoadAndInitSpecialLevel(string);
	bool LoadAllLevels();
	int GetNbLevels() const { return nbLevels; }
	Level* GetCurrentLevel() const;
	void SetCurrentLevel(int);
	std::shared_ptr<Level> GetLevel(int levelNumber);

	// GameObject Management
	static void AddGameObjectToLevel(std::shared_ptr<GameObject> obj) {
		if (currentLevel != nullptr) {
			currentLevel->AddGameObject(obj);
			if (obj->shouldCache)
				InvalidateCache();
		}
	}

	static void RemoveGameObjectFromLevel(std::shared_ptr<GameObject> obj) {
		if (currentLevel != nullptr) {
			currentLevel->RemoveGameObject(obj);
			if (obj->shouldCache)
				InvalidateCache();
		}
	}

	template <typename T>
	static vector<T*> GetObjectsOfType() {
		std::type_index key(typeid(T));

		// Check cache
		auto it = currentLevelObjectsCache.find(key);
		if (it != currentLevelObjectsCache.end()) {
			// Cache hit, return pre-casted objects
			return reinterpret_cast<std::vector<T*>&>(it->second);
		}

		vector<GameObject*> objs;
		auto& allObjects = currentLevel->GetAllGameObjects();
		T* casted = nullptr;
		for (auto& obj : allObjects) {
			casted = dynamic_cast<T*>(obj.get());
			if (casted) {
				objs.push_back(casted);
			}
		}
		currentLevelObjectsCache.insert({ key, objs });
		return reinterpret_cast<std::vector<T*>&>(objs);
	}

	static void InvalidateCache() {
		currentLevelObjectsCache.clear();
	}
};

