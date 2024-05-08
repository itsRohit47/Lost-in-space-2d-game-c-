#include "splashkit.h"
#include "power_up.h"

bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case SHIELD:
        return bitmap_named("shield");
        break;
    case POTION:
        return bitmap_named("potion");
        break;
    case FUEL:
        return bitmap_named("fuel");
        break;
    case CASH:
        return bitmap_named("cash");
        break;
    case COIN:
        return bitmap_named("coin");
        break;
    case TIME:
        return bitmap_named("time");
        break;
    default:
        return bitmap_named("time");
        break;
    }
}

power_up_data new_power_up(double x, double y)
{
    power_up_data result;
    result.kind = static_cast<power_up_kind>(rnd(6));
    result.counter = 1000;
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);
    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);
    return result;
}

void draw_power_up(const power_up_data &power_up_to_draw)
{
    draw_sprite(power_up_to_draw.power_up_sprite);
}

void update_power_up(power_up_data &power_up_to_update)
{
    update_sprite(power_up_to_update.power_up_sprite);
    power_up_to_update.counter -= 1;
}
