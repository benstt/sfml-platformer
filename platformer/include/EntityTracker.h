//
// Created by benja on 19/12/2021.
//

#ifndef PLATFORMER_ENTITYTRACKER_H
#define PLATFORMER_ENTITYTRACKER_H

#include "Entity.h"

class EntityTracker {
public:
    static void addEntity(Entity& entity);
    static bool removeEntity(uint64_t ID);
    static uint64_t entityAmount();
    static std::vector<std::reference_wrapper<Entity>> entities();
private:
    static uint64_t s_EntityAmount;
    static std::vector<std::reference_wrapper<Entity>> s_Entities;
};

#endif //PLATFORMER_ENTITYTRACKER_H
