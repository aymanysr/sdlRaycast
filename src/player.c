#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/map.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

int last_frame_time = 0;
// Initialize player properties
Player player = {18.7f, 5.09f, 0.0f, 4.0f, 45 * (M_PI / 180)};


void init_player() {
  player.x = 18.7f;
  player.y = 5.09f;
  player.angle = 0.0f;
  player.speed = 4.0f;
  player.rotation_speed = 45 * (M_PI / 180); // converting 45 rotation speed degrees from deg/sec to rads/sec using (M_PI / 180deg)
}

void print_player_info(float delta_time) {
    printf("Player position: (%f, %f)\n", player.x, player.y);
    printf("Player angle: %f\n", player.angle);
    printf("Player speed: %f\n", player.speed);
    printf("Player rotation speed: %f\n", player.rotation_speed);
    printf("FPS: %f\n", 1.0f / delta_time);
}

void update_player() {
  // Get the current ticks (time since SDL library initialization)
  Uint32 current_ticks = SDL_GetTicks();

  // Sleep the execution until we reach the target frame time in milliseconds
  int time_to_wait = MY_FRAME_TARGET_TIME - (current_ticks - last_frame_time);

  // Only call delay if we are too fast to process this frame
  if (time_to_wait > 0 && time_to_wait <= MY_FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait); // SDL_Delay to avoid using a while loop
  }

  // Calculate the time elapsed since the last frame in SECONDS to be used to update my objects
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f; // the amount of time in seconds that has passed since the last frame.

  // Update the last frame time to the current ticks
  last_frame_time = current_ticks;

  // Get the current keyboard state
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  float new_x = player.x;
  float new_y = player.y;

  if (state[SDL_SCANCODE_W]) {
      new_x += sinf(player.angle) * player.speed * delta_time;
      new_y += cosf(player.angle) * player.speed * delta_time;
  }

  if (state[SDL_SCANCODE_S]) {
      new_x -= sinf(player.angle) * player.speed * delta_time;
      new_y -= cosf(player.angle) * player.speed * delta_time;
  }

  if (state[SDL_SCANCODE_A]) {
    player.angle -= player.rotation_speed * delta_time;
  }

  if (state[SDL_SCANCODE_D]) {
    player.angle += player.rotation_speed * delta_time;
  }

  // Normalize the angle to keep it within the range of 0 to 2π
  player.angle = fmod(player.angle, 2 * M_PI);
  if (player.angle < 0) {
    player.angle += 2 * M_PI;
  }

  // The game world bounds collision detection
  if (!is_wall(new_x, new_y)) {
    player.x = new_x;
    player.y = new_y;
  }

  print_player_info(delta_time);
}
