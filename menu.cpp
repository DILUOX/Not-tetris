#include "menu.hpp"
#include <iostream>
#include <string>


void parent_app::give_object(object * b)
{
    objects.push_back(b);
}

setting* parent_app::get_settings(){
    return settings;
}


void parent_app::start_application(){}

int parent_app::run_(){return true;}

void menu::start_application()
{
    genv::gout.open(wsizex,wsizey);
    if(objects.size()==0)
    {
        textbox* error= new textbox(130,50,"Hiba az alkalmaz�s indit�sakor",244,0,0);
        give_object(error);
        button* kilepes= new button(1,wsizex/2-40,120,0,0,"Kil�p�s");
        give_object(kilepes);

    }

}



int menu::run_(genv::event e){
    int btn_val=0;
    for(size_t i=0; i<objects.size();i++)
    {
        objects[i]->getinput(e);
        objects[i]->ofunction();
        btn_val=objects[i]->return_value();

        if(btn_val && i==0){
            i=objects.size();
            objects.erase(objects.begin(),objects.end());
            return -1;
        }

        if(btn_val && i==objects.size()-1){
                exit(0);
        }


    }
    return true;
}
