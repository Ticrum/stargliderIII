
#include <starglider.h>

void respawn_enemy(t_enemy  *enemy,
                   int      len,
                   int      *score)
{
    int compt3;
    int compt;
    int compt2;
    t_pos posi;

    srand(time(NULL));
    compt3 = 0;
    while (compt3 < len)
    {
        if (enemy[compt3].hp <= 0)
        {
            *score = *score + 10;
            enemy[compt3].hp = enemy[compt3].maxhp;
            posi.x = rand() % 1600 - 800;
            posi.y = rand() % 1600 - 800;
            posi.z = rand() % 1600 - 800;
            enemy[compt3].obj.position.x = enemy[compt3].obj.position.x + posi.x;
            enemy[compt3].obj.position.y = enemy[compt3].obj.position.y + posi.y;
            enemy[compt3].obj.position.z = enemy[compt3].obj.position.z + posi.z;
            enemy[compt3].vect.x = enemy[compt3].vect.x + posi.x;
            enemy[compt3].vect.y = enemy[compt3].vect.y + posi.y;
            enemy[compt3].vect.z = enemy[compt3].vect.z + posi.z;
            compt = 0;
            compt2 = 0;
            while (compt != enemy[compt3].obj.nbr_subelems)
            {
                enemy[compt3].obj.pos[compt2].x = enemy[compt3].obj.pos[compt2].x + posi.x;
                enemy[compt3].obj.pos[compt2].y = enemy[compt3].obj.pos[compt2].y + posi.y;
                enemy[compt3].obj.pos[compt2].z = enemy[compt3].obj.pos[compt2].z + posi.z;
                enemy[compt3].obj.pos[compt2 + 1].x = enemy[compt3].obj.pos[compt2 + 1].x + posi.x;
                enemy[compt3].obj.pos[compt2 + 1].y = enemy[compt3].obj.pos[compt2 + 1].y + posi.y;
                enemy[compt3].obj.pos[compt2 + 1].z = enemy[compt3].obj.pos[compt2 + 1].z + posi.z;
                enemy[compt3].obj.pos[compt2 + 2].x = enemy[compt3].obj.pos[compt2 + 2].x + posi.x;
                enemy[compt3].obj.pos[compt2 + 2].y = enemy[compt3].obj.pos[compt2 + 2].y + posi.y;
                enemy[compt3].obj.pos[compt2 + 2].z = enemy[compt3].obj.pos[compt2 + 2].z + posi.z;
                compt = compt + 1;
                compt2 = compt2 + 3;
            }
        }
        compt3 = compt3 + 1;
    }
}

