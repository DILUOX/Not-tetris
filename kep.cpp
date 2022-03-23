#include "kep.hpp"

using namespace genv;
void kep::rajz(int rajz_helye_x, int rajz_helye_y)const{

    for(size_t i=0; i<keppontok.size(); i++)
        {
            gout<<move_to(rajz_helye_x+keppontok[i].x-4,rajz_helye_y+keppontok[i].y+3)
                <<color(keppontok[i].r,keppontok[i].g,keppontok[i].b)<<dot;
        }
}
