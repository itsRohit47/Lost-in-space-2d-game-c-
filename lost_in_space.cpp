#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

#define MIN -1500
#define MAX 1500

void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

game_data new_game()
{
    game_data game;
    game.player = new_player(); // create a player
    return game;
}

/**
 * this function keep tracks of the power up positions and returns the mini map cordinates for the power ups based on its position
 * */
point_2d mini_map_coordinate(const power_up_data &power_up)
{
    point_2d result;
    double hud_width = screen_width() - screen_width() / 3.5;
    double mini_map_x = hud_width + (screen_width() / 3.5 - 100) / 2;
    double mini_map_y = (screen_height() - 150);
    double power_up_x = sprite_x(power_up.power_up_sprite);
    double power_up_y = sprite_y(power_up.power_up_sprite);
    result.x = (((power_up_x + 1500) / 3000) * 100) + mini_map_x;
    result.y = (((power_up_y + 1500) / 3000) * 100) + mini_map_y;
    return result;
}

/**
 * this function keep tracks of the player positions and returns the mini map cordinates for the player based on its position
 * */
point_2d mini_map_coordinate_player(const player_data &player)
{
    point_2d result;
    double hud_width = screen_width() - screen_width() / 3.5;
    double mini_map_x = hud_width + (screen_width() / 3.5 - 100) / 2;
    double mini_map_y = (screen_height() - 150);
    double player_x = sprite_x(player.player_sprite);
    double player_y = sprite_y(player.player_sprite);
    result.x = (((player_x + 1500) / 3000) * 100) + mini_map_x;
    result.y = (((player_y + 1500) / 3000) * 100) + mini_map_y;
    return result;
}

/**
 * this procedure draws the powerups on the minimap based on its coordinates
 * */
void draw_mini_map(const vector<power_up_data> &power_ups)
{
    for (int i = power_ups.size() - 1; i >= 0; i--)
    {
        draw_pixel(COLOR_SILVER, mini_map_coordinate(power_ups[i]), option_to_screen());
    }
}

/**
 * this procedure draws the player on the minimap based on its coordinates
 * */
void draw_mini_map_player(const player_data &player)
{
    draw_pixel(COLOR_RED, mini_map_coordinate_player(player), option_to_screen());
}

void draw_hud(const game_data &game)
{
    double hud_width = screen_width() - screen_width() / 3.5;
    // show hud background
    fill_rectangle(COLOR_LIGHT_YELLOW, hud_width, 0, screen_width() / 3.5, screen_height(), option_to_screen());
    // show score
    draw_text("S C O R E : " + to_string(game.player.score), COLOR_BLACK, "font.otf", 20, hud_width + 5, 20, option_to_screen());

    // show sprite(player) location
    point_2d player_pos = sprite_position(game.player.player_sprite);
    draw_text("L O C A T I O N :   " + to_string(player_pos.x) + "  __  " + to_string(player_pos.y), COLOR_BLACK, "font.otf", 18, hud_width + 5, 50, option_to_screen());

    // fuel settings
    if (game.player.fuel_pct <= 1)
    {
        draw_bitmap("fuel", hud_width + 270, 70, option_scale_bmp(0.5, 0.5, option_to_screen()));
        draw_bitmap("empty", hud_width, 100, option_to_screen());
        draw_bitmap("full_fuel", hud_width, 100, option_part_bmp(0, 0, game.player.fuel_pct * bitmap_width("full_fuel"), bitmap_height("full_fuel") - 10, option_to_screen()));
    }

    // potion settings
    if (game.player.potion_pct <= 1)
    {
        draw_bitmap("potion", hud_width + 270, 120, option_scale_bmp(0.5, 0.5, option_to_screen()));
        draw_bitmap("empty", hud_width, 150, option_to_screen());
        draw_bitmap("full_potion", hud_width, 150, option_part_bmp(0, 0, game.player.potion_pct * bitmap_width("full_potion"), bitmap_height("full_potion") - 10, option_to_screen()));
    }

    // time settings
    if (game.player.time_pct <= 1)
    {
        draw_bitmap("time", hud_width + 270, 170, option_scale_bmp(0.5, 0.5, option_to_screen()));
        draw_bitmap("empty", hud_width, 200, option_to_screen());
        draw_bitmap("full_time", hud_width, 200, option_part_bmp(0, 0, game.player.time_pct * bitmap_width("full_time"), bitmap_height("full_time") - 10, option_to_screen()));
    }

    // shield settings
    if (game.player.shield_pct <= 1)
    {
        draw_bitmap("shield", hud_width + 270, 220, option_scale_bmp(0.5, 0.5, option_to_screen()));
        draw_bitmap("empty", hud_width, 250, option_to_screen());
        draw_bitmap("full_shield", hud_width, 250, option_part_bmp(0, 0, game.player.shield_pct * bitmap_width("full_shield"), bitmap_height("full_shield") - 10, option_to_screen()));
    }

    draw_text("C O I N S : " + to_string(game.player.coins), COLOR_BLACK, "font.otf", 20, hud_width + 5, 300, option_to_screen());
    draw_text("C A S H : " + to_string(game.player.cash), COLOR_BLACK, "font.otf", 20, hud_width + 5, 330, option_to_screen());

    // minimap area
    fill_rectangle(COLOR_BLACK, hud_width + (screen_width() / 3.5 - 100) / 2, (screen_height() - 150), 100, 100, option_to_screen());
    draw_mini_map(game.power_ups);
    draw_mini_map_player(game.player);
}

