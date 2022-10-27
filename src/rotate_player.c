
#include <starglider.h>

t_pos rotate_player(t_pos vect,
                    t_pos rota)
{
    rota.x = -rota.x;
    rota.y = -rota.y;
    rota.z = -rota.z;
    vect = stdrotation(vect, rota);
    return (vect);
}
