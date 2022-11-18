#ifndef FL_EXT_HPP
#define FL_EXT_HPP

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Button.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Multiline_Input.H>

#include <functional>
#include <iostream>

inline float dpi_scale = 1.5f;
#define sdpi(pixel) static_cast<int>(dpi_scale * pixel)

using Flcb = std::function<void(Fl_Widget* widget)>;
inline void flcb_bridge(Fl_Widget* widget, void* func_ptr)
{
    (*static_cast<Flcb*>(func_ptr))(widget);
}

inline Fl_Color fl_hex_color(int hex_color)
{
    int r = hex_color / 0x10000;
    int g = ((hex_color / 0x100) % 0x100);
    int b = hex_color % 0x100;
    return fl_rgb_color(r, g, b);
}

namespace
{
    inline void ext_btn_up_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0xE1E1E1));
        fl_rectf(x, y, w, h);
        fl_color(fl_hex_color(0xADADAD));
        fl_rect(x, y, w, h);
    }

    inline void ext_btn_down_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0xCCE4F7));
        fl_rectf(x, y, w, h);
        fl_color(fl_hex_color(0x005499));
        fl_rect(x, y, w, h);
    }

    inline void ext_btn_hover_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0xE5F1FB));
        fl_rectf(x, y, w, h);
        fl_color(fl_hex_color(0x0078D7));
        fl_rect(x, y, w, h);
    }

    inline void ext_frame_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0x7A7A7A));
        fl_rect(x, y, w, h);
    }

    inline void ext_input_idle_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0xFFFFFF));
        fl_rectf(x, y, w, h);
        fl_color(fl_hex_color(0x7A7A7A));
        fl_rect(x, y, w, h);
    }

    inline void ext_input_active_box(int x, int y, int w, int h, Fl_Color c)
    {
        fl_color(fl_hex_color(0xFFFFFF));
        fl_rectf(x, y, w, h);
        fl_color(fl_hex_color(0x0078D7));
        fl_rect(x, y, w, h);
    }

}; // namespace

inline Fl_Boxtype ext_box(int index)
{
#ifndef NO_BOX_EXT
    return static_cast<Fl_Boxtype>(FL_FREE_BOXTYPE + index);
#else
    return static_cast<Fl_Boxtype>(index);
#endif
}

inline const int box_count = 6;
enum Ext_Box
{
    BTN_UP_BOX = 0,
    BTN_DOWN_BOX,
    BTN_HOVER_BOX,
    BTN_FRAME_BOX,
    INPUT_IDLE_BOX,
    INPUT_ACTIVE_BOX
};

#ifndef NO_BOX_EXT
class Initializer
{
  public:
    inline Initializer()
    {
        Fl::set_boxtype(ext_box(BTN_UP_BOX), ext_btn_up_box, 0, 0, 0, 0);
        Fl::set_boxtype(ext_box(BTN_DOWN_BOX), ext_btn_down_box, 0, 0, 0, 0);
        Fl::set_boxtype(ext_box(BTN_HOVER_BOX), ext_btn_hover_box, 0, 0, 0, 0);
        Fl::set_boxtype(ext_box(BTN_FRAME_BOX), ext_frame_box, 0, 0, 0, 0);
        Fl::set_boxtype(ext_box(INPUT_IDLE_BOX), ext_input_idle_box, 0, 0, 0, 0);
        Fl::set_boxtype(ext_box(INPUT_ACTIVE_BOX), ext_input_active_box, 0, 0, 0, 0);
    }
};
inline static Initializer initializer;
#endif

// widget extensions
template <typename Wd_B> //
class Fl_Ext_Attrib
{
  protected:
    Wd_B* widget_ = nullptr;

    Fl_Boxtype normal_box_;
    Flcb* flcb_func_ = nullptr;

  public:
    inline Fl_Ext_Attrib(Wd_B* widget) //
        : widget_(widget)
    {
    }

    inline Fl_Ext_Attrib(Wd_B& widget) //
        : widget_(&widget)
    {
    }

    // pointer to the widget itself
    operator Wd_B&()
    {
        return *widget_;
    }

    operator Wd_B*()
    {
        return widget_;
    }

    inline void push()
    {
        callback(flcb_func_);
        normal_box(normal_box_);
    }

    inline void pull()
    {
        flcb_func_ = static_cast<Flcb*>(widget_->user_data());
    }

    Wd_B& widget_base()
    {
        return *this;
    }

