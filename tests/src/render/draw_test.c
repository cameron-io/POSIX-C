#include "lib/render/draw.h"

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
