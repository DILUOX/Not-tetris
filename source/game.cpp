#include "game.hpp"
#include <iostream>
#include <string>
#include <random>
using namespace genv;
using namespace std;

///jatekter fuggvenyei

void Jatek::indit(){
    elolenyek.erase(elolenyek.begin(),elolenyek.end());
    gameover=0;
    pontok=0;
    identitas* karoly=new kigyo(200,200);
    elolenyek.push_back(karoly);
}



int Jatek::futtatas(event eva){
    if(eva.type==ev_timer){
        ido++;
    }
    int melyikalmaaz=0;
    for(size_t i=0;i<elolenyek.size();i++){

        if(elolenyek[i]->identitast_futtat(eva)==-1){
            gameover=1;
            return -1;
        }

        if(i>0 &&
            ( elolenyek[0]->getpozi()._x- elolenyek[i]->getpozi()._x<=15 && elolenyek[0]->getpozi()._x- elolenyek[i]->getpozi()._x>=-15 ) &&
            ( elolenyek[0]->getpozi()._y - elolenyek[i]->getpozi()._y < 20 &&
            elolenyek[0]->getpozi()._y - elolenyek[i]->getpozi()._y>-30 ) )
            {

            melyikalmaaz=i;

            }

    }

    if(elolenyek.size()>1 && melyikalmaaz!=0){
        int a=elolenyek.size()-1;

        swap(elolenyek[melyikalmaaz],elolenyek[a]);
        elolenyek.pop_back();

        pontok++;
        elolenyek[0]->setparameter(1);
    }

    if((ido%10==0 && eva.type==ev_timer) || eva.keyname=="A" || ido==0){
        identitas* kaja=new alma();
        elolenyek.push_back(kaja);
    }
    return 1;


}

void faltexturarajz(int x, int y,int s){
    gout<<move_to(x,y)<<color(204,204,204)<<box(s,s);
    for(int i=0;i<10;i++){
        gout<<move_to(x,y+i*5)<<color(255,0,0)<<line_to(x+i*5,y);
    }
    for(int i=10;i>0;i--){
        gout<<move_to(x+i*5,y+s)<<color(255,0,0)<<line_to(x+s,y+i*5);
    }
}

void Jatek::rajzolas(){
    gout<<move_to(50,60)<<color(0,0,0)<<text("Pontok: "+to_string(pontok));
    for(int i=0;i<16;i++){
        if(i==0 || i+1==16){
            for(int j=0;j<12;j++){
                faltexturarajz(i*50,j*50,49);
            }
        }
        else{
            faltexturarajz(i*50,0,49);
            faltexturarajz(i*50,550,49);
        }
    }

    for(size_t i=0;i<elolenyek.size();i++){
        elolenyek[i]->kirajz();
    }

}

int Jatek::vereseg(){
    if(gameover){
        kep jatekvegekep("gameover.kep");
        gout<<move_to(0,0)<<color(0,0,0)<<box(800,600);
        jatekvegekep.rajz(1,1);
        gout<<move_to(340,370)<<color(255,255,255)<<text("PONTJAID: "+to_string(pontok));
        return -1;
    }
    else return 0;
}


void identitas::kirajz()const{}


void identitas::getio(event evnt){
    ev=evnt;

}

int identitas::identitast_futtat(event e){return 0;}

pozi identitas::getpozi(){pozi pozicio;pozicio._x=0;pozicio._y=0; return pozicio;}

void identitas::setparameter(int parameter){}

void kigyo::setparameter(int parameter){
    novekszik();
}
void alma::setparameter(int parameter){};



/// A kigyo identitas fuggvenyei

void kigyo::kirajz()const{
    int kx=0,ky=0;


    for(int i=kanyarok.size()-1; i!=-1;i--){     // a kigoy kirajzolasa a kigyo "farkatol" indul, hogy minden esetben a fej is ki legyen rajzolva
            kx=kanyarok[i]->jelenlegi_x;
            ky=kanyarok[i]->jelenlegi_y;

            gout<<move_to(kx,ky)<<color(0,0,0)<<box(30,30)<<move_to(kx+3,ky+3)<<color(0,255,0)<<box(24,24);

            if(i==0){
                gout<<move_to(kx+10,ky+10)<<color(255,0,0)<<box(3,3)<<move_to(kx+20,ky+10)<<box(3,3);
            }
            if(i+1==kanyarok.size()){
                for(int i=0;i<6;i++){
                    gout<<move_to(kx+i*5,ky)<<color(0,0,0)<<box(3,30);
                }

            }
    }
}

