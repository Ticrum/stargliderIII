
#include <starglider.h>

t_pos add_pos(t_pos pos,
              t_pos up)
{
    pos.x = pos.x + up.x;
    pos.y = pos.y + up.y;
    pos.z = pos.z + up.z;
    return (pos);
}

