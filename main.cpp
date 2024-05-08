#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

// screencast link : https://video.deakin.edu.au/media/t/1_4ybwy86m

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 1200, 600);

    load_resources(); // Load the game images, sounds, etc.

    game_data game = new_game(); // new game initialized

    while (not quit_requested()) // loop until not quit
    {

        process_events();
        handle_input(game.player);

        update_game(game);

        draw_game(game);
    }
    return 0;
}
