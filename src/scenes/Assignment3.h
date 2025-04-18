#pragma once

#include "core/Simple2DScene.h"
#include "../objects/Circle.h"

class Assignment3 : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment 3 "; };

    void computeTrajectory(glm::vec2 vel);

    private:
    Circle myCircle;
};
