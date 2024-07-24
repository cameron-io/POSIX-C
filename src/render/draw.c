#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define SCREEN_WIDTH 155
#define SCREEN_HEIGHT 29

#define TRANSFORM_RATE 1

// refresh every 16 milliseconds (60 fps)
#define FRAME_TIME 16

#define DEFAULT_FG_COLOUR "0"

char* screen[SCREEN_HEIGHT][SCREEN_WIDTH]; 

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

char*
draw_object_detail(int x, int y, Object* object)
{
  if (x == object->start_x && y == object->start_y || // top-left
      x == object->end_x   && y == object->end_y   || // top-right
      x == object->start_x && y == object->end_y   || // bottom-left
      x == object->end_x   && y == object->end_y)     // bottom-right
  {
    return "+";
  } else if (x == object->start_x || x == object->end_x) {
    return "|";
  } else {
    return "0";
  }
}

char*
draw(Object *object)
{
  char* output;
  output = malloc(sizeof(char) * 16);
  
  int y = 0;
  while(y < SCREEN_HEIGHT)
  {
    int x = 0;
    while(x < SCREEN_WIDTH)
    {
      if (x > object->start_x && y > object->start_y && 
          x < object->end_x   && y < object->end_y)
      {
        char* enable_colour = "\033[42m";
        char* value = draw_object_detail(x, y, object);
        char* disable_colour = "\033[0m";
        strcpy(output, enable_colour);
        strcat(output, value);
        strcat(output, disable_colour);
        screen[y][x] = output;
      }
      else {
        screen[y][x] = " ";
      }
      x++;
    }
    y++;
  }
  return output;
}

void
clean_render_space()
{
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      screen[y][x] = NULL;
    }
  }
}

long long
current_time_millisecond() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    return te.tv_sec*1000LL + te.tv_usec/1000;
}

void
print_screen()
{
  for (int y = 0; y < SCREEN_HEIGHT; y++)
  {
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      printf("%s", screen[y][x]);
    }
    printf("\n");
  }
}

void
print_fps(int ts_diff)
{
  if (ts_diff > 0)
  {
    printf("%.2ffps\n", (double) 1000 / ts_diff);
  } else {
    printf("1000.00fps");
  }
}

void
clear_screen()
{
  printf("\033c");
}

void
refresh_screen(long long ts)
{
  long long new_ts = 0;
  while (FRAME_TIME >= (new_ts - ts))
  {
    new_ts = current_time_millisecond();
  }
  clear_screen();
}

int
run(Object *object)
{
  long long ts = current_time_millisecond();
  
  clean_render_space();

  while(1)
  {
    long long new_ts = current_time_millisecond();
    print_fps(new_ts - ts);
    ts = new_ts;

    char* new_render = draw(object);
    print_screen();
    refresh_screen(new_ts);
    free(new_render);
    
    switch (object->transform.direction) {
      // Right
      case 1:
        int new_end_x = object->end_x + TRANSFORM_RATE;
        if (new_end_x < SCREEN_WIDTH + TRANSFORM_RATE)
        {
          object->start_x = object->start_x + TRANSFORM_RATE;
          object->end_x = new_end_x;
        } else {
          object->transform.direction = UP;
        }
        break;
      // Left
      case 2:
        int new_start_x = object->start_x - TRANSFORM_RATE;
        if (new_start_x >= -1)
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
        if (new_start_y >= -1)
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
    .start_y = 6,
    .end_x = 70,
    .end_y = 10
  };
  object.transform.direction = RIGHT;
  return run(&object);
}

