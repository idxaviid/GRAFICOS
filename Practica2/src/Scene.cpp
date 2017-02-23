#include "Scene.h"

Scene::Scene()
{
    // Afegeix la camera a l'escena
    cam = new Camera();
    // TODO: Cal crear els objectes de l'escena (punt 2 de l'enunciat) DONE

    //DEFINIM ELS MATERIALS DE LA ESCENA
    Material red;
    red.ambient= glm::vec3(0.02,0.02,0.02);
    red.diffuse=glm::vec3(0.8,0.0,0.0);
    red.specular= glm::vec3(1.0,1.0,1.0);
    red.shininess = 200;

    Material green;
    green.ambient= glm::vec3(0.02,0.02,0.02);
    green.diffuse=glm::vec3(0.0,0.8,0.0);
    green.specular= glm::vec3(1.0,1.0,1.0);
    green.shininess = 200;

    Material silver;
    silver.ambient= glm::vec3(0.0,0.0,0.0);
    silver.diffuse=glm::vec3(0.55,0.55,0.55);
    silver.specular= glm::vec3(0.1);
    silver.shininess = 200;

    Material blue;
    blue.ambient= glm::vec3(0.02,0.02,0.02);
    blue.diffuse=glm::vec3(0.0,0.0,0.8);
    blue.specular= glm::vec3(1.0,1.0,1.0);
    blue.shininess = 200;

    ambientGlobal = glm::vec3(0.0001,0.0001,0.0001);

    //BANCS DE PROVAS
    // 1 PLANO + 1 ESFERA
    //initScene1(red,green,blue,silver);

    // 2 PLANOS + 2 ESFERAS
    //initScene2(red,green,blue,silver);

    //3 PLANOS + 3 ESFERAS
    initScene3(red,green,blue,silver);

    //1PLANO + 6 ESFERAS
    //initScene4(red,green,blue,silver);


}
//DESTRUCTOR DE LA ESCENA, ELIMINEM TOTS ELS OBJECTES I LLUMS
Scene::~Scene()
{
    delete cam;
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            delete objects[i];
        }
    }
    for(unsigned int i = 0; i < lights.size(); ++i){
        if(lights[i]){
            delete lights[i];
        }
    }
}


/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena DONE
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/

bool Scene::CheckIntersection(const Ray &ray, IntersectInfo &info) {

    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar Intersect per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el PayLoad del raig,
    // pero no en aquesta funcio. Per això es posa const en el paràmetre ray, per a
    // que no es canvïi aqui. DONE
    bool intersect = false;
    Object* objecte;
    IntersectInfo* minim = new IntersectInfo();
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            objecte = objects[i];
            if(objecte->Intersect(ray,info)){
                info.indexObjecte = i;

                if( i == 0)
                    minim->operator = (info);

                if (minim->time > info.time)
                    minim->operator = (info);

                intersect = true;
                //cout << "El objecte: " << i << " Interseca en t = " << info.time<< endl;
            }
        }
    }
    if (intersect == true){
        info.operator= (*minim);
        return true;
    }
    return false;
}



//Closest_intersection = CheckIntersection
//Shade = blin_phong
/*
** TODO: Funcio recursiva del RayTracing.
** A modificar en el punt 4 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en el punt 5 per a tractar reflexions
**
** Aquest metode es crida per a cada pixel, i cada cop que es calculen ombres o reflexions
** El paràmetre PayLoad es pot usar per a guardar informacio de sobre el quin es color actual del raig i el nombre de
** rebots que s'han fet.
** Aquest metode retorna el delta del raig (o t) en elobjecte = objects[i];
               if(objecte->Intersect(newRay,newInfo))
                   return info.material->ambient; cas que hi hagi interseccio o
** -1 si no hi ha interseccio amb cap objecte.
*/
//	La funcio CastRay ha de calcular la il·luminacio,
//  les ombres i les reflexions.

