# `Fl_Ext` - a FLTK extension header only library

This library is design to work side by side and work make any change to FLTK itself. Therefore, Fl_Ext can be applied directly on existing project without making big change to the codebase.

## C++ 17 is Required
This library heavily use inline functions and inline varialbe to ensure its header only nature. A c++17 compatible compiler is required to compile the program.

## Templates
`Fl_Ext` use lots of template to make sure its extension-feature can be used on every `Fl_Widget` class. Also, I provide some extra classes that can work as "replacement" of vanilla FLTK widgets. They work exactly like FLTK widgets, but with extra features.

## Documentations

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
This is the base template for all Attributes, it only provide few metohds and functions that can be used. Hoverer, they are also guarantee to work on all `Fl_Widget`.

To "extend" a widget, simply the following function template 
```cpp
template <typename Wd_B>
Fl_Ext_Attrib<Wd_B> make_ext(...);
```
This will return a copy of `Fl_Ext_Attrib<Wd_B>`. Or, manually create a instance is also allowed.

#### `Fl_**_Ext_Attrib` methods