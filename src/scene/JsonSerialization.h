#pragma once

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
private:
    nlohmann::json root;
    nlohmann::json current;
};