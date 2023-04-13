#pragma once
#include <entt/entt.hpp>
#include <nlohmann/json.hpp>
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
    std::string fileName = "Default Scene.json";
};

class SceneInput {
public:
    SceneInput(const std::string& json_string);
    void nextRoot();
    void operator()(std::underlying_type_t<entt::entity>& s);
    void operator()(entt::entity& entity);
    template<typename T>
    void operator()(entt::entity& ent, T& t);
private:
    nlohmann::json root;
    nlohmann::json current;

    int root_idx = -1;
    int current_idx = 0;
};

class SceneOutput {
public:
    SceneOutput();
    void operator()(std::underlying_type_t<entt::entity> size);
    void operator()(entt::entity entity);
    template<typename T>
    void operator()(entt::entity ent, const T& t);
    void close();
    const std::string asString();
    const std::vector<uint8_t> asBson();
    void writeToFile(std::string);
private:
    nlohmann::json root;
    nlohmann::json current;
};

namespace Components {
    struct Transform {
        std::array<float, 3> position = {0, 0, 0};
        std::array<float, 3> rotation = { 0, 0, 0 };
        std::array<float, 3> scale = { 0, 0, 0 };
    };
    struct Camera {
        Transform transform;
        float angle;
    };
    inline void to_json(nlohmann::json& nlohmann_json_j, const Transform& nlohmann_json_t);
    inline void from_json(const nlohmann::json& nlohmann_json_j, Transform& nlohmann_json_t);
    inline void to_json(nlohmann::json& nlohmann_json_j, const Camera& nlohmann_json_t);
    inline void from_json(const nlohmann::json& nlohmann_json_j, Camera& nlohmann_json_t);
}