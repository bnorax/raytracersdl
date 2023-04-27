#pragma once
namespace Components {
    struct Transform {
        std::array<float, 3> position { 0, 0, 0 };
        std::array<float, 3> rotation { 0, 0, 0 };
        std::array<float, 3> scale { 0, 0, 0 };
    };
    struct Camera {
        float sensitivityX = 2.0f;
        float sensitivityY = .005f;

        float minimumY = 0.0f;
        float maximumY = 360.0f;

        float minimumX = -20.0f;
        float maximumX = 60.0f;
        //float angle {0.0f};
    };
    struct Parent {
        entt::entity parent{ entt::null };
    };

}