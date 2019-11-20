#pragma once
#include <ostream>

class BigInt {

public: 
  BigInt(long number);
  BigInt(unsigned short *arr, unsigned long, bool is_neg); 
  BigInt(const BigInt &b);

  virtual ~BigInt();

  BigInt &operator = (const BigInt &b);  
  BigInt &operator += (const BigInt &b);
  BigInt &operator -= (const BigInt &b);
  BigInt &operator *= (const BigInt &b);
  BigInt &operator /= (const BigInt &b);
  
  bool operator < (const BigInt &b);
  bool operator > (const BigInt &b);
  bool operator <= (const BigInt &b);
  bool operator >= (const BigInt &b);
  bool operator != (const BigInt &b);
  bool operator == (const BigInt &b);

  short cmp(const BigInt &b) const;
  
  friend BigInt operator + (const BigInt &a, const BigInt &b);
  friend BigInt operator - (const BigInt &a, const BigInt &b);
  friend BigInt operator * (const BigInt &a, const BigInt &b);
  friend BigInt operator / (const BigInt &a, const BigInt &b);

  friend std::ostream& operator << (std::ostream &os, const BigInt &b);
  friend BigInt add(const BigInt &a, const BigInt &b);
  friend BigInt sub(const BigInt &a, const BigInt &b);
  friend unsigned short getDigit(const BigInt& b, unsigned long l);

private:
  bool is_negative;
  unsigned long length;
  unsigned short *digits;
  void setLength(unsigned long l = 0);
 
};

unsigned short *allocate_mem(unsigned long length); 
unsigned short *reallocate_mem(unsigned long new_length, unsigned long old_length, unsigned short *arr);
