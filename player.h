#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include <vector>

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 90

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   cash            The current cash for the player
 * @field   coins           The current coins for the player
 * @field   kind            Current kind of player ship
 * @field   fuel_pct        Current percentage of total fuel in the ship
 * @field   potion_pct      Current percentage of total potion in the ship
 * @field   time_pct        Current percentage of total time in the ship
 * @field   shield_pct      Current percentage of total shield in the ship
 */
struct player_data
{
    sprite player_sprite;
    int score;
    int cash;
    int coins;
    ship_kind kind;
    double fuel_pct;
    double potion_pct;
    double time_pct;
    double shield_pct;
};

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Draws the player to the screen. 
 * 
 * @param player_to_draw    The player to draw to the screen
 */
void draw_player(const player_data &player_to_draw);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player_to_update      The player being updated
 */
void update_player(player_data &player_to_update);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

#endif