void kigyo::novekszik(){
    kanyar * k=new kanyar(kanyarok[hossz-1]->jelenlegi_x,kanyarok[hossz-1]->jelenlegi_y);
    kanyarok.push_back(k);
    hossz++;

}

pozi kigyo::getpozi(){
    pozi peter;
    peter._x=kanyarok[0]->jelenlegi_x;
    peter._y=kanyarok[0]->jelenlegi_y;
    return peter;
}

void kigyo::billentyukezeles(){
    if(ev.type==ev_key)
    {
        if(ev.keyname=="Down" && fejirany!=-2)  //lefele mozgatas
        {
            fejirany=2;
        }
        if(ev.keyname=="Up" && fejirany!=2){  //lefele mozgatas
            fejirany=-2;
        }
        if(ev.keyname=="Left" && fejirany!=1)
        {
            fejirany=-1;
        }
        if(ev.keyname=="Right" && fejirany!=-1)
        {
            fejirany=1;
        }
    }
}

int iranyertek(int irany){
    if(irany<0){
        return -30;
    }
    else{
        return 30;
    }
}

void kigyo::iranyvaltas(kanyar * kanyar_1, kanyar * kanyar_2)
{
    kanyar_2->elozo_x=kanyar_1->jelenlegi_x;  // iranyvaltasok beallitasa ezekben a sorokban tortenik
    kanyar_2->elozo_y=kanyar_1->jelenlegi_y;
}


void kigyo::koordinatamozgatas(int i)
{
    //ha a "kanyarodopont" igaz, a kigyo a kanyarodas szerinti koordinatakat
    //hasznalja fel a "kanyarok" vectorbol, ha ez hamis, akkor a megszokott,
    //adott irany szerinti  folytonos mozgatast vegzi

    if(i==0){
        if(fejirany==1 || fejirany==-1 ){
            kanyarok[0]->jelenlegi_x+=iranyertek(fejirany);
        }
        else{
            kanyarok[0]->jelenlegi_y+=iranyertek(fejirany);
        }
    }
    else{
            kanyarok[i]->jelenlegi_x=kanyarok[i]->elozo_x;
            kanyarok[i]->jelenlegi_y=kanyarok[i]->elozo_y;
    }

}



void kigyo::mozog()             //mozgatas fuggvenye a teljesseg igenye nelkul
{
    billentyukezeles();
    if(ev.type==ev_timer)
    {
        for(size_t i=0;i<kanyarok.size();i++){
                koordinatamozgatas(i);
        }

        for(size_t j=0;j<kanyarok.size()-1;j++){
            iranyvaltas(kanyarok[j],kanyarok[j+1]);
        }
    }
}


bool kigyo::meghal(){
    int jx=kanyarok[0]->jelenlegi_x;
    int jy=kanyarok[0]->jelenlegi_y;
    bool meghalas=(50>jx || jx>720 || 50>jy || jy>530);
    for(size_t i=3;i<kanyarok.size() && !meghalas;i++){

        if(jx==kanyarok[i]->jelenlegi_x && jy==kanyarok[i]->jelenlegi_y){
            meghalas=1;
        }
    }
    return meghalas;
}


int kigyo::identitast_futtat(event e){
    getio(e);
    if(!eletben)
    {
        for(size_t i=1;i<kanyarok.size();i++){
            kanyarok[i]->jelenlegi_x=kanyarok[i]->elozo_x=kanyarok[i]->elozo_x+30;
            kanyarok[i]->jelenlegi_y=kanyarok[i]->elozo_y=kanyarok[i]->elozo_y;
        }
        eletben=true;
    }
    mozog();
    if(meghal()){
        eletben=0;
    }
    if(eletben){
        return 1;
    }
    else{
        return -1;
    }
}



///gyumolcsok fuggvenyei

void alma::kirajz()const{
    gout<<move_to(almapozi._x,almapozi._y)<<color(255,0,0)<<box(14,20)<<move_to(almapozi._x+7,almapozi._y)
    <<color(0,255,0)<<line(-5,-4)<<move_to(almapozi._x+7,almapozi._y)<<line(5,-4);
}

int alma::identitast_futtat(event eva){
    return 0;
}


pozi alma::getpozi(){
    return almapozi;
}







