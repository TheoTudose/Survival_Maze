#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/wall.h"
#include "lab_m1/tema2/labirint.h"
#include "lab_m1/tema2/camera_class.h"
#include "lab_m1/tema2/avatar.h"
#include "lab_m1/tema2/crosshair.h"
#include "lab_m1/tema2/projectile.h"
#include "lab_m1/tema2/enemy.h"
#include "lab_m1/tema2/tile.h"
#include "lab_m1/tema2/hud.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderDefMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderHUDMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::Camera* camera;
        implemented::Camera* camera_Hud;
        glm::mat4 projectMatrix;
        bool renderCameraTarget;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        float step;
        float timeScale = 3.6f;
        std::vector<Wall> obstacles;
        std::vector<Projectile> weapon;
        std::vector<Enemy> enemies;
        std::vector<Tile> floor;
        std::vector<Enemy> deathBed;
        Labirint* labirint;
        std::vector<Wall>::iterator i;
        std::vector<Projectile>::iterator j;
        std::vector<Enemy>::iterator k;
        std::vector<Tile>::iterator l;
        std::vector<Enemy>::iterator m;

        Avatar* avatar;
        float fireRate;
        Hud* hud;


    };

}   // namespace m1
