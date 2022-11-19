#include "Fl_Ext.hpp"

// button extensions
template <typename Btn_B> //
class Fl_Btn_Ext_Attrib : public Fl_Ext_Attrib<Btn_B>
{
  public:
    inline Fl_Btn_Ext_Attrib(Btn_B* button);
    inline Fl_Btn_Ext_Attrib(Btn_B& button);

    inline Fl_Boxtype click_box() const;
    inline void click_box(Fl_Boxtype new_box);
};

template <typename Btn_T> //
class Fl_Btn_Ext : public Fl_Ext<Btn_T>
{
  private:
    Fl_Boxtype hover_box_;
    Fl_Boxtype normal_box_;
    Fl_Boxtype click_box_;

  public:
    inline Fl_Btn_Ext(int X, int Y, int W, int H, const char* L = 0);

    inline Fl_Boxtype hover_box() const;
    inline void hover_box(Fl_Boxtype new_box);

    inline Fl_Boxtype click_box() const;
    inline void click_box(Fl_Boxtype new_box);

    inline Fl_Boxtype normal_box() const;
    inline void normal_box(Fl_Boxtype new_box);

    inline int handle(int event);
};

// Implementations

template <typename Btn_B>
inline Fl_Btn_Ext_Attrib<Btn_B>::Fl_Btn_Ext_Attrib(Btn_B* button) //
    : Fl_Ext_Attrib<Btn_B>(button)
{
}

template <typename Btn_B>
inline Fl_Btn_Ext_Attrib<Btn_B>::Fl_Btn_Ext_Attrib(Btn_B& button) //
    : Fl_Ext_Attrib<Btn_B>(button)
{
}

template <typename Btn_B>
inline Fl_Boxtype Fl_Btn_Ext_Attrib<Btn_B>::click_box() const
{
    return this->widget().down_box();
}

template <typename Btn_B>
inline void Fl_Btn_Ext_Attrib<Btn_B>::click_box(Fl_Boxtype new_box)
{
    this->widget().down_box(new_box);
}

//////////////////////////////Blank//////////////////////////////

template <typename Btn_T>
inline Fl_Btn_Ext<Btn_T>::Fl_Btn_Ext(int X, int Y, int W, int H, const char* L) //
    : Fl_Ext<Btn_T>(X, Y, W, H, L)                                              //
{
    hover_box_ = fl_ext_box(BTN_HOVER_BOX);
    normal_box(fl_ext_box(BTN_UP_BOX));
    click_box(fl_ext_box(BTN_DOWN_BOX));
}
template <typename Btn_T>
inline Fl_Boxtype Fl_Btn_Ext<Btn_T>::hover_box() const
{
    return hover_box_;
}

template <typename Btn_T>
inline void Fl_Btn_Ext<Btn_T>::hover_box(Fl_Boxtype new_box)
{
    hover_box_ = new_box;
}

template <typename Btn_T>
inline Fl_Boxtype Fl_Btn_Ext<Btn_T>::click_box() const
{
    return click_box_;
}

template <typename Btn_T>
inline void Fl_Btn_Ext<Btn_T>::click_box(Fl_Boxtype new_box)
{
    click_box_ = new_box;
    this->down_box(click_box_);
}

template <typename Btn_T>
inline Fl_Boxtype Fl_Btn_Ext<Btn_T>::normal_box() const
{
    return normal_box_;
}

template <typename Btn_T>
inline void Fl_Btn_Ext<Btn_T>::normal_box(Fl_Boxtype new_box)
{
    normal_box_ = new_box;
    this->box(normal_box_);
}

template <typename Btn_T>
inline int Fl_Btn_Ext<Btn_T>::handle(int event)
{
    int result = Fl_Button::handle(event);

    switch (event)
    {
        case FL_ENTER:
        {
            this->box(hover_box_);
            this->redraw();
            break;
        }
        case FL_LEAVE:
        {
            this->box(normal_box_);
            this->redraw();
            break;
        }
    }

    return result;
}
