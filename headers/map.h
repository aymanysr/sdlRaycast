#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

extern const int worldMap[MAP_WIDTH][MAP_HEIGHT];

int is_wall(float x, float y);
#endif /* MAP_H */
