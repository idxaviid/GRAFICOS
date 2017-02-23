#include "light.h"


Light::Light()
{
    Position = glm::vec3(0.0,5.0,0.0);
    Direction = glm::vec3(0.0,0.0,0.0);
    Ambient = glm::vec3(0.0,0.0,0.0);
    Specular = glm::vec3(0.0,0.0,0.0);
    Diffuse = glm::vec3(0.0,0.0,0.0);
}

Light::Light(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse,Lights type)
{
    Position = position;
    Direction = direction;
    Ambient = ambient;
    Specular = specular;
    Diffuse = diffuse;
    Type = type;
}

glm::vec3 Light::getDiffuse() const
{
    return Diffuse;
}

void Light::setDiffuse(const glm::vec3 &value)
{
    Diffuse = value;
}

glm::vec3 Light::getSpecular() const
{
    return Specular;
}

void Light::setSpecular(const glm::vec3 &value)
{
    Specular = value;
}

glm::vec3 Light::getAmbient() const
{
    return Ambient;
}

void Light::setAmbient(const glm::vec3 &value)
{
    Ambient = value;
}

glm::vec3 Light::getDirection() const
{
    return Direction;
}

void Light::setDirection(const glm::vec3 &value)
{
    Direction = value;
}

glm::vec3 Light::getPosition() const
{
    return Position;
}

void Light::setPosition(const glm::vec3 &value)
{
    Position = value;
}
