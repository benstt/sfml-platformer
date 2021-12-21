//
// Created by benja on 19/12/2021.
//

#include "EntityTracker.h"

uint64_t EntityTracker::s_EntityAmount = 0;
std::vector<std::reference_wrapper<Entity>> EntityTracker::s_Entities {};

void EntityTracker::addEntity(Entity& entity) {
    EntityTracker::s_Entities.emplace_back(entity);
    s_EntityAmount++;
}

bool EntityTracker::removeEntity(uint64_t ID) {
    for (size_t i = 0; i < EntityTracker::s_Entities.size(); ++i) {
        auto& e = EntityTracker::s_Entities[i];
        if (e.get().ID == ID) {
            EntityTracker::s_Entities.erase(EntityTracker::s_Entities.begin() + i);
            return true;
        }
    }

    return false;
}

uint64_t EntityTracker::entityAmount() {
    return EntityTracker::s_EntityAmount;
}

std::vector<std::reference_wrapper<Entity>> EntityTracker::entities() {
    std::vector<std::reference_wrapper<Entity>> entities;
    for (auto e : EntityTracker::s_Entities) {
        entities.push_back(e);
    }

    return entities;
}