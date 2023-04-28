#pragma once
namespace Components {
    struct Transform {
        std::array<float, 3> position { 0, 0, 0 };
        std::array<float, 3> rotation { 0, 0, 0 };
        std::array<float, 3> scale { 0, 0, 0 };
    };
    struct Camera {
        float sensitivityX = 0.1f;
        float sensitivityY = 0.1f;

        float minimumY = -19;
        float maximumY = 19;

        float minimumX = -20.0f;
        float maximumX = 60.0f;
        //float angle {0.0f};
    };
    struct Parent {
        entt::entity parent{ entt::null };
    };

}