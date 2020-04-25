#include "Game.h"
#include "Globals.h"
#include "game_math.h"
#include "input.h"
#include "loading_helpers.h"

#include <cmath>
#include <iostream>


Game::Game()
{
    Entity* tmp = new Entity();

    player.add_child(tmp);

    // tmp->set_local_transform({{50.0f, 0.0f}, 45.0f});

    entity.add_child(tmp);

    entity.add_force({10.0f, 10.0f});
    tmp->add_force({10.0f, 10.0f});
}

Game::~Game() {}

void Game::render()
{
    player.render();
    entity.render();
}

void Game::update(Uint32 delta)
{
    float delta_f = static_cast<float>(delta) / 1000.0f;
    player.update(delta_f);
    entity.update(delta_f);
}
