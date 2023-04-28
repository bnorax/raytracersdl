#include "JsonSerialization.h"
#include <scene/components/Components.h>

namespace Components {
    void to_json(nlohmann::json& nlohmann_json_j, const Transform& nlohmann_json_t) {
        nlohmann_json_j["position"] = nlohmann_json_t.position; nlohmann_json_j["rotation"] = nlohmann_json_t.rotation; nlohmann_json_j["scale"] = nlohmann_json_t.scale;
    }
    void from_json(const nlohmann::json& nlohmann_json_j, Transform& nlohmann_json_t) {
        nlohmann_json_j.at("position").get_to(nlohmann_json_t.position); nlohmann_json_j.at("rotation").get_to(nlohmann_json_t.rotation); nlohmann_json_j.at("scale").get_to(nlohmann_json_t.scale);
    }
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Camera, sensitivityX, sensitivityY, minimumY, maximumY, minimumX, maximumX)
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

template <typename T>
void SceneOutput::operator()(entt::entity ent, const T& t) {
    current.push_back((uint32_t)ent);
    nlohmann::json json;
    Components::to_json(json, t);
    current.push_back(json);
}

template void SceneOutput::operator()<Components::Transform>(entt::entity ent, const Components::Transform& t);
template void SceneOutput::operator()<Components::Camera>(entt::entity ent, const Components::Camera& t);

template void SceneInput::operator()<Components::Transform>(entt::entity& ent, Components::Transform& t);
template void SceneInput::operator()<Components::Camera>(entt::entity& ent, Components::Camera& t);
