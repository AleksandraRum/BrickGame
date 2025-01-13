#include "backend.h"

int max_score;

GameInfo_t *initializeGame(void) {
  static GameInfo_t *game = NULL;
  game = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  game->field = (int **)malloc((FIELD_HEIGHT + 1) * sizeof(int *));
  for (int i = 0; i <= FIELD_HEIGHT; i++) {
    game->field[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));
  }
  game->next = (int **)malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    game->next[i] = (int *)malloc(4 * sizeof(int));
  }
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      game->field[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = 0;
    }
  }
  game->score = 0;
  max_score = read_max_score();
  game->high_score = max_score;
  game->level = 1;
  game->speed = 2500;
  game->pause = 0;
  return game;
}

Figure_t create_figure(int x, int y) {
  int **buffer_f = (int **)malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    buffer_f[i] = (int *)malloc(4 * sizeof(int));
  }

  int figures[7][4][4] = {
      {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // I
      {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},  // L
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},  // J
      {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // O
      {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // S
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // T
      {{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // Z
  };
  int figureIndex = rand() % 7;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figures[figureIndex][i][j])
        buffer_f[i][j] = 10;
      else
        buffer_f[i][j] = 0;
    }
  }
  Figure_t f = {buffer_f, x, y};
  return f;
}

void drop_new_figure(Figure_t figure, GameInfo_t *game) {
  int fx = figure.x;
  int fy = figure.y;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      if (figure.figure[i][j]) game->field[fy][fx] = figure.figure[i][j];
      fy++;
    }
    fy = figure.y;
    fx++;
  }
}

void clean_figure(GameInfo_t *game) {
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 10) {
        game->field[i][j] = 0;
      }
    }
  }
}

int check_collision_sides(GameInfo_t *game) {
  int res = 0;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 10 && (j == 1 || ((game->field[i][j - 1] == 2) &&
                                                 (game->field[i][j - 2] == 2))))
        res = 1;
      else if (game->field[i][j] == 10 &&
               ((j == FIELD_WIDTH - 1) ||
                ((game->field[i][j + 1] == 2) && (game->field[i][j + 2] == 2))))
        res = 2;
    }
  }
  return res;
}

int check_collision(GameInfo_t *game) {
  int res = 0;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 10 &&
          ((i == FIELD_HEIGHT - 1) || game->field[i + 1][j] == 2))
        res = 1;
    }
  }
  return res;
}

void put_figure(GameInfo_t *game) {
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 10) game->field[i][j] = 2;
    }
  }
}

int find_full_line(GameInfo_t *game) {
  int full_line = -1;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    int is_full = 0;
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] != 2) {
        continue;
      } else
        is_full++;
    }
    if (is_full == FIELD_WIDTH - 1) {
      full_line = i;
      break;
    }
  }
  return full_line;
}

void delete_line(int full, GameInfo_t *game) {
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      game->field[full][j] = 0;
    }
  }
}

void move_line(int full, GameInfo_t *game) {
  for (int i = full; i > 0; i--) {
    for (int j = FIELD_WIDTH - 1; j > 0; j--) {
      if (game->field[i - 1][j] == 2) {
        game->field[i][j] = 2;
        game->field[i - 1][j] = 0;
      }
    }
  }
}

int remove_lines(GameInfo_t *game) {
  int score = 0;
  int full;
  int row_count = 0;
  while ((full = find_full_line(game)) != -1) {
    delete_line(full, game);
    move_line(full, game);
    row_count++;
  }
  switch (row_count) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
  }
  return score;
}

void rotate_figure(Figure_t *figure, GameInfo_t *game) {
  if (!check_collision_sides(game) && !check_collision(game)) {
    clean_figure(game);
    int matrix[4][4] = {0};
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        matrix[i][j] = figure->figure[3 - j][i];
      }
    }
    int counter = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if ((matrix[i][j] == 10) && (i + figure->y < FIELD_HEIGHT) &&
            (j + figure->x > 0) && (j + figure->x < FIELD_WIDTH)) {
          counter++;
        }
      }
    }
    if (counter == 4) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figure[i][j] = matrix[i][j];
        }
      }
    }
    drop_new_figure(*figure, game);
  }
}

void move_down_figure(GameInfo_t *game) {
  if (!check_collision(game)) {
    for (int i = FIELD_HEIGHT - 1; i > 0; i--) {
      for (int j = 1; j < FIELD_WIDTH; j++) {
        if (game->field[i][j] == 10 && !game->field[i + 1][j] &&
            (i + 1) != FIELD_HEIGHT) {
          game->field[i][j] = 0;
          game->field[i + 1][j] = 10;
        }
      }
    }
  } else {
    put_figure(game);
  }
}

void move_right_figure(GameInfo_t *game) {
  if (check_collision_sides(game) != 2) {
    for (int i = FIELD_HEIGHT - 1; i > 0; i--) {
      for (int j = FIELD_WIDTH - 1; j > 0; j--) {
        if (game->field[i][j] == 10 && !game->field[i][j + 1] &&
            (j + 1) != FIELD_WIDTH) {
          game->field[i][j + 1] = 10;
          game->field[i][j] = 0;
        }
      }
    }
  }
}

void move_left_figure(GameInfo_t *game) {
  if (check_collision_sides(game) != 1) {
    for (int i = FIELD_HEIGHT - 1; i > 0; i--) {
      for (int j = 1; j < FIELD_WIDTH; j++) {
        if (game->field[i][j] == 10 && !game->field[i][j - 1] && (j - 1) != 0) {
          game->field[i][j - 1] = 10;
          game->field[i][j] = 0;
        }
      }
    }
  }
}

void copy_matrix(Figure_t *figure, GameInfo_t *game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = figure->figure[i][j];
    }
  }
}

int check_figures_on_field(GameInfo_t *game) {
  int res = 0;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 10) res = 1;
    }
  }
  return res;
}

int level_counter(GameInfo_t *game) {
  int level = game->level;
  int speed = game->speed;
  int a = 600 * level;
  if (game->score / a >= 1 && game->score / a < 2) {
    level += 1;
    speed -= 250;
  } else if (game->score / a >= 2 && game->score / a < 3) {
    level += 2;
    speed -= 500;
  } else if (game->score / a >= 3) {
    level += 3;
    speed -= 750;
  }
  game->speed = speed;
  return level;
}

int read_max_score(void) {
  FILE *file = fopen("max_score.txt", "r");
  int max_sc = 0;
  if (file) {
    fscanf(file, "%d", &max_sc);
    fclose(file);
  }
  return max_sc;
}

void rewrite_high_score(GameInfo_t *game) {
  FILE *file = fopen("max_score.txt", "w");
  fprintf(file, "%d", game->score > max_score ? game->score : max_score);
  fclose(file);
}

int losing_position(GameInfo_t *game) {
  int lose = 0;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game->field[1][j] == 2) {
        lose = 1;
        break;
      }
    }
  }
  return lose;
}

void free_matrix(int **matrix, int height) {
  for (int i = 0; i < height; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void terminate(GameInfo_t *game) {
  free_matrix(game->field, FIELD_HEIGHT + 1);
  free_matrix(game->next, 4);
  free(game);
}
