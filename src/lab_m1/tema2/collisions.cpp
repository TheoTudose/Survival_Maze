#include "collisions.h"
#include <vector>
#include <iostream>
#include "lab_m1/tema2/transform3D.h"
#include "avatar.h"
#include "wall.h"
#include "projectile.h"
#include "enemy.h"

collisions::Direction collisions::VectorDirection(glm::vec2 target)
{
    glm::vec3 compass[] = {
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, +1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };
    glm::vec3 target_3 = glm::vec3(target.x, 0, target.y);
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target_3), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}


collisions::Collision collisions::CheckAWCollision(Avatar* player, std::vector<Wall>::iterator i)
{
   bool collisionX = player->getStartingPos().x + abs(player->getBbX()) / 2.0f >= i->getPos().x - 1.0f &&
        i->getPos().x + 1.0f >= player->getStartingPos().x - abs(player->getBbX()) / 2.0f;
   bool collisionZ = player->getStartingPos().z + abs(player->getBbZ()) / 2.0f >= i->getPos().z - 1.0f &&
        i->getPos().z + 1.0f >= player->getStartingPos().z - abs(player->getBbZ()) / 2.0f;
   glm::vec2 difference = glm::vec2(player->getStartingPos().x, player->getStartingPos().z) - glm::vec2(i->getPos().x, i->getPos().z);
  
   if (collisionX && collisionZ == true) {
       return std::make_tuple(true, VectorDirection(difference), glm::vec2(0.0f, 0.0f));
   }
   else {
       return std::make_tuple(false, FORWARD, glm::vec2(0.0f, 0.0f));
   }
   
}

bool collisions::CheckPrOCollision(std::vector<Projectile>::iterator i, std::vector<Wall>::iterator j)
{
    glm::vec2 difference = glm::vec2(i->getRealPos().x, i->getRealPos().z) - glm::vec2(j->getPos().x, j->getPos().z);
    glm::vec2 clamped = glm::clamp(difference, -glm::vec2(1.0f), glm::vec2(1.0f));
    glm::vec2 closest = glm::vec2(j->getPos().x, j->getPos().z) + clamped;
    difference = closest - glm::vec2(i->getRealPos().x, i->getRealPos().z);
    return glm::length(difference) < 0.1f;
}

bool collisions::CheckPrECollision(std::vector<Projectile>::iterator i, std::vector<Enemy>::iterator j)
{
    glm::vec3 difference = i->getRealPos() - j->getPos();
    return glm::length(difference) < 0.5f;
}

bool collisions::CheckEPCollision(Avatar* player, std::vector<Enemy>::iterator i)
{
    glm::vec2 playerPos = glm::vec2(player->getStartingPos().x, player->getStartingPos().z);
    glm::vec2 square_halves(player->getBbX() / 2.0f, player->getBbZ() / 2.0f);
    
    glm::vec2 difference = glm::vec2(i->getPos().x, i->getPos().z) - playerPos;
    glm::vec2 clamped = glm::clamp(difference, -square_halves, square_halves);
    glm::vec2 closest = playerPos + clamped;
    difference = closest - glm::vec2(i->getPos().x, i->getPos().z);
    return glm::length(difference) < 0.4f;
}