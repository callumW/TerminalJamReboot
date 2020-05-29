#include <iostream>

#include "Globals.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "loading_helpers.h"

RenderManager& RenderManager::get()
{
    static RenderManager render_manager;
    return render_manager;
}


void RenderManager::render_all()
{
    size_t const num_components = components.size();
    for (size_t i = 0; i < num_components; i++) {
        render_component_t& comp = components[i];

        if (!comp.hidden) {

            if (entities[i].has_component(PHYSICS)) {
                auto physics_comp = PhysicsManager::get().get_component(entities[i]);
                if (physics_comp && physics_comp->body) {
                    comp.set_position(
                        convert_to_screen_space(physics_comp->body->GetWorldCenter()));
                }
            }

            SDL_RenderCopyEx(g_renderer, comp.texture.tex, &comp.texture.src_rect, &comp.dst_rect,
                             comp.rotation, &comp.pivot_point, comp.flip);
        }
    }
}

render_component_t* RenderManager::create_render_component(entity_t* entity,
                                                           std::string const& tex_path)
{
    render_component_t* comp = create_component(entity);

    comp->texture = load_texture(tex_path);
    comp->pivot_point = {comp->texture.src_rect.w / 2, comp->texture.src_rect.h / 2};
    comp->dst_rect = comp->texture.src_rect;

    return comp;
}

vec2f_t RenderManager::convert_to_screen_space(vec2f_t const& world_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);
    static vec2f_t view_port_top_left = {0.0f - viewport_width / 2.0f,
                                         0.0f - viewport_height / 2.0f};
    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return {world_pos.x - view_port_top_left.x, (0 - world_pos.y) - view_port_top_left.y};
}
vec2f_t RenderManager::convert_to_world_pos(vec2f_t const& screen_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);

    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return {screen_pos.x - world_center.x, 0 - (screen_pos.y - world_center.y)};
}

vec2f_t RenderManager::convert_to_screen_space(b2Vec2 const& world_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);
    static vec2f_t view_port_top_left = {0.0f - viewport_width / 2.0f,
                                         0.0f - viewport_height / 2.0f};

    return {world_pos.x - view_port_top_left.x, (0 - world_pos.y) - view_port_top_left.y};
}
vec2f_t RenderManager::convert_to_world_pos(b2Vec2 const& screen_pos)
{
    static float viewport_width = static_cast<float>(WINDOW_WIDTH);
    static float viewport_height = static_cast<float>(WINDOW_HEIGHT);

    static vec2f_t world_center = {viewport_width / 2.0f, viewport_height / 2.0f};

    return {screen_pos.x - world_center.x, 0 - (screen_pos.y - world_center.y)};
}
