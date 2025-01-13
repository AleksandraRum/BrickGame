#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../common_structure.h"

GameInfo_t *initializeGame(void);
Figure_t create_figure(int x, int y);
void drop_new_figure(Figure_t figure, GameInfo_t *game);
void clean_figure(GameInfo_t *game);
int check_collision_sides(GameInfo_t *game);
int check_collision(GameInfo_t *game);
void put_figure(GameInfo_t *game);
int find_full_line(GameInfo_t *game);
void delete_line(int full, GameInfo_t *game);
void move_line(int full, GameInfo_t *game);
int remove_lines(GameInfo_t *game);
void rotate_figure(Figure_t *figure, GameInfo_t *game);
void move_down_figure(GameInfo_t *game);
void move_right_figure(GameInfo_t *game);
void move_left_figure(GameInfo_t *game);
void copy_matrix(Figure_t *figure, GameInfo_t *game);
int check_figures_on_field(GameInfo_t *game);
int level_counter(GameInfo_t *game);
int read_max_score(void);
void rewrite_high_score(GameInfo_t *game);
int losing_position(GameInfo_t *game);
void free_matrix(int **matrix, int height);
void terminate(GameInfo_t *game);

#endif  // BACKEND_H
