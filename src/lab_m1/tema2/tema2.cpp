#include "tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/tema2/transform3D.h"
#include "lab_m1/tema2/labirint.h"
#include "lab_m1/tema2/wall.h"
#include "lab_m1/tema2/camera_class.h"
#include "lab_m1/tema2/collisions.h"
#include "lab_m1/tema2/projectile.h"
#include "lab_m1/tema2/enemy.h"
#include "lab_m1/tema2/tile.h"
#include "lab_m1/tema2/hud.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    labirint = new Labirint();
    avatar = new Avatar();
    camera = new implemented::Camera();
    camera_Hud = new implemented::Camera();
    hud = new Hud();
    hud->readGameFile();
    hud->writeGameFile();
    hud->setBGMatrix();

 
    camera->Set(hud->getCStartingPos(), hud->getPStartingPos(), glm::vec3(0, 1, 0));
    camera_Hud->Set(hud->getCStartingPos() - glm::vec3(0, 1, 0), hud->getPStartingPos(), glm::vec3(0, 1, 0));
    polygonMode = GL_FILL;

    projectMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);


    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    Mesh* proj = new Mesh("sphere");
    proj->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[proj->GetMeshID()] = proj;


    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (hud->maze[i][j] == 1) {
                Wall obstacle;
                obstacle.setPos(2 *i, 1.0f, 2 * j);
                obstacle.setModelMatrix();
                obstacles.push_back(obstacle);
            }
            else if (hud->maze[i][j] == 2) {
                Enemy enemy;
                enemy.setInitialPos(2 * i - 20.f, 0.8f, 2 * j - 20.f);
                enemy.setModelMatrix();
                enemies.push_back(enemy);
            }
            else {
                Tile tile;
                tile.setMatrix(2 * i - 20.f, -0.05f, 2 * j - 20.f);
                floor.push_back(tile);
            }
        }
    }
    


    avatar->setStartingPos(camera->GetTargetPosition());

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("DefShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShaderDef.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShaderDef.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("WallShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShaderWall.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShaderWall.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    hud->setTimer(deltaTimeSeconds);
    hud->showCMDScore();
    hud->endGame(avatar);

    for (i = obstacles.begin(); i < obstacles.end(); i++) {
        RenderSimpleMesh(meshes["box"], shaders["WallShader"], i->getModelMatrix(), glm::vec3 (0.604, 0.804, 0.196));
    }

    for (l = floor.begin(); l < floor.end(); l++) {
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], l->getMatrix(), glm::vec3(0.902, 0.902, 0.980));
    }

    RenderHUDMesh(meshes["box"], shaders["LabShader"], hud->getHBarMatrix(), glm::vec3(0.902, 0.902, 0.980));
    RenderHUDMesh(meshes["box"], shaders["LabShader"], hud->getSBarMatrix(), glm::vec3(0.902, 0.902, 0.980));
    RenderHUDMesh(meshes["box"], shaders["LabShader"], hud->getTBarMatrix(), glm::vec3(0.902, 0.902, 0.980));

    for (int i = 0; i < avatar->getHealth(); i++) {
        modelMatrix = glm::mat4(1) * transform3D::Translate(hud->getPStartingPos().x + 4.f - (float) i,
            hud->getPStartingPos().y + 4.5f, hud->getPStartingPos().z) *
            transform3D::Scale(1.f, 0.5f, 0.01f);
        RenderHUDMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1.000, 0.271, 0.000));
    }
    if (hud->getScore() > 0) {
        for (int i = 0; i < hud->getScore(); i++) {
            modelMatrix = glm::mat4(1) * transform3D::Translate(hud->getPStartingPos().x - 4.35f + (float)i / 3.333333333f,
                hud->getPStartingPos().y + 4.5f, hud->getPStartingPos().z) *
                transform3D::Scale(0.3f, 0.5f, 0.01f);
            RenderHUDMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.486, 0.988, 0.000));
        }
    }

    if (hud->getSquareNo() > 1) {
        for (int i = 0; i < hud->getSquareNo(); i++) {
            modelMatrix = glm::mat4(1) * transform3D::Translate(hud->getPStartingPos().x - 4.25f ,
                hud->getPStartingPos().y - 1.65f + (float)i / 3.333333333f, hud->getPStartingPos().z) *
                transform3D::Scale(0.5f, 0.3f, 0.01f);
            RenderHUDMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.824, 0.412, 0.118));
        }
    }
    else if (hud->getSquareNo() == 1) {
        timeScale -= deltaTimeSeconds /2.78f;
        modelMatrix = glm::mat4(1) * transform3D::Translate(hud->getPStartingPos().x - 4.25f,
            hud->getPStartingPos().y , hud->getPStartingPos().z) *
            transform3D::Scale(0.5f, timeScale, 0.01f);
        RenderHUDMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.824, 0.412, 0.118));
    }

    if (camera->firstPerson == 0) {
        avatar->setStartingPos(camera->GetTargetPosition());
        avatar->setPlayerMatrix();
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getBody(), glm::vec3(0.565, 0.933, 0.565));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getHead(), glm::vec3(1.000, 0.871, 0.678));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getLArm(), glm::vec3(0.980, 0.980, 0.824));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getRArm(), glm::vec3(0.980, 0.980, 0.824));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getLHand(), glm::vec3(1.000, 0.871, 0.678));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getRHand(), glm::vec3(1.000, 0.871, 0.678));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getLLeg(), glm::vec3(0.545, 0.271, 0.075));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], avatar->getRLeg(), glm::vec3(0.545, 0.271, 0.075));
        //RenderSimpleMesh(meshes["box"], shaders["VertexNormal"], avatar->getBB(), glm::vec3(0.545, 0.271, 0.075));
    }
    else {
        RenderHUDMesh(meshes["box"], shaders["LabShader"],hud->getCrosshairHor(), glm::vec3(1.000, 0.000, 1.000));
        RenderHUDMesh(meshes["box"], shaders["LabShader"], hud->getCrosshairVert(), glm::vec3(1.000, 0.000, 1.000));
    }
   
    for (i = obstacles.begin(); i < obstacles.end(); i++) {
       
        collisions::Collision collision = collisions::CheckAWCollision(avatar, i);
        if (std::get<0>(collision)) {
            collisions::Direction dir = std::get<1>(collision);
            glm::vec2 diff_vector = std::get<2>(collision);
            if (dir == collisions::LEFT)
            {
                
                if (avatar->getStartingPos().x - camera->position.x >= 0) {
                   
                    camera->position = glm::vec3(i->getPos().x - 1.01f - avatar->getBbX() / 2.0f - abs(avatar->getStartingPos().x - camera->position.x), camera->position.y, camera->position.z);
                }
                else {
                  
                    camera->position = glm::vec3(i->getPos().x - 0.99f - avatar->getBbX() / 2.0f + abs(avatar->getStartingPos().x - camera->position.x), camera->position.y, camera->position.z);

                }
            }
            else if (dir == collisions::RIGHT)
            {
               
                if (avatar->getStartingPos().x - camera->position.x < 0) {
                    
                    camera->position = glm::vec3(i->getPos().x + 1.01f + avatar->getBbX() / 2.0f + abs(avatar->getStartingPos().x - camera->position.x), camera->position.y, camera->position.z);
                }
                else {
                    
                    camera->position = glm::vec3(i->getPos().x + 0.99f + avatar->getBbX() / 2.0f - abs(avatar->getStartingPos().x - camera->position.x), camera->position.y, camera->position.z);
                }
            }
            else if (dir == collisions::FORWARD)
            {
               
                if (avatar->getStartingPos().z - camera->position.z < 0) {
                  
                    camera->position = glm::vec3(camera->position.x, camera->position.y, i->getPos().z + 1.01f + avatar->getBbZ() / 2.0f + abs(avatar->getStartingPos().z - camera->position.z));
                }
                else {
                    
                    camera->position = glm::vec3(camera->position.x, camera->position.y, i->getPos().z + 0.99f + avatar->getBbZ() / 2.0f - abs(avatar->getStartingPos().z - camera->position.z));
                }
            }
            else
            {
              
                if (avatar->getStartingPos().z - camera->position.z >= 0) {
                   
                    camera->position = glm::vec3(camera->position.x, camera->position.y, i->getPos().z - 1.01f - avatar->getBbZ() / 2.0f - abs(avatar->getStartingPos().z - camera->position.z));
                }
                else {
                   
                    camera->position = glm::vec3(camera->position.x, camera->position.y, i->getPos().z - 0.99f - avatar->getBbZ() / 2.0f + abs(avatar->getStartingPos().z - camera->position.z));
                }
            }
        }
    }

    if (weapon.size() > 0) {
    
        for (j = weapon.begin(); j < weapon.end();) {
            j->setAirTime(deltaTimeSeconds);
            j->setTranslate(deltaTimeSeconds);
            j->setModelMatrix();
            j->setRealPos();

            for (i = obstacles.begin(); i < obstacles.end(); i++) {
                if (collisions::CheckPrOCollision(j, i)) {
                    j->setSpawn(false);
                }
            }

            if (enemies.size() > 0) {
                for (k = enemies.begin(); k < enemies.end(); k++) {
                    if (collisions::CheckPrECollision(j, k)) {
                        j->setSpawn(false);
                        k->setHealth(0);
                        Enemy enemy;
                        enemy.setInitialPos(k->getInitialPos().x, k->getInitialPos().y, k->getInitialPos().z);
                        enemy.setModelMatrix();
                        deathBed.push_back(enemy);
                        hud->setScore();
                        hud->setShowScore(true);
                    }
                }
            }

            if (j->getAirTime() > 5 || !j->getSpawn()) {
                j = weapon.erase(j);
            }
            else {
                RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], j->getModelMatrix(), glm::vec3(0.502, 0.502, 0.000));

                ++j;
            }
        }
    }

    if (enemies.size() > 0) {
        for (k = enemies.begin(); k < enemies.end();) {
            k->setStep(deltaTimeSeconds);
            k->setModelMatrix();

            if (collisions::CheckEPCollision(avatar, k))
            {
                k->setHealth(0);
                avatar->setHealth();
            }

            if (k->getHealth() < 1) {
                Tile tile;
                tile.setMatrix(k->getInitialPos().x, -0.05f, k->getInitialPos().z);
                floor.push_back(tile);
                k = enemies.erase(k);
            }
            else {
                RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], k->getModelMatrix(), glm::vec3(1.000, 0.271, 0.000));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], k->getFloorMatrix(), glm::vec3(1.000, 1.000, 0.000));
                ++k;
            }
        }
    }

    if (deathBed.size() > 0) {
        for (m = deathBed.begin(); m < deathBed.end();) {
            m->setStep(deltaTimeSeconds);
            m->setModelMatrix();
            m->setDeathTimer(deltaTimeSeconds);
            
            if (m->getDeathTimer() <= 0) {
                m = deathBed.erase(m);
            }
            else {
                RenderDefMesh(meshes["sphere"], shaders["DefShader"], m->getModelMatrix(), glm::vec3(1.000, 0.271, 0.000));
                RenderSimpleMesh(meshes["box"], shaders["LabShader"], m->getFloorMatrix(), glm::vec3(1.000, 1.000, 0.000));
                ++m;
            }
        }
    }

}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectMatrix);
    
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;
    glUseProgram(shader->program);
    glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glm::mat4 projectionMatrix = projectMatrix;

    int modelLocation = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
   
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderDefMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;
    glUseProgram(shader->program);
    glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glm::mat4 projectionMatrix = projectMatrix;

    int timeLocation = glGetUniformLocation(shader->GetProgramID(), "time");
    glUniform1f(timeLocation, (float)Engine::GetElapsedTime());

    int modelLocation = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderHUDMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);
    glUniform3f(glGetUniformLocation(shader->program, "object_color"), color.x, color.y, color.z);

    glm::mat4 viewMatrix = camera_Hud->GetViewMatrix();
    glm::mat4 projectionMatrix = glm::ortho(-5.f, 5.f, -5.f, 5.f, 0.5f, 10.f);

    int modelLocation = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    modelLocation = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        float cameraSpeed = 3.f;
        if (camera->firstPerson == 0) {
            if (window->KeyHold(GLFW_KEY_W)) {
                camera->MoveForward(cameraSpeed * deltaTime);
            }



            if (window->KeyHold(GLFW_KEY_A)) {
                camera->TranslateRight(-cameraSpeed * deltaTime);
            }



            if (window->KeyHold(GLFW_KEY_S)) {
                camera->MoveForward(-cameraSpeed * deltaTime);
            }



            if (window->KeyHold(GLFW_KEY_D)) {
                camera->TranslateRight(cameraSpeed * deltaTime);
            }
        }

}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    if (camera->firstPerson == 0)
    {
        if (key == GLFW_KEY_LEFT_CONTROL)
        {
            camera->firstPerson = true;
            camera->forward_copy = camera->forward;
            camera->up_copy = camera->up;
            camera->right_copy = camera->right;
            camera->position_copy = camera->position;
            camera->TranslateForward(1);

        }
    }
    else {
        if (key == GLFW_KEY_LEFT_CONTROL)
        {
            camera->firstPerson = false;
            camera->forward = camera->forward_copy;
            camera->up = camera->up_copy;
            camera->right = camera->right_copy;
            camera->position = camera->position_copy;
        }
    }

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;



        if (!camera->firstPerson) {
            glm::vec3 angleX = camera->right;
            glm::vec3 angleY = camera->up;

            camera->RotateThirdPerson_OX(-deltaY * sensivityOY);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
            avatar->setRad(atan2(angleX.z, angleX.x), atan2(angleY.y, 0), 0);
            

        } else {
            glm::vec3 angleX = camera->right;
            glm::vec3 angleY = camera->up;
            camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
        }
        
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_2 && fireRate < Engine::GetElapsedTime()) {
        fireRate = Engine::GetElapsedTime() + 0.5f;
        Projectile projectile;
        projectile.setInitialPos(avatar->getStartingPos());
        projectile.setTrajectory(camera->forward);
        projectile.setModelMatrix();
        weapon.push_back(projectile);
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
