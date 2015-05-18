#ifndef HUGEINT_H
#define HUGEINT_H
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class HugeInt{
  friend ostream &operator<<(ostream &,const HugeInt &);
  friend istream &operator>>(istream &,HugeInt &);

public:
  HugeInt();
  HugeInt(const int &);
  HugeInt(const string &);

  const HugeInt &operator=(const HugeInt &);
  const HugeInt &operator+(const HugeInt &);
  const HugeInt &operator-(HugeInt);

private:
  int int_num[100];     //store most 100 digits
  int arr_size;  
};
#endif
