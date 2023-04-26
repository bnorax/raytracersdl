#pragma once

class GameObject {
public:
	GameObject(entt::entity);
	/*template<typename T>
	void addComponent() {
	}*/
	entt::entity GetEntityID();
private:
	entt::entity id;
};