#include "Assignment2Scene.h"

#include "imgui.h"
#include "../objects/Circle.h"
#include "core/Colors.h"


Circle circle = Circle(1, 1, glm::vec2(0, 7.5), glm::vec2(15, 15));
float mass = 1;
void Assignment2Scene::OnEnable() 
{
    
}

void Assignment2Scene::OnDisable() {}

void Assignment2Scene::Update(float deltaTime) 
{
    circle.SetMass(mass);
    glm::vec2 gravity = glm::vec2(0, -9.8);

    //circle.AddForceVector(gravity);

    if (circle.circlePosition.y - circle.GetRadius() < -15) 
    {
        circle.AddForceVector(glm::vec2(0,25));
        
    }

    if (circle.circlePosition.y - circle.GetRadius() > 15)
    {
        circle.AddForceVector(glm::vec2(0, -25));
    }

    if (circle.circlePosition.x - circle.GetRadius() > 15) 
    {
        circle.AddForceVector(glm::vec2(-25, 0 ));
    }

    if (circle.circlePosition.x - circle.GetRadius() < -15) 
    {
        circle.AddForceVector(glm::vec2(25, 0));
    }
    
    // v = v +A*deltaT
    circle.circleVel += circle.GetTotalForceVector() / circle.GetMass() * deltaTime;


    circle.circlePosition += circle.circleVel * deltaTime;

    circle.ResetForceVector();
}

void Assignment2Scene::Draw() 
{
    Draw::SetColor(Colors::white);
    Draw::Circle(circle.circlePosition, circle.GetRadius());
    Draw::Line(glm::vec2(-15, -15) , glm::vec2(15, -15));
    Draw::Line(glm::vec2(-15, 15), glm::vec2(15, 15));
    Draw::Line(glm::vec2(-15, -15), glm::vec2(-15, 15));
    Draw::Line(glm::vec2(15, -15), glm::vec2(15, 15));

    if (Input::IsMouseDown(0)) {
        Draw::SetColor(Colors::red);
    }

    Draw::Circle(Input::GetMousePos(), 1);

}

void Assignment2Scene::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::DragFloat("Mass", &mass, 0.1f);

    if (ImGui::Button("Reset")) {
        circle.SetPos(glm::vec2(0,0));
    }
    ImGui::End();
}