    inline bool operator==(Fl_Ext_Attrib<Wd_B>& target)
    {
        if (target.widget_ != widget_)
        {
            return false;
        }
        else if (target.normal_box_ != normal_box_)
        {
            return false;
        }
        else if (target.flcb_func_ != flcb_func_)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // box attrib extention
    inline void normal_box(Fl_Boxtype new_box)
    {
        normal_box_ = new_box;
        widget_->box(normal_box_);
    }

    inline Fl_Boxtype normal_box() const
    {
        return normal_box_;
    }

    // color attrib extention
    inline void color(int a)
    {
        widget_->color(fl_hex_color(a));
    }

    inline void color(int r, int g, int b)
    {
        widget_->color(fl_rgb_color(r, g, b));
    }

    inline void selection_color(int a)
    {
        widget_->selection_color(fl_hex_color(a));
    }

    inline void selection_color(int r, int g, int b)
    {
        widget_->selection_color(fl_rgb_color(r, g, b));
    }

    inline void labelcolor(int a)
    {
        widget_->labelcolor(fl_hex_color(a));
    }

    inline void labelcolor(int r, int g, int b)
    {
        widget_->labelcolor(fl_rgb_color(r, g, b));
    }

    // callback extension
    inline void callback(Flcb* cb)
    {
        flcb_func_ = cb;
        widget_->callback(flcb_bridge, flcb_func_);
    }

    inline void callback(Flcb& cb)
    {
        flcb_func_ = &cb;
        widget_->callback(flcb_bridge, flcb_func_);
    }

    inline Flcb* callback() const
    {
        return flcb_func_;
    }
};

template <typename Wd_T> //
class Fl_Ext : public Wd_T
{
  public:
    Fl_Ext_Attrib<Wd_T> ext;

    inline Fl_Ext(int X, int Y, int W, int H, const char* L = 0) //
        : Wd_T(X, Y, W, H, L),                                   //
          ext(this)
    {
    }
};

// button extensions
template <typename Btn_B> //
class Fl_Btn_Ext_Attrib : public Fl_Ext_Attrib<Btn_B>
{
  protected:
    Fl_Boxtype hover_box_;
    Fl_Boxtype click_box_;

  public:
    inline Fl_Btn_Ext_Attrib(Btn_B* button) //
        : Fl_Ext_Attrib<Btn_B>(button)
    {
        this->widget_->box(ext_box(BTN_UP_BOX));
        this->widget_->down_box(ext_box(BTN_DOWN_BOX));

        this->normal_box_ = ext_box(BTN_UP_BOX);
        click_box_ = ext_box(BTN_DOWN_BOX);
        hover_box_ = ext_box(BTN_HOVER_BOX);
    }

    inline Fl_Boxtype hover_box() const
    {
        return hover_box_;
    }

    inline void hover_box(Fl_Boxtype new_box)
    {
        hover_box_ = new_box;
    }

    inline void click_box(Fl_Boxtype new_box)
    {
        this->widget_->down_box(click_box_);
        click_box_ = new_box;
    }

    inline Fl_Boxtype click_box() const
    {
        return click_box_;
    }
};

template <typename Btn_T> //
class Fl_Btn_Ext : public Btn_T
{
  public:
    Fl_Btn_Ext_Attrib<Btn_T> ext;

    inline Fl_Btn_Ext(int X, int Y, int W, int H, const char* L = 0) //
        : Btn_T(X, Y, W, H, L),                                      //
          ext(this)
    {
    }
};

template <> // special effect for normal button
class Fl_Btn_Ext<Fl_Button> : public Fl_Button
{
  public:
    Fl_Btn_Ext_Attrib<Fl_Button> ext;

    inline Fl_Btn_Ext(int X, int Y, int W, int H, const char* L = 0) //
        : Fl_Button(X, Y, W, H, L),                                  //
          ext(this)
    {
    }

    int handle(int event)
    {
        int result = Fl_Button::handle(event);

        switch (event)
        {
            case FL_ENTER:
            {
                box(ext.hover_box());
                redraw();
                break;
            }
            case FL_LEAVE:
            {
                box(ext.normal_box());
                redraw();
                break;
            }
            case FL_DRAG:
            {
                box(ext.normal_box());
                redraw();
                break;
            }
        }

        return result;
    }
};

// input extensions
class Fl_Input_Ext : public Fl_Input
{
  private:
    Flcb* flcb_func_ = nullptr;
    Fl_Boxtype active_box_;
    Fl_Boxtype prev_box_;

  public:
    Fl_Input_Ext(int X, int Y, int W, int H, const char* L = 0) //
        : Fl_Input(X, Y, W, H, L)
    {
        box(ext_box(INPUT_IDLE_BOX));
        active_box(ext_box(INPUT_ACTIVE_BOX));
        selection_color(fl_hex_color(0x0078D7));
    }

    Fl_Input_Ext& father()
    {
        return *this;
    }

    Fl_Input_Ext* father_ptr()
    {
        return this;
    }

    inline Fl_Boxtype active_box() const
    {
        return active_box_;
    }

    inline void active_box(Fl_Boxtype new_box)
    {
        active_box_ = new_box;
    }

    inline int handle(int event)
    {
        switch (event)
        {
            case FL_FOCUS:
            {
                prev_box_ = box();
                box(active_box_);
                redraw();
                break;
            }
            case FL_UNFOCUS:
            {
                box(prev_box_);
                redraw();
                break;
            }
        }
        return Fl_Input::handle(event);
    }

    void callback(Flcb* cb)
    {
        flcb_func_ = cb;
        Fl_Input::callback(flcb_bridge, flcb_func_);
    }

    Flcb* callback()
    {
        return flcb_func_;
    }
};

#endif // FL_EXT_HPP
