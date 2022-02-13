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
    virtual ~object()=default;

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
    button(bool default_,int _x, int _y, int _sx,int _sy,std::string _title)
    {
        if(!default_)
        {
        x=_x;   sx=_sx;    title=_title;
        y=_y;   sy=_sy;
        }

        else{
            x=_x;   y=_y;   title=_title;
            sx=100; sy=35;
        }
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
public:
    textbox(int _x, int _y,std::string _title,int _r,int _g,int _b){
        x=_x;   sx=genv::gout.twidth(_title)+30;    title=_title;
        y=_y;   sy=50;  r=_r;   g=_g;   b=_b;
    }
    virtual void draw();
};

void torol(const int x, const int y );


#endif // button_hpp
