#include "Assignment3.h"

#include "imgui.h"
#include "../objects/Circle.h"
#include "core/Colors.h"
#include"core/Input.h"
#include <vector> 

glm::vec2 mouseStart;
glm::vec2 mouseEnd;
bool isDragging = false;

std::vector<glm::vec2> trajectoryPoints;




void Assignment3::OnEnable() {
    
    myCircle = Circle(1, 2, glm::vec2(1, 1), glm::vec2(0, 0));
}

void Assignment3::OnDisable() {}

void Assignment3::Update(float deltaTime) {

    

    glm::vec2 gravity = glm::vec2(0, -9.8);

    myCircle.AddForceVector(gravity);
    

    //  click
    if (Input::IsMouseClicked(0)) {
        isDragging = true;
        myCircle.SetPos(Input::GetMousePos());
        myCircle.SetVelocity(glm::vec2(0, 0));
    }

    // dragging
    if (isDragging) {
        mouseEnd = Input::GetMousePos();
        computeTrajectory((mouseEnd - myCircle.circlePosition) / myCircle.GetMass());

    }

    // release
    if (Input::IsMouseReleased(0) && isDragging) {
        isDragging = false;

        glm::vec2 impulse = mouseEnd - myCircle.circlePosition;
        glm::vec2 newVelocity = impulse / myCircle.GetMass();

        myCircle.SetVelocity(newVelocity);
        
    }

    myCircle.circleVel += myCircle.GetTotalForceVector() / myCircle.GetMass() * deltaTime;

    if (myCircle.circlePosition.y - 0 < myCircle.GetRadius() && myCircle.circleVel.y < 0) {
        
        myCircle.circleVel.y *= -1;
    }


    myCircle.circlePosition += myCircle.circleVel * deltaTime;

    myCircle.ResetForceVector();

}

void Assignment3::Draw() {

    Draw::Line(glm::vec2(-150, 0), glm::vec2(150, 0));

    
    
    Draw::SetColor(Colors::yellow);
    for (auto& p : trajectoryPoints) {
        Draw::Circle(p, 1);
    }

    Draw::SetColor(Colors::cyan);
    if (isDragging) {
        glm::vec2 circleCenter = myCircle.circlePosition;
        glm::vec2 currentMouse = Input::GetMousePos();
        Draw::Line(circleCenter, currentMouse);
    }

    Draw::SetColor(Colors::red);
    Draw::Circle(myCircle.circlePosition, myCircle.GetRadius(), Colors::red);


}

void Assignment3::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}


void Assignment3::computeTrajectory(glm::vec2 initialVel) {
    trajectoryPoints.clear();

    glm::vec2 pos = myCircle.circlePosition;
    glm::vec2 vel = initialVel;
    glm::vec2 gravity = glm::vec2(0, -9.8f);
    float mass = myCircle.GetMass();
    float timeStep = 0.01f;

    for (int i = 0; i < 500; ++i) {
        
        glm::vec2 acceleration = gravity / mass;
        vel += acceleration * timeStep;
        pos += vel * timeStep;

        
        if (pos.y - myCircle.GetRadius() < 0.0f && vel.y < 0.0f) {
            vel.y *= -1;                  
            pos.y = myCircle.GetRadius(); 
        }

        trajectoryPoints.push_back(pos);
    }
}
