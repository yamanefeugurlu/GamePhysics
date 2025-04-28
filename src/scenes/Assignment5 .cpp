#include <glm/glm.hpp>
#include <vector>
#include "../objects/Circle.h"
#include "Assignment5 .h"
#include "core/Colors.h"
#include "core/Input.h"
#include "imgui.h"



// Box boundaries
glm::vec2 boxMin = glm::vec2(-30, -20);
glm::vec2 boxMax = glm::vec2(30, 20);

void Assignment5 ::OnEnable() {
    balls.clear();
    balls.push_back(Circle(2, 1, glm::vec2(-10, 0), glm::vec2(0, 0)));
    balls.push_back(Circle(2, 1, glm::vec2(10, 0), glm::vec2(0, 0)));
    balls.push_back(Circle(2, 1, glm::vec2(0, 10), glm::vec2(0, 0)));
}

void Assignment5::OnDisable() {}

void Assignment5::Update(float deltaTime) {
    // Input 
    if (Input::IsMouseClicked(0)) {
        glm::vec2 mousePos = Input::GetMousePos();
        for (int i = 0; i < balls.size(); i++) {
            if (glm::distance(balls[i].circlePosition, mousePos) <=
                balls[i].GetRadius()) {
                selectedBall = i;
                isDragging = true;
                mouseStart = mousePos;
                balls[i].SetVelocity(glm::vec2(0, 0));
                break;
            }
        }
    }

    if (isDragging && Input::IsMouseReleased(0)) {
        isDragging = false;
        mouseEnd = Input::GetMousePos();
        if (selectedBall != -1) {
            glm::vec2 impulse = (mouseEnd - mouseStart);
            glm::vec2 newVelocity = impulse / balls[selectedBall].GetMass();
            balls[selectedBall].SetVelocity(newVelocity);
            selectedBall = -1;
        }
    }

    // Physics
    for (int i = 0; i < balls.size(); i++) {
        
        //circle reference and not copy so I work with the real thing
        Circle& ball = balls[i];

        // drag
        ball.circleVel *= (1.0f - damping * deltaTime);

        
        ball.circlePosition += ball.circleVel * deltaTime;

        // Wall collision
        if (ball.circlePosition.x - ball.GetRadius() < boxMin.x &&
            ball.circleVel.x < 0) {
            ball.circleVel.x *= -1;
            ball.circlePosition.x = boxMin.x + ball.GetRadius();
        }
        if (ball.circlePosition.x + ball.GetRadius() > boxMax.x &&
            ball.circleVel.x > 0) {
            ball.circleVel.x *= -1;
            ball.circlePosition.x = boxMax.x - ball.GetRadius();
        }
        if (ball.circlePosition.y - ball.GetRadius() < boxMin.y &&
            ball.circleVel.y < 0) {
            ball.circleVel.y *= -1;
            ball.circlePosition.y = boxMin.y + ball.GetRadius();
        }
        if (ball.circlePosition.y + ball.GetRadius() > boxMax.y &&
            ball.circleVel.y > 0) {
            ball.circleVel.y *= -1;
            ball.circlePosition.y = boxMax.y - ball.GetRadius();
        }
    }

    //Balls
    for (int i = 0; i < balls.size(); i++) {
        for (int j = i + 1; j < balls.size(); j++) {
            Circle& a = balls[i];
            Circle& b = balls[j];

            glm::vec2 delta = b.circlePosition - a.circlePosition;
            float dist = glm::length(delta);
            float combinedRadius = a.GetRadius() + b.GetRadius();

            if (dist < combinedRadius && dist > 0.0f) {
                glm::vec2 normal = glm::normalize(delta);
                float penetration = combinedRadius - dist;

                // Move balls apart 
                a.circlePosition -= normal * (penetration * 0.5f);
                b.circlePosition += normal * (penetration * 0.5f);

                // Reflect velocities
                glm::vec2 relativeVelocity = b.circleVel - a.circleVel;
                float velAlongNormal = glm::dot(relativeVelocity, normal);

                if (velAlongNormal > 0)
                    continue; 

                
                float impulseMagnitude = -2 * velAlongNormal;
                impulseMagnitude /= (1.0f / a.GetMass() + 1.0f / b.GetMass());

                glm::vec2 impulse = impulseMagnitude * normal;
                a.circleVel -= impulse / a.GetMass();
                b.circleVel += impulse / b.GetMass();
            }
        }
    }
}

void Assignment5 ::Draw() {
    // Draw box
    Draw::Line(glm::vec2(boxMin.x, boxMin.y), glm::vec2(boxMax.x, boxMin.y));
    Draw::Line(glm::vec2(boxMax.x, boxMin.y), glm::vec2(boxMax.x, boxMax.y));
    Draw::Line(glm::vec2(boxMax.x, boxMax.y), glm::vec2(boxMin.x, boxMax.y));
    Draw::Line(glm::vec2(boxMin.x, boxMax.y), glm::vec2(boxMin.x, boxMin.y));

    // Draw balls
    for (auto& ball : balls) {
        Draw::SetColor(Colors::cyan);
        Draw::Circle(ball.circlePosition, ball.GetRadius());
    }

    // Draw drag line
    if (isDragging && selectedBall != -1) {
        Draw::SetColor(Colors::yellow);
        Draw::Line(mouseStart, Input::GetMousePos());
    }
}

void Assignment5 ::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::SliderFloat("Damping", &damping, 0.0f, 10.0f);
    ImGui::End();
}
