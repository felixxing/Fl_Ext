#include "app.hpp"

#include "Fl_Ext.hpp"
#include "Fl_Btn_Ext.hpp"

#include <iostream>
#include <FL/Fl_Progress.H>

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
    Fl_Btn_Ext<Fl_Button>* btn = new Fl_Btn_Ext<Fl_Button>(0, 0, 0, 0, "Hello world");
    btn->hover_box(FL_FLAT_BOX);

    static Flcb ccb = [](Fl_Widget* w) { std::cout << 111; };
    btn->attrib.callback(ccb);

    rule(btn, "=<=^");
}

void fc::App::exit()
{
}

int fc::App::run(int argc, char** argv)
{
    show();
    return Fl::run();
}
