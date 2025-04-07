#include "Assignment1Scene.h"


#include "core/Draw.h"
#include "imgui.h"

void Assignment1Scene::OnEnable()
{
    glm::vec2 initPos;
    initPos = { 0, 3 };
    bottomLineOriginPos = { 0, -5 };
    topLineOriginPos = { 0, 5 };
    leftLineOriginPos = { -5, 0 };
    rightLineOriginPos = { 5, 0 };
    lineLength = 5;
    bounceForce = 6;

    bounceForceMult = 1;

    circlePosition = circlePosition + initPos;

    circleRadius = 1;

    circleVel = { 6, 1 };


}

void Assignment1Scene::OnDisable() {}

void Assignment1Scene::Update(float deltaTime)
{

    float gravity = 9.81f;

    circleVel.y -= gravity * deltaTime;


    // Bounce off bottom or top
    if (circlePosition.y - bottomLineOriginPos.y < circleRadius && circleVel.y < 0)
    {

        circleVel.y += -circleVel.y + (bounceForce * bounceForceMult);
        bounceForceMult *= 0.85f;
    }

    if (topLineOriginPos.y - circlePosition.y < circleRadius && circleVel.y > 0)
    {
        circleVel.y += -circleVel.y - (bounceForce * bounceForceMult);
        bounceForceMult *= 0.85f;
    }

    // Bounce off left or right
    if (circlePosition.x - leftLineOriginPos.x < circleRadius && circleVel.x < 0)
    {

        circleVel.x += -circleVel.x + (bounceForce * bounceForceMult);
        bounceForceMult *= 0.85f;
    }

    if (rightLineOriginPos.x - circlePosition.x < circleRadius && circleVel.x > 0) 
    {
        circleVel.x += -circleVel.x - (bounceForce * bounceForceMult);
        bounceForceMult *= 0.85f;
    }

    

    if (bounceForceMult < 0.01f) 
    {
        bounceForceMult = 0;
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
    ImGui::DragFloat("Bounce Force Mult", &bounceForceMult, 0.1f);
    ImGui::End();
}
