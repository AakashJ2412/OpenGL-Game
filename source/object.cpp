#include "object.h"
#include "main.h"
#define PI 3.1416

// define player object
Player::Player(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.8f, 0.0f,
        0.5f, -0.8f, 0.0f,
        0.5f, -0.8f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        -0.8f, 0.4f, 0.0f,
        -0.8f, -0.4f, 0.0f,
        -0.5f, -0.4f, 0.0f,
        -0.5f, -0.4f, 0.0f,
        -0.8f, 0.4f, 0.0f,
        -0.5f, 0.4f, 0.0f,

        -0.5f, -0.8f, 0.0f,
        -0.5f, -1.3f, 0.0f,
        -0.2f, -1.3f, 0.0f,
        -0.2f, -1.3f, 0.0f,
        -0.5f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,

        0.5f, -0.8f, 0.0f,
        0.5f, -1.3f, 0.0f,
        0.2f, -1.3f, 0.0f,
        0.2f, -1.3f, 0.0f,
        0.5f, -0.8f, 0.0f,
        0.2f, -0.8f, 0.0f,
        
        0.0f,0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f*sin(PI/10 -PI/2),0.5f+cos(PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(PI/10 -PI/2),0.5f+cos(PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(2*PI/10-PI/2),0.5f+cos(2*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(2*PI/10 -PI/2),0.5f+cos(2*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(3*PI/10 -PI/2),0.5f+cos(3*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(3*PI/10-PI/2),0.5f+cos(3*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(4*PI/10-PI/2),0.5f+cos(4*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(4*PI/10-PI/2),0.5f+cos(4*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(5*PI/10-PI/2),0.5f+cos(5*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(5*PI/10-PI/2),0.5f+cos(5*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(6*PI/10-PI/2),0.5f+cos(6*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(6*PI/10-PI/2),0.5f+cos(6*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(7*PI/10-PI/2),0.5f+cos(7*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(7*PI/10-PI/2),0.5f+cos(7*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(8*PI/10-PI/2),0.5f+cos(8*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(8*PI/10-PI/2),0.5f+cos(8*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(9*PI/10-PI/2),0.5f+cos(9*PI/10-PI/2)*0.5f,0.0f,

        0.0f,0.5f,0.0f,
        0.5f*sin(9*PI/10-PI/2),0.5f+cos(9*PI/10-PI/2)*0.5f,0.0f,
        0.5f*sin(10*PI/1-PI/2),0.5f+cos(10*PI/10-PI/2)*0.5f,0.0f,

        0.6f, 0.7f, 0.0f,
        0.6f, 0.3f, 0.0f,
        -0.2f, 0.3f, 0.0f,
        -0.2f, 0.3f, 0.0f,
        0.6f, 0.7f, 0.0f,
        -0.2f, 0.7f, 0.0f,

    };
    static const GLfloat colour_buffer_data[] = {
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
    
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,

        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,

        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,

        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,
        0.0f,255.0f,255.0f,

        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        
    };
    this->object = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Player::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}


// define imposter object. flag stores whether imposter is active or not
Imposter::Imposter(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = { // top - 1.0f, bottom - 1.3f, left - 0.8f, right - 0.5f
        -0.5f,0.85f,0.0f,
        -0.3f, 0.3f, 0.0f,
        1.0f,1.2f,0.0f,
        
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.8f, 0.0f,
        0.5f, -0.8f, 0.0f,
        0.5f, -0.8f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        -0.8f, 0.4f, 0.0f,
        -0.8f, -0.4f, 0.0f,
        -0.5f, -0.4f, 0.0f,
        -0.5f, -0.4f, 0.0f,
        -0.8f, 0.4f, 0.0f,
        -0.5f, 0.4f, 0.0f,

        -0.5f, -0.8f, 0.0f,
        -0.5f, -1.3f, 0.0f,
        -0.2f, -1.3f, 0.0f,
        -0.2f, -1.3f, 0.0f,
        -0.5f, -0.8f, 0.0f,
        -0.2f, -0.8f, 0.0f,

        0.5f, -0.8f, 0.0f,
        0.5f, -1.3f, 0.0f,
        0.2f, -1.3f, 0.0f,
        0.2f, -1.3f, 0.0f,
        0.5f, -0.8f, 0.0f,
        0.2f, -0.8f, 0.0f,
        
        0.0f,0.7f,0.0f,
        -0.5f,0.7f,0.0f,
        0.7f*sin(PI/10 -3*PI/4),0.7f+cos(PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(PI/10 -3*PI/4),0.7f+cos(PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(2*PI/10-3*PI/4),0.7f+cos(2*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(2*PI/10 -3*PI/4),0.7f+cos(2*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(3*PI/10 -3*PI/4),0.7f+cos(3*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(3*PI/10-3*PI/4),0.7f+cos(3*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(4*PI/10-3*PI/4),0.7f+cos(4*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(4*PI/10-3*PI/4),0.7f+cos(4*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(5*PI/10-3*PI/4),0.7f+cos(5*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(5*PI/10-3*PI/4),0.7f+cos(5*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(6*PI/10-3*PI/4),0.7f+cos(6*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(6*PI/10-3*PI/4),0.7f+cos(6*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(7*PI/10-3*PI/4),0.7f+cos(7*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(7*PI/10-3*PI/4),0.7f+cos(7*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(8*PI/10-3*PI/4),0.7f+cos(8*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(8*PI/10-3*PI/4),0.7f+cos(8*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(9*PI/10-3*PI/4),0.7f+cos(9*PI/10-3*PI/4)*0.7f,0.0f,

        0.0f,0.7f,0.0f,
        0.7f*sin(9*PI/10-3*PI/4),0.7f+cos(9*PI/10-3*PI/4)*0.7f,0.0f,
        0.7f*sin(10*PI/1-3*PI/4),0.7f+cos(10*PI/10-3*PI/4)*0.7f,0.0f,

        -0.5f, 1.1f, 0.0f,
        -0.3f, 0.7f, 0.0f,
        0.3f, 1.4f, 0.0f,
        -0.5f, 1.1f, 0.0f,
        0.3f, 1.4f, 0.0f,
        0.1f, 1.7f, 0.0f,

    };
    static const GLfloat colour_buffer_data[] = {
        255.0f,0.0f,0.0f,
        255.0f,0.0f,0.0f,
        255.0f,0.0f,0.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,
        255.0f,0.0f,255.0f,

        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        0.720f, 0.730f, 0.740f,
        
    };
    this->object = create3DObject(GL_TRIANGLES, 63, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Imposter::draw(glm::mat4 VP)
{
    if(this->flag == 0)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }
}

void Imposter::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}


// imposter task. Flag stores whether is has been picked up or not
Pow_imp::Pow_imp(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.8f, 0.0f,
        0.0f, -0.8f, 0.0f,
        -0.6f, 0.0f, 0.0f,
        0.0f, 0.8f, 0.0f,
        0.0f, -0.8f, 0.0f,
        0.6f, 0.0f, 0.0f,
    };
    static const GLfloat colour_buffer_data[] = {
        0.120f, 0.730f, 0.740f,
        0.720f, 0.130f, 0.740f,
        0.720f, 0.730f, 0.140f,
        0.120f, 0.730f, 0.740f,
        0.720f, 0.130f, 0.740f,
        0.720f, 0.730f, 0.140f,        
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Pow_imp::draw(glm::mat4 VP)
{
    if(this->flag == 0)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }
}

void Pow_imp::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

// object that stores the exitpoint for the game
Exitgame::Exitgame(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.0f,
        -0.6f, 1.5f, 0.0f,
        0.6f, 1.5f, 0.0f,

        0.0f,0.0f,0.0f,
        0.6f, 1.5f, 0.0f,
        1.5f, 0.6f, 0.0f,

        0.0f,0.0f,0.0f,
        1.5f, 0.6f, 0.0f,
        1.5f, -0.6f, 0.0f,

        0.0f,0.0f,0.0f,
        1.5f, -0.6f, 0.0f,
        0.6f, -1.5f, 0.0f,
    
        0.0f,0.0f,0.0f,
        0.6f, -1.5f, 0.0f,
        -0.6f, -1.5f, 0.0f,

        0.0f,0.0f,0.0f,
        -0.6f, -1.5f, 0.0f,
        -1.5f, -0.6f, 0.0f,

        0.0f,0.0f,0.0f,
        -1.5f, -0.6f, 0.0f,
        -1.5f, 0.6f, 0.0f,

        0.0f,0.0f,0.0f,
        -1.5f, 0.6f, 0.0f,
        -0.6f, 1.5f, 0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void Exitgame::draw(glm::mat4 VP)
{
    if(this->flag == 0)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }
}

void Exitgame::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}


// task that enables powerups and obstacles in the field
Pow_obspow::Pow_obspow(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 0;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = { 
        0.8f, 0.0f, 0.0f,
        -0.4f, -0.7f, 0.0f,
        -0.4f, 0.7f, 0.0f,
        -0.8f, 0.0f, 0.0f,
        0.4f, -0.7f, 0.0f,
        0.4f, 0.7f, 0.0f,
    };
    static const GLfloat colour_buffer_data[] = {
        0.100f, 0.420f, 0.330f,
        0.520f, 0.030f, 0.240f,
        0.220f, 0.630f, 0.640f,
        0.120f, 0.130f, 0.440f,
        0.720f, 0.430f, 0.540f,
        0.520f, 0.430f, 0.140f,        
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Pow_obspow::draw(glm::mat4 VP)
{
    if(this->flag == 0)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }
}

void Pow_obspow::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}


// object storing an individual item for pickup
Pickups::Pickups(float x, float y, int type, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->flag = 1;
    this->type = type;
    speed = 1;
    static const GLfloat vertex_buffer_data[] = {
        0.6f, 0.6f, 0.0f,
        0.6f,-0.6f,0.0f,
        -0.6f,0.6f,0.0f,
        0.6f,-0.6f,0.0f,
        -0.6f,0.6f,0.0f,
        -0.6f,-0.6f,0.0f

    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Pickups::draw(glm::mat4 VP)
{
    if(this->flag == 0)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }
}

void Pickups::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

