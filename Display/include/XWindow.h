#ifndef __XWINDOW_H__
#define __XWINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  
  ~Xwindow();                              
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  void drawString(int x, int y, std::string msg);

  void drawString(int x, int y, std::string msg, int colour);

};

#endif
