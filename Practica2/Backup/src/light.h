#ifndef LIGHT_H
#define LIGHT_H
#include "glm/glm.hpp"
enum Lights {Puntual, Direccional, SpotLight};

class Light
{
protected:

    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Ambient;
    glm::vec3 Specular;
    glm::vec3 Diffuse;
    Lights Type;

public:
    Light();
    Light(glm::vec3 position,glm::vec3 direction,glm::vec3 ambient,glm::vec3 specular,glm::vec3 diffuse,Lights type);
    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 &value);
    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3 &value);
    glm::vec3 getAmbient() const;
    void setAmbient(const glm::vec3 &value);
    glm::vec3 getSpecular() const;
    void setSpecular(const glm::vec3 &value);
    glm::vec3 getDiffuse() const;
    void setDiffuse(const glm::vec3 &value);
};

#endif // LIGHT_H
