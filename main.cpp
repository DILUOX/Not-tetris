#include "graphics.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <vector>
#include <cstdlib>
#include <string>

using namespace genv;
using namespace std;

const int wx=800;
const int wy=600;


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
         button* jatek= new button(600,wy-270+j*55,cuttitles(titles));
         m->give_object(jatek);
    }
}


void run(menu* m,Jatek* kigyokaroly)           //maga a teljes jatek
{

    string buttonnames="Új játék;Kilépés";
    generate_buttons(m,2,buttonnames);
    event ev;
    m->start_application();
    kigyokaroly->indit();



    bool gamerun=0;
    gin.timer(500);
    while(ev.keycode!=key_escape)
    {
        gin>>ev;
        if(!gamerun)
        {
            torol(wx,wy,0,0,255);
            if(m->run_(ev)==-1)              //-1 a "jatek"/folytatas gomb visszateresi erteke
            {
                gamerun=1;
                torol(wx,wy,0,0,0);                   //elindul a jatek
            }
            if(kigyokaroly->vereseg()==-1 && ev.keyname=="F1"){
                buttonnames="Új játék;Kilépés";
                generate_buttons(m,2,buttonnames);
                kigyokaroly->indit();
            }

        }
        if(gamerun)
        {
            if(kigyokaroly->futtatas(ev)==-1){
                gamerun=0;
            }

            if(ev.type==ev_timer){
                torol(wx,wy,203 , 140, 111);
                kigyokaroly->rajzolas();
            }

            if(ev.keyname=="F1"){
                buttonnames="Folytatás;Kilépés"; //a futo jatekbol az esc billentyuvel lehet kilepni
                generate_buttons(m,2,buttonnames);
                gamerun=0;

            }
        }


        gout<<refresh;
    }

}



int main()
{
    menu* main_menu= new menu(wx,wy,"Kígyó károly");
    Jatek* not_tetris=new Jatek(wx,wy);
    run(main_menu,not_tetris);
    delete main_menu;
    delete not_tetris;
    return 0;
}
