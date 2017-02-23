#include "Object.h"

Material::Material():
    ambient(1.0f),
    diffuse(1.0f),
    specular(1.0f),
    shininess(10.0f)

{}

Object::Object(const glm::mat4 &transform, const Material &material):
    transform(transform),
    material(material)
{}
Sphere::Sphere(glm::vec3 center,float radius){
    Center = center;
    Radius =  radius;
}

/* TODO: Implementar en el punt 2 */
bool Sphere::Intersect(const Ray &ray, IntersectInfo &info) const
{
    /*
    * Hemos hecho la parte de aislar variables usando formula de teoria pero en la wiki es aun mas facil
    * usamos esta formula la parte de abajo
    * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
    * https://en.wikipedia.org/wiki/Ray_tracing_%28graphics%29
    */

    glm::vec3 v = (ray.origin - this->Center);

    float solution = glm::pow( glm::dot (ray.direction , v) , 2.0f) - (glm::length( v ) * glm::length( v ))  + glm::pow(this->Radius,2.0f);

    /*
     * Tenemos 3 casos
     * 1:El rayo no toca la esfera
     * 2:El rayo toca la esfera solo en un punto: es perpendicular a la esfera
     * 3:El rayo toca la esfera en dos puntos,guardamos la posicion del mas cercano
     */

    if(solution < 0.0f){
        return false;

    }else if(solution == 0.0f){

        float delta = - glm::dot(ray.direction,v);

        if(delta < 0.0) //solo comprobamos si es menor que 0 porque normalizamos direcion del rayo sino se tendria que hacer con if(delta < 0.0 || delta >1.0)
            return false;

        info.time = delta;
        info.hitPoint = ray.origin + (delta * ray.direction);
        info.normal = glm::normalize(info.hitPoint - this->Center);
        info.material = &this->material;

        return true;

    }else{

        solution = glm::sqrt(solution);

        float delta = - glm::dot(ray.direction,v);

        float t1 = glm::length(delta - solution);
        float t2 = glm::length(delta + solution);

        if( t1 < t2 )
            delta = delta - solution;
        else
            delta = delta + solution;
        if(delta < 0.0)
            return false;
        info.time = delta;
        info.hitPoint = ray.origin + (delta * ray.direction);
        info.normal = glm::normalize(info.hitPoint - this->Center);
        info.material = &this->material;
        return true;
    }
    return false;

}

// Function glm::dot(x,y) will return the dot product of parameters. (It's the inner product of vectors)

/* TODO: Implementar en el punt 2 DONE */
bool Plane::Intersect(const Ray &ray, IntersectInfo &info) const
{
    /*
     * Tenemos 3 casos
     * 1. No intersecta return false
     * 2. Es paralelo   return false
     * 3. Interseca en 1 punto return true
     *
     */

    float denom = glm::dot(ray.direction,this->Normal);

    if (fabs(denom) == 0.0f)
        return false;
    //solo comprobamos si es menor que 0 porque normalizamos direcion del rayo sino se tendria que hacer con if( < 0.0 || >1.0)
    if(fabs(denom) > 1e-4f)
    {
        float delta = glm::dot((this->Start - ray.origin),this->Normal) / denom;

        if (delta >= 0.0f){
            info.time = delta;
            info.hitPoint = ray.origin + (delta * ray.direction);
            info.normal = this->Normal;
            info.material = &this->material;
            return true;
        }

    }
    return false;

}

/* TODO: Implementar com a extensio */
bool Triangle::Intersect(const Ray &ray, IntersectInfo &info) const { return -1.0f; }
