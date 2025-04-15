#include "Assignment4.h"

#include "imgui.h"
#include "core/Colors.h"
#include"core/Input.h"
#include <vector> 

glm::vec2 lineStart = glm::vec2(-15, -15);
glm::vec2 lineEnd = glm::vec2(15, 15);
glm::vec2 lineNormal;
glm::vec2 pos;

void Assignment4::OnEnable() {
    myCircle = Circle(1, 2, glm::vec2(0, 5), glm::vec2(0, 0));
    myCircle.ResetForceVector();

    circle2 = Circle(1, 1, glm::vec2(0, -5), glm::vec2(0, 10));
    circle2.ResetForceVector();
   
    glm::vec2 normalisedLine = glm::normalize(lineEnd - lineStart);
    lineNormal = glm::vec2(-normalisedLine.y, normalisedLine.x);
}

void Assignment4::OnDisable() {}

void Assignment4::Update(float deltaTime) {
    
    
    glm::vec2 gravity = glm::vec2(0, -9.8);

    myCircle.AddForceVector(gravity);
    circle2.AddForceVector(gravity);

    float dotPosNormal = glm::dot(myCircle.circlePosition, lineNormal);
    float distToLine = dotPosNormal - circle2.GetRadius();

    float dotPosNormal2 = glm::dot(circle2.circlePosition, lineNormal);
    float distToLine2 = dotPosNormal2 + circle2.GetRadius();

    if (distToLine <= 0) {
        //reflect
        //myCircle.circleVel.y *= -1;
        glm::vec2 reflect = glm::reflect(myCircle.circleVel, lineNormal);
        myCircle.circleVel = reflect;
    }

    if (distToLine2 >= 0) {
        glm::vec2 reflect = glm::reflect(circle2.circleVel, lineNormal);
        circle2.circleVel = reflect;
    }

    circle2.circleVel += circle2.GetTotalForceVector() / circle2.GetMass() * deltaTime;
    circle2.circlePosition += circle2.circleVel * deltaTime;
    circle2.ResetForceVector();

    myCircle.circleVel += myCircle.GetTotalForceVector() / myCircle.GetMass() * deltaTime;
    myCircle.circlePosition += myCircle.circleVel * deltaTime;
    myCircle.ResetForceVector();
}

void Assignment4::Draw() {

    Draw::Line(lineStart, lineEnd);


    Draw::SetColor(Colors::red);
    Draw::Circle(myCircle.circlePosition, myCircle.GetRadius(), Colors::red);
    Draw::Circle(circle2.circlePosition, circle2.GetRadius(), Colors::yellow);
}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    
    ImGui::End();
}
