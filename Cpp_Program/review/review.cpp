#include <iostream>
#include <string>

using namespace std;

extern int i;
int ival = 1024;
int &refVal = ival;
int *p = &ival;
int *&r = p;
const int ci = 42;
const int &r1 = ival;

class A{
  private:
      int value;
  public:
      A(int n){value = n;}
      A(const A& other){value = other.value;}
      void Print(){ cout << value << endl;}
};

class CMyString{
  public:
  CMyString(char* pData = nullptr);
  CMyString(const CMyString& str);
  ~CMyString(void);
  CMyString& operator=(const CMyString&);
  private:
     char* m_pData;

};
// 初级程序员
// CMyString& CMyString::operator=(const CMyString& mptr){
//   if(this == &mptr)
//     return *this;
//   delete []m_pData;
//   m_pData = nullptr;

//   m_pData = new char[strlen(mptr.m_pData)+1];
//   strcpy(m_pData,mptr.m_pData);
//   return *this;
// }

// 高级程序员
CMyString& CMyString::operator=(const CMyString& mptr){
  if(this!=&mptr){
    CMyString strTmp(mptr);
    char* stmp = strTmp.m_pData;
    strTmp.m_pData = m_pData;
    m_pData = stmp;
  }
  return *this;
}
int main(){
  cout << refVal << endl;
  cout << r1 << endl;
  return 0;
}
