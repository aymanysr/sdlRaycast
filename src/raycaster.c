#include "../headers/raycaster.h"
#include "../headers/player.h"
#include "../headers/map.h"
#include "../headers/constants.h"
#include <math.h>

void render_scene(SDL_Renderer *renderer) {
  int w, h;
  // Retrieve the size of the output of a renderer.
  SDL_GetRendererOutputSize(renderer, &w, &h);

  for (int x = 0; x < w; x++) {
    // Calculate the camera's x-coordinate in the virtual screen space
    float camera_x = 2 * x / (float)w - 1;

    // Calculate the direction of the ray
    float ray_dir_x = sinf(player.angle) + camera_x * cosf(player.angle);
    float ray_dir_y = cosf(player.angle) - camera_x * sinf(player.angle);

    // Determine the player's current map position
    int map_x = (int)player.x;
    int map_y = (int)player.y;

    // Calculate the distance between the player and the next x or y side
    float side_dist_x;
    float side_dist_y;

    // Calculate the distance between the player and the next x or y side
    float delta_dist_x = fabs(1 / ray_dir_x);
    float delta_dist_y = fabs(1 / ray_dir_y);
    float perp_wall_dist;

    // Determine the step direction and initial side distance
    int step_x;
    int step_y;

    // Determine the step direction and initial side distance
    int hit = 0;
    int side;

    // Determine the step direction and initial side distance
    if (ray_dir_x < 0) {
      step_x = -1;
      side_dist_x = (player.x - map_x) * delta_dist_x;
    } else {
      step_x = 1;
      side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x;
    }
    if (ray_dir_y < 0) {
      step_y = -1;
      side_dist_y = (player.y - map_y) * delta_dist_y;
    } else {
      step_y = 1;
      side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y;
    }

    // Perform DDA (Digital Differential Analysis) algorithm to find the intersection point with a wall
    while (hit == 0) {
      if (side_dist_x < side_dist_y) {
        side_dist_x += delta_dist_x;
        map_x += step_x;
        side = 0;
      } else {
        side_dist_y += delta_dist_y;
        map_y += step_y;
        side = 1;
      }
      if (worldMap[map_x][map_y] > 0) hit = 1;
    }

    // Calculate the perpendicular wall distance
    if (side == 0) perp_wall_dist = (map_x - player.x + (1 - step_x) / 2) / ray_dir_x;
    else perp_wall_dist = (map_y - player.y + (1 - step_y) / 2) / ray_dir_y;

    // Calculate the height of the wall slice to be rendered
    int line_height = (int)(h / perp_wall_dist);

    // Calculate the start and end positions of the wall slice to be rendered
    int draw_start = -line_height / 2 + h / 2;
    if (draw_start < 0) draw_start = 0;
    int draw_end = line_height / 2 + h / 2;
    if (draw_end >= h) draw_end = h - 1;

    // Set the render draw color based on the side of the wall
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (side == 1) SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    // Render the wall slice
    SDL_RenderDrawLine(renderer, x, draw_start, x, draw_end);
  }
}
