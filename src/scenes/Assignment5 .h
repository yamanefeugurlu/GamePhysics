#pragma once

#include "core/Simple2DScene.h"

class Assignment5  : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment 5"; };

private:
    glm::vec2 mouseStart;
    glm::vec2 mouseEnd;
    std::vector<Circle> balls;

    float damping = 2.0f; // drag coefficient

    bool isDragging = false;
    int selectedBall = -1;
};
