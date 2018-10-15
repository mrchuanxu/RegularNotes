#include <iostream>
#include "account.h"
#include <string>

int main(){
  Account ac1;
  Account *ac2 = &ac1;
  double r;
  r = ac1.rate();
  r = ac2->rate();
  r = Account::rate();
}
