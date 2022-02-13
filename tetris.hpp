#ifndef     TETRIS_HPP
#define     TETRIS_HPP
#include "graphics.hpp"
#include "menu.hpp"

class game : public parent_app{
public:
    game(int _wx, int _wy){
        wsizex=_wx; wsizey=_wy;
        start_application();
    }

    virtual void start_application();
    virtual int run_();



};



#endif // tetris_hpp