float Scene::CastRay(Ray &ray, Payload &payload,int reflect_number) {

    IntersectInfo info;

    if (CheckIntersection(ray,info)) {
        /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
         * el material de l'objecte i les llums per l'apartat 4 de la practica
         * I per l'apartat 5, cal fer que tambe es tinguin en compte els rebots de les reflexions.

           Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
           payload ha d'anar tenint el color actualitzat segons els rebots.
        */

        if(reflect_number >= MAX_REFLECT){
            payload.color = info.material->ambient; //quan estem amb el numero maxim de reflexions podem usar ambien o ambient global
            return info.time;
        }

        glm::vec3 color = glm::vec3(0.0,0.0,0.0);
        glm::vec3 global = info.material->ambient * ambientGlobal;
        //glm::vec3 global = glm::vec3(0.2126, 0.7152, 0.0722);
        //PARA CADA LUZ HACEMOS EL CALCULO DE SOMBRAS BLINNPHONG Y REFLEXIONS
        for(unsigned int i = 0; i < lights.size(); ++i){
            if(lights[i]){
                Light *l = lights[i];

                color = color + object_color(*l,info,ray,reflect_number);

            }
        }

        payload.color = global + color;

        return info.time;
    }
    else{
        payload.color = ambientGlobal;
        // Si el ray des de la camera no intersecta amb cap objecte
        // no s'ha de veure res, encara que també es podria posar el color de la Intensita ambien global
        //cout << "No interseca amb re" << endl;
        return -0.0f;
    }
}
//Comprueba si hay algun objeto entre nuestro punto de itnersecion y la luz
bool Scene::CheckIntersectionShadow(const Ray &ray, IntersectInfo &info){
    Object* objecte;
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
                objecte = objects[i];
                if(objecte->Intersect(ray,info))
                    return true;
        }
    }
}

glm::vec3 Scene::object_color(Light l,IntersectInfo &info,Ray &ray,int reflect_number){


    //si he llegado al numero maximo de refleciones retorno el color ambiente


    glm::vec3 diffuse, ambient, specular, N, V, L, H;

    float E = 0.01f;//EPSILON para evitar selfShadowing i selfReflections

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    L = glm::vec3(l.getPosition() - info.hitPoint);
    L = glm::normalize(L);  //normalizamos la L ya que hacemos el calculo de coordenadas normalizadas en el rayo sino se tendira que hacer sin normalizarlo
    //CALCULO SOMBRA

    IntersectInfo shadowInfo;
    Ray shadowRay(info.hitPoint + ( E * L ), L);

    Object* objecte;

    if(CheckIntersectionShadow(shadowRay,shadowInfo))
        return l.getAmbient() * info.material->ambient; //aqui podemos retornar tambien info.ambient o ambientglobal y multiplicar o no per ambient de la luz

    //CALCULO BLINN PHONG
    L = glm::normalize(L);

    // la normal del vertice, normalizada
    N = glm::normalize(info.normal);

    // el vector desde el punt fins al viewer
    V = glm::normalize(info.hitPoint);

    // the halfway, o l'optimitzacio de Blinn
    H = (L+V) / glm::length(L+V);

    // la difusa es el producto de la difusa de la luz por la difusa del material
    diffuse = (l.getDiffuse() * info.material->diffuse) * glm::max(glm::dot(L, N), 0.0f);

    // la especular es el producto del producto especular de la luz por el del material y  el dot de N y H elevado a E
    specular = (l.getSpecular() * info.material->specular) * glm::max(glm::pow(glm::dot(N, H), info.material->shininess) , 0.0f);

    // producto de light ambient y  ambient del material
    ambient = l.getAmbient() * info.material->ambient;

    //CALCULO COLOR REFLECTIDO

    //glm::vec3 reflectedRayDirection = ray.direction - ( 2 * ( glm::dot(info.normal,ray.direction) ) * info.normal );
    glm::vec3 reflectedRayDirection = -2 * glm::dot(info.normal,ray.direction)  * info.normal  + ray.direction ;
    Ray reflectedRay(info.hitPoint + (E * L),reflectedRayDirection);

    Payload payload;
    payload.color = glm::vec3(0.0,0.0,0.0);

    //FUNCION RECURSIVA PARA CALCULAR LAS REFLEXIONES
    if(CastRay(reflectedRay,payload,reflect_number + 1) > 0.0f)
        payload.color = payload.color * info.material->specular; //multiplicamos el color resultado por la ks de material como lo dice en teoria


    return (ambient + diffuse + specular +  payload.color);

}


void Scene::initScene1(Material red,Material green,Material blue,Material silver){


    Sphere *s = new Sphere(glm::vec3(0.0,0.0,0.0),1.0);
    s->material = red;
    objects.push_back(s);

    Plane *p = new Plane();
    p->Normal = glm::vec3(0.0,1.0,0.0);
    p->Start = glm::vec3(-10.0,-2.0,-10.0);
    p->material = silver;
    objects.push_back(p);

    Light *l1 = new Light();
    l1->setPosition(glm::vec3(-10.0,10.0,10.0));
    l1->setAmbient(glm::vec3(0.2));
    l1->setDiffuse(glm::vec3(0.8));
    l1->setSpecular(glm::vec3(1.0));
    lights.push_back(l1);


}


