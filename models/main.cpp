#include <SFML/Graphics.hpp>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

    glewInit();

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glm::vec4 pointLightPositions[] = {
        glm::vec4( 0.7f,  0.2f,  2.0f, 1.0f),
        glm::vec4( 2.3f, -3.3f, -4.0f, 1.0f),
        glm::vec4(-4.0f,  2.0f, -12.0f, 1.0f),
        glm::vec4( 0.0f,  0.0f, -3.0f, 1.0f)
    };  

    // Setting up light VAO
    GLuint lampVAO, lampVBO;
    glGenVertexArrays(1, &lampVAO);
    glGenBuffers(1, &lampVBO);

    glBindVertexArray(lampVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glPolygonMode(GL_FRONT, GL_TRIANGLES);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //тест глубины для нормального отображения полигонов
    glEnable(GL_DEPTH_TEST);

    bool keys[sf::Keyboard::KeyCount] = {false};

    

    Camera cam(&window);
    cam.setKeys(keys);

    Shader shader(&cam, "../combined_light.vert", "../combined_light.frag");
    Shader lampShader(&cam, "../lamp.vert", "../lamp.frag");

    /*glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window.display();*/

    //Model back("../suit/scene.fbx");
    Model back("../backpack/backpack.obj");

    sf::Clock clock;
    sf::Clock fpsClock;
    int fps = 0;

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                keys[event.key.code] = true;
                if(event.key.code == sf::Keyboard::F)
                    cam.changeCursorCapchure();
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                keys[event.key.code] = false;
            }
        }

        if(clock.getElapsedTime().asMilliseconds() < 20)
            continue;

        clock.restart();
        
        cam.update();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

        shader.Use();

        shader.uniform("material.shininess", 64.0f);
        shader.uniform("dirLight.direction", cam.View()*glm::vec4(-0.1f, -0.4f, -1.4f, 0.0f));  
        shader.uniform("dirLight.ambient", ambientColor);
        shader.uniform("dirLight.diffuse", diffuseColor);
        shader.uniform("dirLight.specular", glm::vec3(1.0f));

         for (int i = 0; i < 4; i++)
        {
            std::string s("pointLights[");
            s += std::to_string(i) + "]";
            shader.uniform((s+".ambient").c_str(), ambientColor);
            shader.uniform((s+".diffuse").c_str(), diffuseColor); // darken the light a bit to fit the scene
            shader.uniform((s+".specular").c_str(), glm::vec3(1.0f));
            shader.uniform((s+".constant").c_str(), 1.0f);
            shader.uniform((s+".linear").c_str(), 0.09f);
            shader.uniform((s+".quadratic").c_str(), 0.032f); 
            shader.uniform((s+".position").c_str(), cam.View()*pointLightPositions[i]);
        }

        /*glm::vec3 camPos = cam.View()*glm::vec4(cam.Position(), 1.0f);
        glm::vec3 camDir = glm::normalize(cam.View()*glm::vec4(cam.Direction(), 0.0f));
        shader.uniform("projectedLight.position", camPos);
        shader.uniform("projectedLight.direction", camDir);
        shader.uniform("projectedLight.ambient", ambientColor);
        shader.uniform("projectedLight.diffuse", diffuseColor);
        shader.uniform("projectedLight.specular",glm::vec3(1.0f));
        shader.uniform("projectedLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader.uniform("projectedLight.cutOffOut", glm::cos(glm::radians(17.5f)));
        shader.uniform("projectedLight.constant", 1.0f);
        shader.uniform("projectedLight.linear", 0.09f);
        shader.uniform("projectedLight.quadratic", 0.032f);*/
        
        shader.uniform("viewPos", cam.Position());   

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.uniform("model", model);

        back.Draw(shader);

        // Rendering lamp
        lampShader.Use();
        glBindVertexArray(lampVAO);  

        for(int i = 0; i < 4; i++)
        {
            glm::mat4 model(1.0f);
            glm::vec3 vec(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            model = glm::translate(model, vec);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.uniform("model", model);        
            glDrawArrays(GL_TRIANGLES, 0, 36);        
        }
        glBindVertexArray(0);
        


        //swap buffers
        window.display();
    }

    glDeleteVertexArrays(1, &lampVAO);
    glDeleteBuffers(1, &lampVBO);

    return 0;
}