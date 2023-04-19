#pragma once
namespace Components {
    struct Transform {
        std::array<float, 3> position { 0, 0, 0 };
        std::array<float, 3> rotation { 0, 0, 0 };
        std::array<float, 3> scale { 0, 0, 0 };
    };
    struct Camera {
        Transform transform;
        float angle {0.0f};
    };
    struct Parent {
        entt::entity parent{ entt::null };
    };

}