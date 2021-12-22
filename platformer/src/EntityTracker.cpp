//
// Created by benja on 19/12/2021.
//

#include "EntityTracker.h"

uint64_t EntityTracker::s_EntityAmount = 0;
std::vector<std::reference_wrapper<Entity>> EntityTracker::s_Entities {};

void EntityTracker::addEntity(Entity& entity) {
    /*
     * @return void
     * - add entity to the vector
     * - sum 1 to total entities
     *
     * Adds the entity to the collection of entities.
     */

    EntityTracker::s_Entities.emplace_back(entity);
    s_EntityAmount++;
}

bool EntityTracker::removeEntity(uint64_t ID) {
    /*
     * @return success on removal
     * - loop through all entities
     * - if given ID exists, remove it
     *
     * Removes an entity from the collection of entities.
     */
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
    /*
     * @return the amount of entities
     * Returns the total amount of entities.
     */

    return EntityTracker::s_EntityAmount;
}

std::vector<std::reference_wrapper<Entity>> EntityTracker::entities() {
    /*
     * @return the collection of entities
     * Returns all the entities.
     */

    return EntityTracker::s_Entities;
}