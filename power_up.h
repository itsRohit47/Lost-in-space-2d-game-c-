#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

#include "splashkit.h"

/**
 * Different options for the kind of power up.
 * Adjusts the image used.
 */
enum power_up_kind
{
    FUEL,
    TIME,
    POTION,
    SHIELD,
    CASH,
    COIN,
};

/**
 * The power up data keeps track of all of the information related to the power up.
 * 
 * @field   power_up_sprite   The power_up's sprite used to track position and collisions
 * @field   kind              Current kind of power up
 * @field   counter           a life counter for the power up
 */
struct power_up_data
{
    sprite power_up_sprite;
    power_up_kind kind;
    int counter;
};

/**
 * The power up bitmap function converts a power up kind into a 
 * bitmap that can be used.
 * 
 * 
 * @param kind  The kind of power up you want the bitmap of
 * @return      The bitmap matching this power up kind
 */
bitmap power_up_bitmap(power_up_kind kind);

/**
 * The new power up function creates a new  power up sprite  
 * that will be drawn in game enviornment
 * 
 * 
 * @param x     position of the power up on x axis
 * @param y     position of the power up on y axis
 * @return      The power up data 
 */
power_up_data new_power_up(double x, double y);

/**
 * The draw power up procedure draws the power up sprite 
 * in the game enviornment
 * @param power_up_to_draw     The power up to draw
 */
void draw_power_up(const power_up_data &power_up_to_draw);

/**
 * The update power up procedure updates any data related to 
 * the power up sprite in the game enviornment
 * @param power_up_to_update     The power up to update
 */
void update_power_up(power_up_data &power_up_to_update);

#endif