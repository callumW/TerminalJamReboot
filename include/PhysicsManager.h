#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include <array>
#include <unordered_map>
#include <vector>

#include "PhysicsComponent.h"
#include "entity_id.h"

class PhysicsManager {
public:
    static constexpr float GRAVITY = 300.0f;

    static PhysicsManager& get();

    void cleanup();

    void check_for_moved_entities();
    void check_for_dead_entities();

    void simulate(float delta);

    physics_component_t* new_physics_component(entity_id_t id);

    std::vector<entity_id_t> const& dirty_entities() const { return dirty_components; }

    physics_component_t const* get_physics_component(entity_id_t id);

private:
    PhysicsManager();

    void update_entity_mapping(entity_id_t const& old_id, entity_id_t const& new_id);

    void log_map();

    void validate_map();

    void verify_removed(entity_id_t const& id);

    std::unordered_map<entity_id_t, size_t, entity_id_hash_t, entity_id_t_compare_t> map;
    std::vector<physics_component_t> physics_components;

    std::vector<entity_id_t> dirty_components;
};
#endif
