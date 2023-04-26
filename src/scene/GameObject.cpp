#include "GameObject.h"

GameObject::GameObject(entt::entity entity) : id {entity}
{
}

entt::entity GameObject::GetEntityID()
{
	return id;
}