void Scene::initScene2(Material red,Material green,Material blue,Material silver){




    Sphere *s = new Sphere(glm::vec3(0.0,0.0,0.0),1.0);
    s->material = red;
    objects.push_back(s);

    Sphere *s1 = new Sphere(glm::vec3(-4.0,0.0,0.0),1.0);
    s1->material = blue;
    objects.push_back(s1);


    Plane *p = new Plane();
    p->Normal = glm::vec3(0.0,1.0,0.0);
    p->Start = glm::vec3(-10.0,-4.0,-10.0);
    p->material = silver;
    objects.push_back(p);

    Plane *p1 = new Plane();
    p1->Normal = glm::vec3(0.0,0.0,1.0);
    p1->Start = glm::vec3(-10.0,-10.0,-4.0);
    p1->material = silver;
    objects.push_back(p1);

    Light *l1 = new Light();
    l1->setPosition(glm::vec3(-10.0,20.0,10.0));
    l1->setAmbient(glm::vec3(0.2));
    l1->setDiffuse(glm::vec3(0.8));
    l1->setSpecular(glm::vec3(1.0));
    lights.push_back(l1);


}

void Scene::initScene3(Material red,Material green,Material blue,Material silver){




    Sphere *s = new Sphere(glm::vec3(-4.0,0.0,0.0),1.0);
    s->material = red;
    objects.push_back(s);

    Sphere *s1 = new Sphere(glm::vec3(0.0,0.0,4.0),1.0);
    s1->material = green;
    objects.push_back(s1);

    Sphere *s2 = new Sphere(glm::vec3(0.0,0.0,0.0),1.0);
    s2->material = blue;
    objects.push_back(s2);



    Plane *p = new Plane();
    p->Normal = glm::vec3(0.0,1.0,0.0);
    p->Start = glm::vec3(-10.0,-4.0,-10.0);
    p->material = silver;
    objects.push_back(p);

    Plane *p1 = new Plane();
    p1->Normal = glm::vec3(0.0,0.0,1.0);
    p1->Start = glm::vec3(-10.0,-10.0,-4.0);
    p1->material = silver;
    objects.push_back(p1);

    Plane *p2 = new Plane();
    p2->Normal = glm::vec3(-1.0,0.0,0.0);
    p2->Start = glm::vec3(4.0,-10.0,-10.0);
    p2->material = silver;
    objects.push_back(p2);


    Light *l1 = new Light();
    l1->setPosition(glm::vec3(-10.0,20.0,10.0));
    l1->setAmbient(glm::vec3(0.2126, 0.7152, 0.0722));
    l1->setDiffuse(glm::vec3(0.2126, 0.7152, 0.0722));
    l1->setSpecular(glm::vec3(0.2126, 0.7152, 0.0722));
    lights.push_back(l1);



}
void Scene::initScene4(Material red,Material green,Material blue,Material silver){


    Sphere *s = new Sphere(glm::vec3(-4.0,0.0,0.0),1.5);
    s->material = red;
    objects.push_back(s);

    Sphere *s1 = new Sphere(glm::vec3(0.0,0.0,0.0),1.5);
    s1->material = green;
    objects.push_back(s1);

    Sphere *s2 = new Sphere(glm::vec3(4.0,0.0,0.0),1.5);
    s2->material = blue;
    objects.push_back(s2);

    Sphere *s3 = new Sphere(glm::vec3(-2.0,3.0,0.0), 0.75);
    s3->material = blue;
    objects.push_back(s3);

    Sphere *s4 = new Sphere(glm::vec3(2.0,3.0,0.0),0.75);
    s4->material = red;
    objects.push_back(s4);

    Sphere *s5 = new Sphere(glm::vec3(0.0,4.5,0.0),0.5);
    s5->material = green;
    objects.push_back(s5);

    Plane *p = new Plane();
    p->Normal = glm::vec3(0.0,1.0,0.0);
    p->Start = glm::vec3(-10.0,-4.0,-10.0);
    p->material = silver;
    objects.push_back(p);


    Light *l1 = new Light();
    l1->setPosition(glm::vec3(-10.0,20.0,10.0));
    l1->setAmbient(glm::vec3(0.2));
    l1->setDiffuse(glm::vec3(0.8));
    l1->setSpecular(glm::vec3(1.0));
    lights.push_back(l1);

}
