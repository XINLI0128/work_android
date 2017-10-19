//
// Created by xinli on 17-10-11.
//

#ifndef MYAPPLICATION_PARTICE_H
#define MYAPPLICATION_PARTICE_H


#include <GLES2/gl2.h>

#define PARTICLE_NUM 1000

class Partice
{
public:

    float mass;
    float lifetime;

    glm::vec3 velocity;
    glm::vec3 color;
    glm::vec3 force;
    glm::vec3 position;

};

class ParticeEnginee
{
public:

    Partice *p;
    void createPartice();
    void deletePartice();

}
#endif //MYAPPLICATION_PARTICE_H
