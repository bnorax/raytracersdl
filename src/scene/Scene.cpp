#include "Scene.h"
#include <scene/components/Components.h>

using json = nlohmann::json;

Scene::Scene()
{
    registry = std::make_unique<entt::registry>();
}

entt::registry& Scene::getRegistry()
{
    return *registry;
}

std::string Scene::serialize()
{
    using namespace Components;
    entt::basic_snapshot snapshot(*registry);
    SceneOutput output;
    snapshot.entities(output).component<Transform, Camera>(output);
    output.close();
    std::string jsonOutput = output.asString();
    return jsonOutput;
}

std::unique_ptr<entt::registry> Scene::deserialize(std::string json)
{
    using namespace Components;
    SceneInput input(json);
    std::unique_ptr<entt::registry> reg = std::make_unique<entt::registry>();
    entt::basic_snapshot_loader loader(*reg);
    loader.entities(input).component<Transform, Camera>(input);
    return reg;
}

void Scene::saveToFile(std::string fileName = "Default Scene.json")
{
    std::string json = serialize();
    std::ofstream file(fileName);
    if(file.is_open())
        file << json;
    file.close();
}

void Scene::loadFromFile(std::string fileName)
{
    std::string json;
    std::ifstream file(fileName);
    if (file.is_open()) {
        file >> json;
        this->sceneName = fileName;
    }
    file.close();
    registry = deserialize(json);
}
