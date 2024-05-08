#ifndef LOST_IN_SPACE_GAME
#define LOST_IN_SPACE_GAME

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <vector>
using std::vector;

/**
 * Load the game images, sounds, etc.
 */
void load_resources();

/**
 * The game data keeps track of all of the information related to the player and powerups
 * 
 * @field   player      the player in the game
 * @field   power ups   all the power ups in the game
 */
struct game_data
{
    player_data player;
    vector<power_up_data> power_ups;
};

/**
 * The new game function creates a new game that will be used do every operation in the game
 * 
 * @return      The game data 
 */
game_data new_game();

/**
 * The draw hud procedure draws the hud and its elemets such as player score, cash, fuel and so on
 * 
 * @param game     the game itself
 */
void draw_hud(const game_data &game);

/**
 * The add power up procedure pushes random power up sprites in the game
 * 
 * @param game     the game itself
 */
void add_power_up(game_data &game);

/**
 * The apply power up procedure update player data based on power up kind
 * 
 * @param game     the game itself
 * @param index    index of the power up being applied
 */
void apply_power_up(game_data &game, int index);

/**
 * The remove power up procedure removes the power up sprite from the game 
 * 
 * @param game     the game itself
 * @param index    index of the power up being removed from the game
 */
void remove_power_up(game_data &game, int index);

/**
 * The check collisions procedure keep track of any collision between player's sprite and power up's sprite
 * 
 * @param game     the game itself
 */
void check_collisions(game_data &game);

/**
 * The update game procedure updates player's sprite and power up's sprite
 * 
 * @param game     the game itself
 */
void update_game(game_data &game);

/**
 * The draw game redraws eveything inside the game 
 * 
 * @param game     the game itself
 */
void draw_game(const game_data &game);

#endif