void add_power_up(game_data &game)
{
    if (rnd() < 0.01)
    {
        game.power_ups.push_back(new_power_up(rnd() * 3000 - 1500, rnd() * 3000 - 1500));
    }
}

void remove_power_up(game_data &game, int index)
{
    int last_idx;
    last_idx = game.power_ups.size() - 1;
    game.power_ups[index] = game.power_ups[last_idx];
    game.power_ups.pop_back();
}

void apply_power_up(game_data &game, int index)
{
    game.player.score += 10;
    play_sound_effect("time");
    if (game.power_ups[index].kind == FUEL and game.player.fuel_pct < 0.9)
    {
        if (game.player.fuel_pct > 0.75)
        {
            game.player.fuel_pct = 0.89;
        }
        else
        {
            game.player.fuel_pct += 0.25;
        }
    }
    if (game.power_ups[index].kind == POTION and game.player.potion_pct < 0.9)
    {
        game.player.potion_pct += 0.10;
    }
    if (game.power_ups[index].kind == TIME and game.player.time_pct < 0.9)
    {
        game.player.time_pct += 0.10;
    }
    if (game.power_ups[index].kind == SHIELD and game.player.shield_pct < 0.9)
    {
        game.player.shield_pct += 0.10;
    }
    if (game.power_ups[index].kind == CASH)
    {
        game.player.cash += 10;
    }
    if (game.power_ups[index].kind == COIN)
    {
        game.player.coins += 10;
    }
}

void check_collisions(game_data &game)
{
    for (int i = game.power_ups.size() - 1; i >= 0; i--)
    {
        if (sprite_collision(game.power_ups[i].power_up_sprite, game.player.player_sprite))
        {
            apply_power_up(game, i);
            remove_power_up(game, i);
        }
        if (sprite_position(game.power_ups[i].power_up_sprite).x < MIN or sprite_position(game.power_ups[i].power_up_sprite).x > MAX)
        {
            remove_power_up(game, i);
        }
        if (sprite_position(game.power_ups[i].power_up_sprite).y < MIN or sprite_position(game.power_ups[i].power_up_sprite).y > MAX)
        {
            remove_power_up(game, i);
        }
    }
}

void update_game(game_data &game)
{
    add_power_up(game);
    check_collisions(game);
    update_player(game.player);
    for (int i = game.power_ups.size() - 1; i >= 0; i--)
    {
        update_power_up(game.power_ups[i]);
        if (game.power_ups[i].counter == 0)
        {
            remove_power_up(game, i);
        }
    }
}

void draw_game(const game_data &game)
{
    clear_screen(COLOR_BLACK);
    for (int i = game.power_ups.size() - 1; i >= 0; i--)
    {
        draw_power_up(game.power_ups[i]);
    }
    draw_player(game.player);
    draw_hud(game);
    refresh_screen(60);
}
