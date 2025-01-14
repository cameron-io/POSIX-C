#ifndef DRAW_H
#define DRAW_H

enum Direction {
  RIGHT = 1,
  LEFT  = 2,
  UP    = 3,
  DOWN  = 4
};

typedef struct
{
  enum Direction direction;
} Transform;

typedef struct
{
  int start_x;
  int end_x;
  int start_y;
  int end_y;
  Transform transform;
} Object;

int run(Object *object);

#endif