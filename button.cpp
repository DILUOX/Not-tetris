#include "button.hpp"
#include <iostream>


void object::ofunction(){draw();}
void object::draw()const{};
int object::return_value(){return 0;};

void object::getinput(genv::event ev){
    e=ev;
}

void object::centering(std::string text)const{
    genv::gout<<genv::move_to(x+sx/2-genv::gout.twidth(text)/2,y+(sy/2+genv::gout.cascent()/2));        //kozepre igazitja a rajzpontot szovegirashoz
}

void  torol(const int x, const int y){
     genv::gout<<genv::move_to(0,0)<<genv::color(0,0,0)<<genv::box(x,y);    //kepernyotorles; mozgatashoz ajanlott
}

bool button::isklicked(){
    return e.pos_x>x && e.pos_y > y && e.pos_x< x+sx && e.pos_y < y+sy;     //ha a kurzor az objektumon van, igaz erteket ad vissza
}

void button::draw()const {
   genv::gout<<genv::move_to(x,y)<<genv::color(r,g,b)<<genv::box(sx,sy);    //gombrajzolas
   centering(title);
   genv::gout<<genv::color(0,0,0)<<genv::text(title);       //szoveg
}


void button::ofunction(){
    if(isklicked()){
        r=200;
    }
    else{
        r=244;
    }
    draw();
}

int button::return_value(){
    return isklicked() && e.button==genv::btn_left;

}

void textbox::draw(){
    genv::gout<<genv::move_to(x,y)<<genv::color(r,g,b)<<genv::box(sx,sy);
    centering(title);
    genv::gout<<genv::color(0,0,0)<<genv::text(title);
}



