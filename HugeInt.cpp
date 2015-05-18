#include"HugeInt.h"
using namespace std;

HugeInt::HugeInt()
{
  arr_size=100;		     //預設size為100	
  for(int i=0;i<100;i++)     //把數字都初始成零
    int_num[i]=0;
}
HugeInt::HugeInt(const int &num)
{
  for(int i=0;i<100;i++)     //把數字都初始成零
    int_num[i]=0;

  stringstream s1;
  string str1;
  
  s1 << num;      //int -> string
  s1 >> str1;
  
  arr_size=str1.size();
  
  stringstream s2[arr_size];
  string str_arr[arr_size];
  
  for(int i=0;i<arr_size;i++)
  {
    str_arr[i]=str1.substr(i,1);    //切割成一個一個數字
  }  
  for(int i=arr_size-1,j=0;i>=0;i--,j++) //從個位數開始存
  {
    s2[i]<<str_arr[i];  //str -> int
    s2[i]>>int_num[j];
  }
}
HugeInt::HugeInt(const string &str2)
{
  for(int i=0;i<100;i++)     //把數字都初始成零
    int_num[i]=0;
  
  arr_size=str2.size();
  stringstream ss[arr_size];
  string str_arr[arr_size];
  
  for(int i=0;i<arr_size;i++)
  {
    str_arr[i]=str2.substr(i,1);
  }
  for(int i=arr_size-1,j=0;i>=0;i--,j++)
  {
    ss[i]<<str_arr[i];   //str -> int
    ss[i]>>int_num[j];
  }
}

const HugeInt & HugeInt::operator=(const HugeInt &right)
{
  for(int i=0;i<right.arr_size;i++)
  {
    int_num[i]=right.int_num[i];
  }
  return *this;
}

const HugeInt HugeInt::operator+(const HugeInt &right)
{
  HugeInt answer;
  
  for(int i=0;i<(arr_size>right.arr_size?arr_size:right.arr_size);i++)
  {
    answer.int_num[i]=int_num[i]+right.int_num[i];
  }  
  for(int i=0;i<(arr_size>right.arr_size?arr_size:right.arr_size);i++)  
  {
    if(answer.int_num[i]>=10)
    {
      answer.int_num[i]=answer.int_num[i]-10;
      answer.int_num[i+1]=answer.int_num[i+1]+1;
    }
  }
  return answer;
}

const HugeInt HugeInt::operator-(HugeInt right)
{
  HugeInt answer;
  int arr[arr_size];		  //避免改到原本的數字
  for(int i=0;i<arr_size;i++)
    arr[i]=int_num[i];
  
  if(arr_size>right.arr_size)     //正的
  {
    for(int i=0;i<arr_size;i++)
    {
      answer.int_num[i]=arr[i]-right.int_num[i];
      if(answer.int_num[i]<0)
      {
        answer.int_num[i]=answer.int_num[i]+10;
	arr[i+1]=arr[i+1]-1;
      }
    }
  }
  if(arr_size<right.arr_size)   //負的
  {
    for(int i=0;i<right.arr_size;i++)
    {
      answer.int_num[i]=right.int_num[i]-arr[i]; 
      if(answer.int_num[i]<0)
      {
        answer.int_num[i]=answer.int_num[i]+10;
	right.int_num[i+1]=right.int_num[i+1]-1;
      }
    }
    for(int i=right.arr_size-1;i>=0;i--)   //把負號加上去
    {  
      if(answer.int_num[i]!=0)
      {
        answer.int_num[i]=(answer.int_num[i])*(-1);  
        break;
      }
    }
  }
  if(arr_size==right.arr_size)   //位數相同
  {
    for(int i=arr_size-1;i>=0;i--)
    {  
      if(int_num[i]>right.int_num[i])   //正的 
      {
        for(int j=0;j<arr_size;j++)
        {
          answer.int_num[j]=arr[j]-right.int_num[j];
	  if(answer.int_num[j]<0)
          {
            answer.int_num[j]=answer.int_num[j]+10;
	    arr[j+1]=arr[j+1]-1;
          }
        }
        break;
      }  
      if(int_num[i]<right.int_num[i])   //負的
      {
        for(int j=0;j<arr_size;j++)
        {
          answer.int_num[j]=right.int_num[j]-arr[j]; 
          if(answer.int_num[j]<0)
          {
            answer.int_num[j]=answer.int_num[j]+10;
	    right.int_num[j+1]=right.int_num[j+1]-1;
          }
        }
        for(int k=arr_size-1;k>=0;k--)   //把負號加上去
        {  
          if(answer.int_num[k]!=0)
          {
            answer.int_num[k]=(answer.int_num[k])*(-1);  
            break;
          }
        }
        break;
      }
      if(i==0)              //兩個一樣
      {
        for(int j=0;j<arr_size;j++)
	  answer.int_num[j]=0;
      }
    }    
  }
  return answer;
}

ostream & operator<<(ostream &out,const HugeInt &a)
{
  int size=1;
  for(int i=a.arr_size-1;i>=0;i--)
  {
    if(a.int_num[i]!=0)         //找出有幾位數
      {size=i+1;break;} 
  }
  
  for(int i=size-1;i>=0;i--)    //從後面大的位數先印出來
    out<<a.int_num[i];
  return out;
}

istream & operator>>(istream &in,HugeInt &a)
{
  string input_str;
  in>>input_str;
  a.arr_size=input_str.size();
  string str_arr[a.arr_size];
  stringstream ss[a.arr_size];
  for(int i=0;i<a.arr_size;i++)
  {
    str_arr[i]=input_str.substr(i,1);
  }
  for(int i=a.arr_size-1,j=0;i>=0;i--,j++)
  {
    ss[i]<<str_arr[i];
    ss[i]>>a.int_num[j];
  }
  return in;
}
