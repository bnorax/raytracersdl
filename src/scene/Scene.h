#pragma once
#include <scene/JsonSerialization.h>

class Scene {
public:
	Scene();
	entt::registry& getRegistry();
	std::string serialize();
	std::unique_ptr<entt::registry> deserialize(std::string);
	void saveToFile(std::string filaName);
	void loadFromFile(std::string fileName);
private:
	std::unique_ptr<entt::registry> registry;
    std::string sceneName = "Default Scene.json";
};