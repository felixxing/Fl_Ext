#include "app.hpp"

#include "fl_ext.hpp"

#include <iostream>
#include <FL/Fl_Progress.H>

#include "test.cpp"

fc::App::App(int W, int H, const char* title) //
    : Fl_Double_Window(sdpi(W), sdpi(H), title)
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
    end();

    main_flow_.end();
    main_flow_.resize(x(), y(), w(), h());
    add(main_flow_);
    resizable(main_flow_);

}

void fc::App::exit()
{
}

int fc::App::run(int argc, char** argv)
{
    show();
    return Fl::run();
}
