#ifndef menu_hpp
#define menu_hpp
#include "button.hpp"
#include <vector>

struct setting{
    int difficulty;
};

class parent_app{

protected:
    int wsizex, wsizey;
    std::vector<object*> objects;
    setting* settings;

public:
    virtual ~parent_app(){
        objects.erase(objects.begin(),objects.end());
        delete this;
    };

    setting* get_settings();
    virtual void start_application()=0;
    virtual int run_();
        void give_object(object* b);
};


class menu : public parent_app{

protected:
    genv::event io;

public:
    menu(int wx, int wy){
        wsizex=wx; wsizey=wy;
    }

    virtual void start_application();
    virtual int run_(genv::event e);
};
#endif // menu_hpp
