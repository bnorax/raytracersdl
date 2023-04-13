#include "Scene.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Scene::Scene()
{
}

std::string Scene::serialize()
{
    using namespace Components;
    entt::basic_snapshot snapshot(registry);
    SceneOutput output;
    snapshot.entities(output).component<Transform, Camera>(output);
    output.close();
    std::string jsonOutput = output.asString();
    return jsonOutput;
}

void Scene::deserialize()
{
    using namespace Components;
    std::ifstream file("Check.json");
    std::string json;
    file >> json;
    SceneInput input(json);
    entt::registry reg;
    entt::basic_snapshot_loader loader(reg);
    loader.entities(input).component<Transform, Camera>(input);
}

void Scene::saveToFile(std::string filaName)
{
    std::string json = serialize();
    std::ifstream file(filaName);
    if(file.is_open())
        file >> json;
    file.close();
}

void Scene::loadFromFile(std::string fileName)
{
}

SceneOutput::SceneOutput()
{
    root = nlohmann::json::array();
}

void SceneOutput::operator()(std::underlying_type_t<entt::entity> size) {
    int a = 0;
    if (!current.empty()) {
        root.push_back(current);
    }
    current = nlohmann::json::array();
    current.push_back(size);
}

void SceneOutput::operator()(entt::entity entity) {
    current.push_back((uint32_t)entity);
}
template<typename T>
void SceneOutput::operator()(entt::entity ent, const T& t) {
    current.push_back((uint32_t)ent);
    nlohmann::json json;
    Components::to_json(json, t);
    current.push_back(json);
}

void SceneOutput::close() {
    if (!current.empty()) {
        root.push_back(current);
    }
}

const std::string SceneOutput::asString() {
    std::string output = root.dump();
    return output;
}

const std::vector<uint8_t> SceneOutput::asBson() {
    std::vector<std::uint8_t> as_bson = nlohmann::json::to_bson(root);
    return as_bson;
}

void SceneOutput::writeToFile(std::string fileName)
{
    std::ofstream file(fileName);
    file << root;
}

void Components::to_json(nlohmann::json& nlohmann_json_j, const Transform& nlohmann_json_t)
{
    
    nlohmann_json_j["position"] = nlohmann_json_t.position; nlohmann_json_j["rotation"] = nlohmann_json_t.rotation; nlohmann_json_j["scale"] = nlohmann_json_t.scale;
}

void Components::from_json(const nlohmann::json& nlohmann_json_j, Transform& nlohmann_json_t)
{
    nlohmann_json_j.at("position").get_to(nlohmann_json_t.position); nlohmann_json_j.at("rotation").get_to(nlohmann_json_t.rotation); nlohmann_json_j.at("scale").get_to(nlohmann_json_t.scale);
}

void Components::to_json(nlohmann::json& nlohmann_json_j, const Camera& nlohmann_json_t)
{
    to_json(nlohmann_json_j["transform"], nlohmann_json_t.transform);
   // nlohmann_json_j["transform"] = nlohmann_json_t.transform;
    nlohmann_json_j["angle"] = nlohmann_json_t.angle;
}

void Components::from_json(const nlohmann::json& nlohmann_json_j, Camera& nlohmann_json_t)
{
    from_json(nlohmann_json_j.at("transform"), nlohmann_json_t.transform);
   // nlohmann_json_j.at("transform").get_to(nlohmann_json_t.transform); 
    nlohmann_json_j.at("angle").get_to(nlohmann_json_t.angle);
}

SceneInput::SceneInput(const std::string& json_string)
{
    root = nlohmann::json::parse(json_string);
}

void SceneInput::nextRoot()
{
    root_idx++;
    if (root_idx >= root.size()) {
        // ERROR
        return;
    }
    current = root[root_idx];
    current_idx = 0;
}

void SceneInput::operator()(std::underlying_type_t<entt::entity>& s)
{
    nextRoot();
    int size = current[0].get<int>();
    current_idx++;
    s = (std::underlying_type_t<entt::entity>)size; // pass amount to entt
}
void SceneInput::operator()(entt::entity& entity)
{
    uint32_t ent = current[current_idx].get<uint32_t>();
    entity = entt::entity(ent);
    current_idx++;
}
template<typename T>
void SceneInput::operator()(entt::entity& ent, T& t) {
    nlohmann::json component_data = current[current_idx * 2];

    auto comp = component_data.get<T>();
    t = comp;

    uint32_t _ent = current[current_idx * 2 - 1];
    ent = entt::entity(_ent); // last element is the entity-id
    current_idx++;
}
