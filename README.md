# `Fl_Ext` - a FLTK extension header only library
# The library is not feature compelete and just got started.

This library is design to work side by side and make no changes to FLTK itself. Therefore, Fl_Ext can be applied directly on existing project

## C++ 17 is Required
This library heavily uses inline functions and inline varialbes to ensure its header only nature. A c++17 compatible compiler is required to compile the program.

## Templates
`Fl_Ext` use lots of templates to make sure its extension-feature can be used on every `Fl_Widget` class. Also, I provide some extra classes that can work as "replacement" of vanilla FLTK widget. They work exactly like FLTK widgets, but with extra features.

## In short

### `Flcb` Callbacks
FLTK is too old to support full lambdas or funtors, and programing without it can be painful. Therefore, I provide a interface for using lambdas.
```cpp
using Flcb = std::function<void(Fl_Widget* widget)>;
```
All lambdas require the signature above. This little trick work by replacing `user_data` argument of `Fl_Widget::callback` with pointer to `Flcb` and `flcb_bridge(Fl_Widget* widget, void* func_ptr)` as the callback. YOU MUST MAKE SURE THAT LIFE TIME OF FUNCTOR IS LONGER THAN THE WIDGET ITSELF.

### `Fl_**_Ext_Attrib` Templates
Those templates are "Extension to FLTK", that is, all of them are stateless, fast and simple. The provide extra "Attribute" to vanilla FLTK widgets to make them easier to use and modern.

### Base Extension Attributes
```cpp
template <typename Wd_B>
class Fl_Ext_Attrib
{
    //.....
}
```
This is the base template for all Attributes, they are guarantee for working on every `Fl_Widget`.

To "extend" a widget, simply call the following function template 
```cpp
template <typename Wd_B>
Fl_Ext_Attrib<Wd_B> make_attrib(Wd_B widget);
```
This will return a copy of `Fl_Ext_Attrib<Wd_B>`. Manually create a instance is also allowed.
```cpp
// Example
Fl_Button* btn = new Fl_Button(0, 0, 100, 100, "Hello");

Fl_Ext_Attrib<Fl_Button> btn_attrib(btn);
// Or
auto btn_attrib2 = make_attrib(btn);
// Because Fl_Ext_Attrib is stateless, it doesn't matter how many Attribs are created for the same Widget

parent_widget.add(btn); // Add vanilla widget
parent_widget.add(btn_attrib); // Attrib can be used as Widget
parent_widget.add(btn_attrib2);
```

### `Fl_**_Ext` Templates
Those templates are "replacement" of vanilla widgets, unlike `Fl_**_Ext_Attrib`, `Fl_**_Ext` is the widget itself.

### Base Extension Widget
```cpp
template <typename Wd_T>
class Fl_Ext
{
    //.....
}
```
This is the bass template for all Extensions. It might provide lot more methods if special version of it is used. All of the Extension are not stateless and they are the widget itself. Therefore, except for the base Extension, other extension will only work on a specify child of `Fl_Widget`.

To create a "Extended Widget" simply create a template object
```cpp
// Example
Fl_Ext<Fl_Button>* ext_btn = new Fl_Ext<Fl_Button>(0, 0, 100,100, "Hello world");

ext_btn->active(); // Fl_Widget method
parent_widget.add(ext_btn);
```
Obtain `attrib` field to use Attribute methods. Special Extensions have extra methods can be used.
```cpp
// Example 2
Fl_Btn_Ext<Fl_Button>* ext_btn = new Fl_Ext<Fl_Button>(0, 0, 100,100, "Hello world"); // Fl_Button special extensions

Flcb* cb = ext_btn->attrib.callback(); // Attribute method
parent_widget.add(ext_btn);
```

## Extended Callback
`Fl_Ext_Attrib::callback(...)` is a elegant way to use functor in FLTK. 
```cpp
Fl_Button* btn = new Fl_Button(0, 0, 0, 0, "Hello");
auto btn_attrib = make_attrib(btn); // create a Attribute for btn
std::string world = "World";

// make a static functor to ensure life time
static Flcb btn_cb = [=](Fl_Widget* w) { std::cout << world; };
btn_attrib.callback(btn_cb);              // pass by reference
btn_attrib.callback(&btn_cb);             // pass by pointer
Flcb* btn_cb_ptr = btn_attrib.callback(); // can only return bypointer, basically Fl_Widget::user_data().
```
Notice that only Attributes provide a easy way to bind functor as callback. Vanilla widgets have to use `flcb_bridge(Fl_Widget* widget, void* func_ptr)` to bind functor.

Because Attributes are stateless, they does not store the functor itself, you have to pass functor as reference or pointer; rvalue or copy is not allowed.

## Extenede Colors
It is painful to use FLTK build in color. Therefore, I make an extension for it.
```cpp
class Fl_Ext_Color
{
    //.....
}
```
`Fl_Ext_Color` can be construct using rgb, hex and event FLTK's `Fl_Color`. It can be use as `Fl_Color` as well. `Fl_Ext_Color` is used for all Extentions and Attributes. If you devided to use this library, you should consider change all old `Fl_Color` specific code with this class.


