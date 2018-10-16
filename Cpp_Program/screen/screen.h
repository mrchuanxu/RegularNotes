#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <string>
#include <vector>
#include "window_mgr.h"

using namespace std;

class Screen{
  public:
      // typedef string::size_type pos;
      using ScreenIndex = std::vector<Screen>::size_type;
      friend class Window_mgr;
      friend void Window_mgr::clear(ScreenIndex);
      using pos = string::size_type;
      Screen() = default;
      Screen(pos hr,pos wd, char c):height(hr),width(wd),contents(hr*wd,c){}
      char get() const {
        return contents[cursor];
      }
      pos size() const;
      inline char get(pos hr,pos wd) const;
      Screen &move(pos r,pos c);
      Screen &set(char);
      Screen &set(pos,pos,char);
      void some_member() const;
      Screen &diplay(ostream &os){ do_display(os); return *this;}
      const Screen &display(ostream &os) const{ do_display(os); return *this;}
  private:
      void do_display(ostream &os) const { os << contents; }
      mutable size_t access_ctr;
      pos cursor = 0;
      pos height = 0, width = 0;
      string contents;
};

void Screen::some_member() const{
  ++access_ctr;
}

inline Screen &Screen::set(char c){
  contents[cursor] = c;
  return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch){
  contents[r*width+col] = ch;
  return *this;
}

inline Screen &Screen::move(pos r, pos c){
  pos row = r*width;
  cursor = row + c;
  return *this;
}

char Screen::get(pos r, pos c) const {
  pos row = r*width;
  return contents[row + c];
}
Screen::pos Screen::size() const{
  return height * width;
}
#endif
