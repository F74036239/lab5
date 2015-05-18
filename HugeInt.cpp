#include"HugeInt.h"
using namespace std;

HugeInt::HugeInt()
{}
HugeInt::HugeInt(const int &num)
{
  stringstream s1,s2[100];
  string str1;
  
  s1 << num;      //int -> string
  s1 >> str1;
  
  arr_size=str1.size();
  
  string str_arr[arr_size];
  
  for(int i=0;i<arr_size;i++)
  {
    str_arr[i]=str1.substr(i,1);    //切割成一個一個數字
  }  
  /*check 
  cout<<"int cut string:";
  for(int i=0;i<arr_size;i++)
  {  
    cout<<str_arr[i]<<" ";
  }
  cout<<endl;
  */
  for(int i=arr_size-1,j=0;i>=0;i--,j++) //從個位數開始存
  {
    s2[i]<<str_arr[i];  //str -> int
    s2[i]>>int_num[j];
  }
  /*check
  cout<<"int int:";
  for(int i=0;i<arr_size;i++)
  {
    cout<<int_num[i]<<" ";
  }
  cout<<endl;
  */
}
HugeInt::HugeInt(const string &str2)
{
  stringstream ss[100];
  
  arr_size=str2.size();
  
  string str_arr[arr_size];
  
  for(int i=0;i<arr_size;i++)
  {
    str_arr[i]=str2.substr(i,1);
  }
  /*check 
  cout<<"str cut string:";
  for(int i=0;i<arr_size;i++)
  {  
    cout<<str_arr[i]<<" ";
  }
  cout<<endl;
  */
  for(int i=arr_size-1,j=0;i>=0;i--,j++)
  {
    ss[i]<<str_arr[i];   //str -> int
    ss[i]>>int_num[j];
  }
  /*check
  cout<<"str int:";
  for(int i=0;i<arr_size;i++)
  {
    cout<<int_num[i]<<" ";
  }
  cout<<endl;
  */
}

const HugeInt & HugeInt::operator=(const HugeInt &right)
{
  for(int i=0;i<right.arr_size;i++)
  {
    int_num[i]=right.int_num[i];
  }
  return *this;
}

const HugeInt & HugeInt::operator+(const HugeInt &right)
{
  for(int i=0;i<(arr_size>right.arr_size?arr_size:right.arr_size);i++)
  {
    int_num[i]=int_num[i]+right.int_num[i];
    if(int_num[i]>=10)
    {
      int_num[i]=int_num[i]-10;
      int_num[i+1]=int_num[i+1]+1;
    }
  }
  return *this;
}

const HugeInt & HugeInt::operator-(HugeInt right)
{
  if(arr_size>right.arr_size)     //正的
  {
    for(int i=0;i<arr_size;i++)
    {
      int_num[i]=int_num[i]-right.int_num[i];
      if(int_num[i]<0)
      {
        int_num[i]=int_num[i]+10;
	int_num[i+1]=int_num[i+1]-1;
      }
    }
  }
  if(arr_size<right.arr_size)   //負的
  {
    for(int i=0;i<right.arr_size;i++)
    {
      int_num[i]=right.int_num[i]-int_num[i]; 
      if(int_num[i]<0)
      {
        int_num[i]=int_num[i]+10;
	right.int_num[i+1]=right.int_num[i+1]-1;
      }
    }
    for(int i=right.arr_size-1;i>=0;i--)   //把負號加上去
    {  
      if(int_num[i]!=0)
      {
        int_num[i]=(int_num[i])*(-1);  
        break;
      }
    }
  }
  if(arr_size==right.arr_size)
  {
    if(int_num[arr_size]>right.int_num[arr_size])   //正的 
    {
      for(int i=0;i<arr_size;i++)
      {
        int_num[i]=int_num[i]-right.int_num[i];
        if(int_num[i]<0)
        {
          int_num[i]=int_num[i]+10;
	  int_num[i+1]=int_num[i+1]-1;
        }
      }
    }
    if(int_num[arr_size]<right.int_num[arr_size])   //負的
    {
      for(int i=0;i<right.arr_size;i++)
      {
        int_num[i]=right.int_num[i]-int_num[i]; 
        if(int_num[i]<0)
        {
          int_num[i]=int_num[i]+10;
	  right.int_num[i+1]=right.int_num[i+1]-1;
        }
      }
      for(int i=right.arr_size-1;i>=0;i--)   //把負號加上去
      {  
        if(int_num[i]!=0)
        {
          int_num[i]=(int_num[i])*(-1);  
          break;
        }
      }
    }
  }
  return *this;
}

ostream & operator<<(ostream &out,const HugeInt &a)
{
  for(int i=a.arr_size-1;i<=0;i--)    //從後面大的位數先印出來
    out<<a.int_num[i];
  out<<endl;
  return out;
}

istream & operator>>(istream &in,HugeInt &a)
{
  string input_str;
  in>>input_str;
  string str_arr[input_str.size()];
  stringstream ss[100];
  for(int i=0;i<input_str.size();i++)
  {
    str_arr[i]=input_str.substr(i,1);
  }
  for(int i=input_str.size(),j=0;i>=0;i--,j++)
  {
    ss[i]<<str_arr[i];
    ss[i]>>a.int_num[j];
  }
  return in;
}
