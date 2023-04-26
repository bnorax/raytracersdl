#pragma once
#include <scene/JsonSerialization.h>
#include <scene/GameObject.h>

class Scene {
public:
	Scene();
	entt::registry& getRegistry();
	void saveToFile(std::string filaName);
	void loadFromFile(std::string fileName);

	GameObject& createGameObject();
	void deleteGameObject(GameObject&);
	template<typename T>
	T& addComponent(GameObject& object) {
		return registry->emplace<T>(object.GetEntityID());
	}
	template<typename T>
	T& getComponent(GameObject& object) {
		return registry->get<T>(object.GetEntityID());
	}

	void Start();
	void Update();
	/*template<typename T>
	T& updateComponent(GameObject& object, T& updatedComponent = nullptr) {
		if(updateComponent)
			return registry->replace<T>(object.GetEntityID(), updatedComponent);
		else
			return registry->patch<T>(object.GetEntityID());
	}*/
	///void createGameObject();
private:
	std::string serialize();
	std::unique_ptr<entt::registry> deserialize(std::string);
	std::unique_ptr<entt::registry> registry;
	std::vector<GameObject> objects;
    std::string sceneName = "Default Scene.json";
};