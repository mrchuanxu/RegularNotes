#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include "screen.h"
#include <iostream>
#include <vector>
using namespace std;
class Screen; // 低级错误！！！

class Window_mgr
{
public:
  using ScreenIndex = vector<Screen>::size_type;
  ScreenIndex addScreen(const Screen&);
  inline void clear(ScreenIndex);
private:
  vector<Screen> screens;
};

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s){
  screens.push_back(s);
  return screens.size() - 1;
}
// void Window_mgr::clear(ScreenIndex i)
// {
//   Screen &s = screens[i];
//   s.contents = string(s.height * s.width, ' ');
// }

#endif
