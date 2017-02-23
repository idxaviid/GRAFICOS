#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Ray.h"
#include "Object.h"
#include <vector> //Notice that vector in C++ is different from Vector2, Vector3 or similar things in a graphic library.
#include <iostream>
#include "light.h"
#define MAX_REFLECT 1
using namespace std;
class Scene
{
public:
    Scene();
    ~Scene();

    bool  CheckIntersection(const Ray &ray, IntersectInfo &info);
    float CastRay(Ray &ray, Payload &payload,int reflect_number);
    bool CheckIntersectionShadow(const Ray &ray, IntersectInfo &info);
    void initScene1(Material m1,Material m2, Material m3, Material m4);
    void initScene2(Material m1,Material m2, Material m3, Material m4);
    void initScene3(Material m1,Material m2, Material m3, Material m4);
    void initScene4(Material m1,Material m2, Material m3, Material m4);
    /*
    ** std::vector d'objectes continguts a l'escena
    */
    std::vector<Object*> objects;

    /*
     * camera de l'escena
     */
    Camera *cam;
    /*
     * TODO: Cal afegir el conjunt de llums de l'escena DONE
     */
    std::vector<Light*> lights;
    glm::vec3 ambientGlobal;

    glm::vec3 object_color(Light l,IntersectInfo &info,Ray &ray,int reflect_number);
};

#endif // SCENE_H
