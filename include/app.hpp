#ifndef APP_HPP
#define APP_HPP

#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Double_Window.H>

#include "Fl_Win_Ext.hpp"

namespace fc
{
    class App : public Fl_Win_Ext<Fl_Double_Window>
    {
      private:

      public:
        App(int W, int H, const char* title = nullptr);
        ~App();

        void init();
        void exit();

        int run(int argc, char** argv);
    };

} // namespace fc

#endif // APP_HPP
