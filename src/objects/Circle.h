#pragma once
#include <glm/glm.hpp>

class Circle
{
    private:
    float circleMass = 2;
    
    float circleRadius = 1;
    glm::vec2 totalForceVector;

	public:
    glm::vec2 circlePosition;
    glm::vec2 circleVel;
    Circle(int radius,int mass,glm::vec2 initialPosition,glm::vec2 initialVelocity);
    void SetPos(glm::vec2 position);
    void SetMass(float newMass);
    
    void SetVelocity(glm::vec2 velocity);
    
    void AddForceVector(glm::vec2 force);
    glm::vec2 GetTotalForceVector();
    void ResetForceVector();
    float GetRadius();
    
    float GetMass();

};