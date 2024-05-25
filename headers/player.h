#ifndef PLAYER_H
#define PLAYER_H
#define M_PI 3.14159265358979323846

typedef struct {
  float x, y; // player position
  float angle; // player rotation angle
  float speed; // player (W, S) movement speed
  float rotation_speed; // player (A, D) rotation speed
} Player;

extern Player player;

void init_player();
void update_player();

#endif /* PLAYER_H */
