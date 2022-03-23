#include "button.hpp"
#include <iostream>


void object::ofunction(){draw();}
void object::draw()const{};

int object::return_value(){return 0;};

void object::getinput(genv::event ev){

    if(ev.pos_x!=0){
            e=ev;
    }
}

void object::centering(std::string text)const{
    genv::gout<<genv::move_to(x+sx/2-genv::gout.twidth(text)/2,y+(sy/2+genv::gout.cascent()/2));        //kozepre igazitja a rajzpontot szovegirashoz
}

void  torol(const int x, const int y,int r,const int g,const int b){
     genv::gout<<genv::move_to(0,0)<<genv::color(r,g,b)<<genv::box(x,y);    //kepernyotorles; mozgatashoz ajanlott
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
    if(isklicked() && value==0){
        value=1;
        r=255;
        g=204;
        b=0;

    }
    else if(value==1 && !isklicked()){
        r=200;
        g=244;
        b=244;
        value=0;
    }
    draw();
}

int button::return_value(){
    return isklicked() && e.button==genv::btn_left;

}

void textbox::draw(){
    genv::gout<<genv::move_to(x,y)<<genv::color(r,g,b)<<genv::box(sx,sy);
    if(centered){
            centering(title);
    }
    if(title!="notitle"){
        genv::gout<<genv::color(0,0,0)<<genv::text(title);
    }

}



