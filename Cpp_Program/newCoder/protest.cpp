#include <stdio.h>
#pragma pack(2)
struct A{
  int a;
  char b;
  short c;
};
#pragma pack()
#pragma pack(4)
struct B{
  char b;
  int a;
  short c;
};

#pragma pack()

int main(){
  float num = 1e+5;
  printf("sizeof(A) = %d,size(B) = %d \n",sizeof(A),sizeof(B));
  printf("%f",num);
}
