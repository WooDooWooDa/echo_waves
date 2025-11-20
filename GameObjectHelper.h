#pragma once
#include <memory>
#include <utility>
#include <type_traits>
#include "LevelManager.h"

class GameObject;

/*	Args&& -> "Take anything (lvalue or rvalue) and remember what it was."
	std::forward<Args> -> "Pass it on exactly as it came in."*/

template<typename T = GameObject, typename... Args> requires std::derived_from<T, GameObject>
static std::shared_ptr<T> Instantiate(Args&&... args) {
	auto newObj = std::make_shared<T>(std::forward<Args>(args)...);
	LevelManager::AddGameObjectToLevel(newObj);
	return newObj;
}