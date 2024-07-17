#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 22;

int TRANSFORM_RATE = 2;

// refresh every 250 milliseconds (4 fps)
int FRAME_TIME = 250;

char* DEFAULT_FG_COLOUR = "0";

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

long long current_time_millisecond() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    return te.tv_sec*1000LL + te.tv_usec/1000;
}

int
run(Object *object)
{
  // TODO: do draw
  long long ts = current_time_millisecond();
  long long ts_diff = 0;

  while(1)
  {
    Transform transform = object->transform;
    switch (transform.direction) {
      // Right
      case 1:
        int new_end_x = object->end_x + TRANSFORM_RATE;
        if (new_end_x <= SCREEN_WIDTH + TRANSFORM_RATE)
        {
          object->start_x = object->start_x + TRANSFORM_RATE;
          object->end_x = new_end_x;
        } else {
          object->transform.direction = UP;
        }
        break;
      // Left
      case 2:
        int new_start_x = object->end_x - TRANSFORM_RATE;
        if (new_start_x >= 0)
        {
          object->start_x = new_start_x;
          object->end_x = object->end_x - TRANSFORM_RATE;
        } else {
          object->transform.direction = DOWN;
        }
        break;
      // Up
      case 3:
        int new_start_y = object->start_y - TRANSFORM_RATE;
        if (new_start_y >= 0)
        {
          object->start_y = new_start_y;
          object->end_y = object->end_y - TRANSFORM_RATE;
        } else {
          object->transform.direction = LEFT;
        }
        break;
      // Down
      case 4:
        int new_end_y = object->end_y + TRANSFORM_RATE;
        if (new_end_y <= SCREEN_HEIGHT)
        {
          object->start_y = object->start_y + TRANSFORM_RATE;
          object->end_y = new_end_y;
        } else {
          object->transform.direction = RIGHT;
        }
        break;
    }
  }
  return 0;
}

int
main()
{
  Object object = {  
    .start_x = 30,
    .start_y = 5,
    .end_x = 70,
    .end_y = 10
  };
  object.transform.direction = RIGHT;
  return run(&object);
}

