#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string>

using namespace std;

typedef double Money;
string bal;
class Account{
  public:
    Account() = default;
    void calculate(){ amount+=amount * interestRate; }
    explicit Account(string owner,double amount):owner(owner),amount(amount){}
    static double rate(){ return interestRate; }
    static void rate(double);

  private:
    string owner;
    double amount;
    static double interestRate;
    static constexpr double period = 30;
    // double daily_tbl[period];
    static double initRate(){ return period; };
};
double Account::interestRate = initRate(); // 需要在外部初始化static成员
#endif
