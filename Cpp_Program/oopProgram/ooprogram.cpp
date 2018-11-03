#include <iostream>
#include <string>
#include "ooprogram.h"

using namespace std;

int main(){
  Bulk_quote bqu;
  Quote item(bqu);
  item = bqu;
  Quote *p = &item; // p指向Quote对象
  p = &bqu;
  Quote &r = bqu;

  return 0;
}
