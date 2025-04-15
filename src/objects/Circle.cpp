#include "Circle.h"

float Circle :: GetMass()
{
    return circleMass;
}

float Circle ::GetRadius() 
{
    return circleRadius;
}

void Circle::SetMass(float newMass)
{
    circleMass = newMass;
}

Circle::Circle(int radius,int mass,glm::vec2 initialPosition,glm::vec2 initialVelocity) 
{
    circleRadius = radius;
    circleMass = mass;
    SetPos(initialPosition);
    SetVelocity(initialVelocity);
}

Circle::Circle()
{
    Circle(1, 1, glm::vec2(0, 0), glm::vec2(0, 0));
}

void Circle::SetPos(glm::vec2 position)
{
    circlePosition = position;
}



void Circle::SetVelocity(glm::vec2 velocity)
{
    circleVel = velocity;
}



void Circle::AddForceVector(glm::vec2 force) 
{
    totalForceVector += force;
}

glm::vec2 Circle::GetTotalForceVector()
{
    return totalForceVector;
}

void Circle::ResetForceVector()
{
    totalForceVector = glm::vec2(0, 0);
}


