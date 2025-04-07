#pragma once
#include <glm/glm.hpp>
#include "core/Simple2DScene.h"

class Assignment1Scene : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment 1"; };

    private:
    glm::vec2 circlePosition;
    glm::vec2 circleVel;
    float circleRadius;
    glm::vec2 bottomLineOriginPos;
    glm::vec2 topLineOriginPos;
    glm::vec2 rightLineOriginPos;
    glm::vec2 leftLineOriginPos;
    float lineLength;
    float bounceForce;
    float bounceForceMult;
};
