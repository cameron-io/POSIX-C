#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Window Window;
typedef struct Transform Transform;

struct Window
{
  int start_x;
  int end_x;
  int start_y;
  int end_y;
};

struct Transform
{
  char* direction;
};

long long current_time_millisecond() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    return te.tv_sec*1000LL + te.tv_usec/1000;
}

int
do_run(Window window, Transform transform)
{
  // TODO: do draw
  long long ts = current_time_millisecond();
  long long ts_diff = 0;
  return 0;
}

int
run(Window window)
{
  Transform transform = {.direction = "right"};
  return do_run(window, transform);
}

int
main()
{
  Window window = {  
    .start_x = 30,
    .start_y = 5,
    .end_x = 70,
    .end_y = 10
  };
  return run(window);
}

