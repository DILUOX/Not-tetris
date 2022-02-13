#include "graphics.hpp"
#include "menu.hpp"
#include "tetris.hpp"
#include <vector>
#include <cstdlib>
#include <string>

using namespace genv;
using namespace std;

const int wx=500;
const int wy=700;



string cuttitles(string& title)   //Adott meretu szoveget darabol szet ";" jelek alapjan
{
    string btittle="";
    btittle=title.substr(0,title.find(';'));
    title=title.substr(title.find(';')+1,title.length());
    return btittle;
}


void generate_buttons(menu* m,int db,string& titles){           //tettszoleges mennyisegu gombot general; a gombok nevet egymas utan ';' jellel elvalasztva kell megadni.
                                                                //Ha nem adsz meg annyi nevet, ahany gombod van, akkor automatikusan a legutolso megadott nev fog a gombokon szerepelni
    for(int j=0;j<db;j++){
         button* jatek= new button(1,wx/3+25,wy/4+j*55,0,0,cuttitles(titles));
         m->give_object(jatek);
    }
}


void run(menu* m){          //maga a teljes jatek

    string buttonnames="Új játék;Kilépés";
    generate_buttons(m,2,buttonnames);
    event e;
    m->start_application();


    bool gamerun=0;
    while(e.keycode!=key_f12){
        gin>>e;
        if(m->run_(e)==-1){             //-1 a "jatek" gomb visszateresi erteke
            torol(wx,wy);
            gamerun=1;
        }
        if(e.keycode==key_escape && gamerun){           //a futo jatekbol az esc billentyuvel lehet kilepni
            buttonnames="Folytatás;Új játék;Kilépés";
            generate_buttons(m,3,buttonnames);
            gamerun=0;
        }

        gout<<refresh;
    }
    delete m;
}

int main()
{
    menu* main_menu= new menu(wx,wy);
    run(main_menu);
    return 0;
}
