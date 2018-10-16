#include <iostream>
#include "screen.h"
using namespace std;

int main(){
  Screen myScreen(5,3,' ');
  // char ch = myScreen.get();
  // ch = myScreen.get(0,0);
  // myScreen.move(5,3).set('#');
  const Screen blank(5,3,'*');
  myScreen.set('#').display(cout);
  blank.display(cout);
  return 0;
};
