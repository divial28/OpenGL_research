#include "Camera.h"

Camera::Camera()
    : view(1.0f)
    , position(0.0f, 0.0f, 3.0f)
    , front(0.0f, 0.0f, -1.0f)
    , up(0.0f, 1.0f, 0.0f)
    , rotation(0.0f)
    , pitch(0.0f)
    , yaw(-90.0f)
    , sensitivity(0.03f)
    , speed(0.05f)
    , mode(FPS)
{

}

void Camera::handle(bool* keys)
{
    if(keys[sf::Keyboard::W])
        moveForward();
    if(keys[sf::Keyboard::S])
        moveBackward();
    if(keys[sf::Keyboard::A])
        moveLeft();
    if(keys[sf::Keyboard::D])
        moveRight();

    update();
}

void Camera::rotate(const sf::Vector2i& dir)
{
    yaw += dir.x * sensitivity;
    pitch -= dir.y * sensitivity;

    /*
    if(pitch > 89.0f)
    pitch =  89.0f;
    if(pitch < -89.0f)
    pitch = -89.0f;
    */

    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw)); 
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    direction = front;
    if(mode == FPS)
        direction.y = 0;

    front = glm::normalize(front);
    direction = glm::normalize(direction);
}

void Camera::moveForward()
{
    position += direction * speed;
}

void Camera::moveBackward()
{
    position -= direction * speed;
}

void Camera::moveLeft()
{
    position -= glm::normalize(glm::cross(direction, up)) * speed;
}

void Camera::moveRight()
{
    position += glm::normalize(glm::cross(direction, up)) * speed;
}

void Camera::update()
{
    //glm::lookAt()
    view = glm::lookAt(position, position + front, up);
}

const glm::mat4& Camera::View()
{
    return view;
}

void Camera::setMode(Mode new_mode)
{
    mode = new_mode;
}