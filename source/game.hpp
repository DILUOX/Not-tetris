#ifndef     GAME_HPP
#define     GAME_HPP
#include "graphics.hpp"
#include "kep.hpp"
#include <vector>
#include <random>
//#include <iostream>


struct pozi{
    int _x, _y;
};

class identitas{
public:
    virtual void kirajz()const;
    virtual int identitast_futtat(genv::event e);
    virtual pozi getpozi();

    virtual void setparameter(int parameter);
    void getio(genv::event evnt);
    virtual ~identitas()=default;

protected:                   // current_x current_y
    genv::event ev;
};

struct kanyar{
    int jelenlegi_y, jelenlegi_x;       //jelenlegi_*: a testresz aktualis helye kanyar_*: a testresz iranyvaltas eseten bekovetkezo uj helye
    int elozo_x, elozo_y;

    kanyar(int testresz_helye_x, int testresz_helye_y){
        jelenlegi_x=elozo_x=testresz_helye_x;
        jelenlegi_y=elozo_y=testresz_helye_y;
    }
};


class kigyo : public identitas{
public:
    kigyo(int spawn_x,int spawn_y){ //konstruktor
        for(int i=0;i<3;i++){
            kanyar* k=new kanyar(spawn_x-(i*30),spawn_y);
            kanyarok.push_back(k);
        }
        hossz=kanyarok.size();
        fejirany=1;
        eletben=1;
        start=0;
    }
    ~kigyo(){
        kanyarok.erase(kanyarok.begin(),kanyarok.end());
    }

    void billentyukezeles();
    pozi getpozi();
    void kirajz()const override;
    void mozog();

    void iranyvaltas(kanyar * kanyar_1, kanyar * kanyar_2);
    void koordinatamozgatas(int i);

    bool meghal();
    int identitast_futtat(genv::event e)override;

    void novekszik();
    void setparameter(int parameter)override;

protected:
    int hossz,fejirany;
    bool eletben,start;
    std::vector<kanyar*> kanyarok;

};

class alma : public identitas{
public:
    alma(){
        almapozi._x=(rand()%49) * 14 + 50 ;
        almapozi._y=(rand()%25) * 20 + 50 ;
    }
    void kirajz()const;
    int identitast_futtat(genv::event e)override;
    pozi getpozi();
    pozi setpozi();
    void setparameter(int paraneter)override;
protected:
    pozi almapozi;
};



class Jatek{
public:
    Jatek(const int wx, const int wy){
        nehezseg=1;
        ido=0;
        pontok=0;
        gameover=false;
    }
    ~Jatek(){
        elolenyek.erase(elolenyek.begin(),elolenyek.end());
    }
    void beallit(int _nehezseg);
    void indit();
    int futtatas(genv::event eva);
    void rajzolas();
    int vereseg();



private:
    genv::event e;
    int nehezseg,ido,pontok;
    bool gameover;
    std::vector<identitas*> elolenyek;


};


#endif // game_hpp
