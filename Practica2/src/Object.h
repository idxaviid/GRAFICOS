#pragma once

#include "Ray.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "math.h"
class Material {
  public:
    Material();
    glm::vec3 ambient;
    glm::vec3 diffuse;   
    glm::vec3 specular;	
    float shininess;

};

// Es la classe pare de tots els objectes que s'han de visualitzar.
class Object {
  public:
    Object(const glm::mat4 &transform = glm::mat4(1.0f), const Material &material = Material());

    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const { return true; }
    glm::vec3 Position() const { return glm::vec3(transform[3][0], transform[3][1], transform[3][2]); }
    const Material *MaterialPtr() const { return &material; }
    Material material;
  protected:
    glm::mat4 transform;  // Matriu de transformacio de coordenades locals a globals

};

// TODO: Cal definir els diferents tipus d'objectes de l'escena com a fills d'Object.
// Cal definir-lis els atributs propis i implementar la funció
// tots els objectes de l'escena, cal definir el metode Intersect()

/* TODO: Implementar en el punt 2 de l'enunciat*/
class Sphere : public Object {

  public:
    //el Centro de la esfera es Position definida en el objecte
    Sphere(glm::vec3 center,float radius);
    glm::vec3 Center;
    float Radius;
    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;  //  To figure out if the Ray hit this object.
};

/* TODO: Implementar en el punt 2 de l'enunciat*/
class Plane : public Object {
  public:
    //glm::vec3 p1,p2,p3; //para hacer plano con 3 puntos
    glm::vec3 Start;
    glm::vec3 Normal;
    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;
};

/* TODO: Implementar com a extensio*/
class Triangle : public Object {
  public:
    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;
};
