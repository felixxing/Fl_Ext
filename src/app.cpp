#include "app.hpp"

#include "Fl_Ext.hpp"
#include "Fl_Hover_Ext.hpp"

#include <iostream>
#include <FL/Fl_Input.H>

#include "test.cpp"

fc::App::App(int W, int H, const char* title) //
    : Fl_Win_Ext<Fl_Double_Window>(100, 100, W, H, title)
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
}

void fc::App::exit()
{
}

int fc::App::run(int argc, char** argv)
{
    show();
    return Fl::run();
}
