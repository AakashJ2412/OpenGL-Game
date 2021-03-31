#include "main.h"

#ifndef OBJECT_H
#define OBJECT_H

class Player
{
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

class Imposter
{
public:
    Imposter() {}
    Imposter(float x, float y, color_t color);
    glm::vec3 position;
    int flag;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

class Pow_imp
{
public:
    Pow_imp() {}
    Pow_imp(float x, float y, color_t color);
    glm::vec3 position;
    int flag;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

class Pow_obspow
{
public:
    Pow_obspow() {}
    Pow_obspow(float x, float y, color_t color);
    glm::vec3 position;
    int flag;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

class Pickups
{
public:
    Pickups() {}
    Pickups(float x, float y, int type, color_t color);
    glm::vec3 position;
    int flag;
    int type;       // 0 for powerup, 1 for obstacle
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

class Exitgame
{
public:
    Exitgame() {}
    Exitgame(float x, float y, color_t color);
    glm::vec3 position;
    int flag;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};


#endif
