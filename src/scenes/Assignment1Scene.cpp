#include "Assignment1Scene.h"


#include "core/Draw.h"
#include "imgui.h"

void Assignment1Scene::OnEnable() {
    glm::vec2 initPos;
    initPos = {0, 3};

    lineLength = 5;

    circlePosition = circlePosition + initPos;

    circleRadius = 1;

    circleVel = {0, 0};

    
}

void Assignment1Scene::OnDisable() {}

void Assignment1Scene::Update(float deltaTime) {

    float gravity = 9.81f;

    circleVel.y -= gravity * deltaTime;

    

    if (circlePosition.y - bottomLineOriginPos.y < circleRadius) {
        circleVel.y += -circleVel.y + bounceForce;
    }

    circlePosition += circleVel * deltaTime;
}

void Assignment1Scene::Draw() {
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-lineLength, bottomLineOriginPos.y),
               glm::vec2(lineLength, bottomLineOriginPos.y));

    Draw::Line(glm::vec2(-lineLength, topLineOriginPos.y),
               glm::vec2(lineLength, topLineOriginPos.y));

    Draw::Line(glm::vec2(rightLineOriginPos.x, lineLength),
               glm::vec2(rightLineOriginPos.x, -lineLength));

    Draw::Line(glm::vec2(leftLineOriginPos.x, lineLength),
               glm::vec2(leftLineOriginPos.x, -lineLength));


}

void Assignment1Scene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat2("Bottom Line", &bottomLineOriginPos[0], 0.1f);
    ImGui::DragFloat2("Top Line", &topLineOriginPos[0], 0.1f);
    ImGui::DragFloat2("Right Line", &rightLineOriginPos[0], 0.1f);
    ImGui::DragFloat2("Left Line", &leftLineOriginPos[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::DragFloat("Bounce Force", &bounceForce, 0.1f);
    ImGui::End();
}
