#include "app.hpp"

#include "Fl_Ext.hpp"
#include "Fl_Hover_Ext.hpp"

#include <iostream>
#include <FL/Fl_Input.H>

#include "test.cpp"

fc::App::App(int W, int H, const char* title) //
    : Fl_Win_Ext<Fl_Double_Window>(sdpi(100), sdpi(100), sdpi(W), sdpi(H), title)
{
    Fl::visible_focus();
    init();
}

fc::App::~App()
{
    exit();
}

void fc::App::init()
{
    Fl_Hover_Ext<Fl_Input>* btn = new Fl_Hover_Ext<Fl_Input>(0, 0, 200, 200, "&Hello world");
    btn->hover_box(FL_FLAT_BOX);
    btn->normal_box(FL_UP_BOX);
    Fl_Button* btn2 = new Fl_Button(300, 300, 200, 200, "Hello world");

    static Flcb ccb = [](Fl_Widget* w) { std::cout << 111; };
    btn->attrib.callback(ccb);

    add(btn);
    add(btn2);
}

void fc::App::exit()
{
}

int fc::App::run(int argc, char** argv)
{
    show();
    return Fl::run();
}
