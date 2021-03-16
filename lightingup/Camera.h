#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>

class Camera
{
public:

    enum Mode 
    {
        FLY = 0,
        FPS
    };

    Camera(const glm::vec3 position, Mode mode);

    void handle(bool* keys);

    void rotate(const sf::Vector2i& dir);

    void moveForward();

    void moveBackward();

    void moveLeft();

    void moveRight();

    void update();

    const glm::mat4& View();

    void setMode(Mode new_mode);

private:
    glm::mat4   view;

    glm::vec3   position;
    glm::vec3   front;
    glm::vec3   up;
    glm::vec3   direction;

    GLfloat     speed;

    GLfloat     yaw;
    GLfloat     pitch;
    GLfloat     rotation;
    GLfloat     sensitivity;

    Mode        mode;
};

#endif