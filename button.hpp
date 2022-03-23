#ifndef button_hpp
#define button_hpp
#include "graphics.hpp"

class object
{
protected:
    int x,y,sx,sy;
    genv::event e;


public:
    void centering(std::string text)const;
    void getinput(genv::event e);
    virtual ~object(){
        delete this;
    }

    virtual void draw()const;
    virtual void ofunction();
    virtual int return_value();

};


class button : public object
{
protected:
    std::string title;
    bool value;
    int r,g,b;

public:
    button(int _x, int _y, int _sx,int _sy,std::string _title)
    {
        x=_x;   sx=_sx;    title=_title;
        y=_y;   sy=_sy;
        r=244;b=244;g=244;
        value=0;
    }

    button(int _x, int _y,std::string _title){
        x=_x;   y=_y;
        title=_title;
        sx=100; sy=35;
        r=244;b=244;g=244;
        value=0;
    }

    ~button(){}

    bool isklicked();
    virtual void draw()const;
    virtual void ofunction();
    virtual int return_value();

};

struct textbox : public object{
protected:
    std::string title;
    int r,g,b;
    bool centered;
public:
    textbox(int _x, int _y,std::string _title,int _r,int _g,int _b){
        x=_x;   sx=genv::gout.twidth(_title)+30;    title=_title;
        y=_y;   sy=50;  r=_r;   g=_g;   b=_b;
        centered=true;
    }
    textbox(int _x, int _y,std::string _title, int _r, int _g, int _b, bool centering){
        x=_x;   sx=genv::gout.twidth(_title)+30;    title=_title;
        y=_y;   sy=50;  r=_r;   g=_g;   b=_b; centered=centering;
    }
    textbox(int _r, int _g, int _b, int _x, int _y,int sx_, int sy_){
        x=_x;y=_y;
        sx=sx_; sy=sy_;
        r=_r;g=_g;b=_b;
        title="notitle";
    }
    virtual void draw();
};

void torol(const int x, const int y,const int r, const int g, const int b);


#endif // button_hpp
