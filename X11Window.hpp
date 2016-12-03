#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <X11/Xlib.h>
class X11Display;

class X11Window {
friend class X11Display;

public:
    X11Window(X11Display* d, Window& w);
    ~X11Window();

    static X11Window CreateSimpleWindow(X11Display* d, int width, int height);

    Window window;
    X11Display* display;
};

#endif