#include "BigInt.h"
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>

#pragma warning( push )
#pragma warning( disable : 6386 )

BigInt::BigInt(long number): is_negative(number < 0) {

  setLength(abs(number)); 
  digits = allocate_mem(length); 

  long nr = abs(number);

  for (unsigned long i = 0; i < length; i++)
  {
	  digits[i] = nr % 10; 
	  nr /= 10; 
  }  
} 

BigInt::BigInt(unsigned short* arr, unsigned long len, bool is_neg): is_negative(is_neg), length(len), digits(nullptr) {
  if (len > 0) {
    digits = allocate_mem(length);

    for (unsigned long i = 0; i < length; i++)
    {
      digits[i] = arr[i]; 
    }
  } 

  //eliminate unnecessary zeros
  for (unsigned long i = length - 1; i < length; i--) {
    if (digits[i] == 0)
      length--;
    else
      break;
  }
}

BigInt::~BigInt() {
  if (digits != nullptr) {
    delete[] digits;
    digits = nullptr; 
  }
}

BigInt::BigInt(const BigInt &b): length(b.length), is_negative(b.is_negative) {
  digits = allocate_mem(b.length);

  for (unsigned long i = 0; i < b.length; i++)
    digits[i] = getDigit(b, i);
}

BigInt &BigInt::operator=(const BigInt &b) {
  if (this == &b) return *this;

  digits = reallocate_mem(b.length, length, b.digits);
  length = b.length;
  is_negative = b.is_negative;

  for (unsigned long i = 0; i < length; i++)
    digits[i] = getDigit(b, i);

  return *this;
}
BigInt& BigInt::operator+=(const BigInt &b)
{
  return *this = *this + b; 
}
BigInt& BigInt::operator-=(const BigInt &b)
{
  return *this = *this - b;
}
BigInt& BigInt::operator*=(const BigInt &b)
{
  return *this = *this * b;
}
BigInt& BigInt::operator/=(const BigInt &b)
{
  return *this = *this / b;
}

bool BigInt::operator<(const BigInt &b)
{
  if (is_negative && b.is_negative) return (cmp(b) > 0); 
  if (b.is_negative) return false;
  if (is_negative) return true;

  return (cmp(b) < 0); 
}

bool BigInt::operator>(const BigInt &b)
{
  if (is_negative && b.is_negative) return (cmp(b) < 0);
  if (b.is_negative) return true;
  if (is_negative) return false;

  return (cmp(b) > 0);
}

bool BigInt::operator<=(const BigInt &b)
{
  if (is_negative && b.is_negative) return (cmp(b) >= 0);
  if (b.is_negative) return false;
  if (is_negative) return true;

  return (cmp(b) <= 0);
}

bool BigInt::operator>=(const BigInt &b)
{
  if (is_negative && b.is_negative) return (cmp(b) <= 0);
  if (b.is_negative) return true;
  if (is_negative) return false;

  return (cmp(b) >= 0);
}

bool BigInt::operator!=(const BigInt &b)
{
  if (is_negative != b.is_negative) return true;
  return cmp(b) != 0;
}

bool BigInt::operator==(const BigInt &b)
{
  if (is_negative != b.is_negative) return false; 
  return cmp(b) == 0; 
}

short BigInt::cmp(const BigInt &b) const {
  unsigned long i = length - 1;
  if (length > b.length) return 1;
  if (length < b.length) return -1;
  else
  {
    while (i < length && digits[i] == b.digits[i])    
      i--;
    if (digits[i] > b.digits[i]) return 1; 
    if (digits[i] < b.digits[i]) return -1; 
  }
  return 0; 
}


void BigInt::setLength(unsigned long l) 
{
  if (l > 0)
    this->length = (unsigned long)floor(log10(l) + 1);
  else
    this->length = 1; 
}

std::ostream &operator<<(std::ostream &os, const BigInt &b) {
  
  if (b.is_negative) os << "-"; 
  for (unsigned long i = b.length; i > 0; i--)
  {
    os << b.digits[i - 1]; 
  }
  return os; 
}

BigInt add(const BigInt &a, const BigInt &b)
{
  BigInt sum(a); 
  unsigned short digit = 0; 
  //evaluate new length
  if (sum.length <= b.length) {
    sum.length = b.length;
    sum.digits = reallocate_mem(sum.length, a.length, sum.digits);
  }

   //add the digits from two arrays in a new array
   for (unsigned long i = 0; i < sum.length; i++)
   {
     if (i < a.length && i < b.length) {
       digit += getDigit(a, i) + getDigit(b, i);
       if (digit > 9) {
         sum.digits[i] = digit % 10;
         digit = 1;
       }
       else {
         sum.digits[i] = digit;
         digit = 0;
       }
     } 
     else if (i < a.length) {
       digit += getDigit(a, i); 
       if (digit > 9) {
         sum.digits[i] = digit % 10;
         digit = 1;
       }
       else {
         sum.digits[i] = digit;
         digit = 0;
       }
     }
     else if (i < b.length) {
       digit += getDigit(b, i);
       if (digit > 9) {
         sum.digits[i] = digit % 10;
         digit = 1;
       } else {
         sum.digits[i] = digit;
         digit = 0;
       }
     }
   }
   
   //if digit is not 0 reallocate memory for the last digit
   if (digit != 0) {
     sum.length += 1;
     sum.digits = reallocate_mem(sum.length, sum.length - 1, sum.digits);
     sum.digits[sum.length - 1] = digit;
   }
     
  return sum;
}

BigInt sub(const BigInt &a, const BigInt &b) {
  unsigned short val1 = 0; 
  unsigned short val2 = 0; 
  unsigned short *digits = allocate_mem(a.length); 
  unsigned short carry = 0; 
  unsigned long i = 0;

  for (i = 0; i < a.length; i++) {
    val1 = getDigit(a, i);  
    val2 = (b.length > i ? getDigit(b, i) : 0) + carry;
    carry = (val1 < val2 ? 1 : 0);
    digits[i] = (val1 + (carry * 10)) - val2; 
  }

  //create new BigInt
  BigInt diff(digits, i, false); 

  delete[] digits; 
  return diff; 
}

unsigned short getDigit(const BigInt &b, unsigned long l)
{
  if (l < b.length)
    return b.digits[l];

  return 0;
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
  if (a.is_negative && b.is_negative) {
    BigInt sum = add(a, b);     
    sum.is_negative = true; 
    return sum;
  } 
  else if (a.is_negative) {
    if (a.cmp(b) > 0) {
      BigInt sum = sub(a, b);
      sum.is_negative = true;
      return sum;
    } else {
      BigInt sum = sub(b, a);
      sum.is_negative = false;
      return sum;
    }
  }
  else if (b.is_negative) {
    if (a.cmp(b) > 0) {
      BigInt sum = sub(a, b);
      sum.is_negative = false;
      return sum;
    } else {
      BigInt sum = sub(b, a);
      sum.is_negative = true;
      return sum;
    }
  } 
  else {
    BigInt sum = add(a, b);
    sum.is_negative = false;
    return sum;
  }
}

BigInt operator-(const BigInt &a, const BigInt &b) {
  if (a.is_negative && b.is_negative) {
    if (a.cmp(b) > 0) {
      BigInt diff = sub(a, b);
      diff.is_negative = true;
      return diff;
    } else {
      BigInt diff = sub(b, a);
      diff.is_negative = false;
      return diff;
    }
  } 
  else if (a.is_negative) {
    BigInt diff = add(a, b);
    diff.is_negative = true;
    return diff;
  } 
  else if (b.is_negative) {
    BigInt diff = add(a, b);
    diff.is_negative = false;
    return diff;
  } 
  else {
    if (a.cmp(b) > 0) {
      BigInt diff = sub(a, b);
      diff.is_negative = false;
      return diff;
    } else {
      BigInt diff = sub(b, a);
      diff.is_negative = true;
      return diff;
    }
  }
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
  unsigned long maxLength = a.length + b.length; 
  unsigned short carry = 0; 
  unsigned short *product = allocate_mem(maxLength); 
  bool is_negative = (a.is_negative != b.is_negative ? true : false); 

  for (unsigned long i = 0; i < maxLength; i++) {
    product[i] = 0; 
  }
     
  for (unsigned long i = 0; i < b.length; i++) {
    carry = 0; 
    for (unsigned long j = 0; j < a.length; j++) {
      unsigned short factor1 = getDigit(a, j);
      unsigned short factor2 = getDigit(b, i);
      product[i + j] += (factor1 * factor2) + carry;  
      carry = product[i + j] / 10;
      product[i + j] %= 10;
    }
    product[i + a.length] = carry;
  }

  BigInt new_product(product, maxLength, is_negative);
  delete[] product; 
  return new_product;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
  //return zero if divisor is biger then the divident or divisor is 0
  BigInt zero(0L);
  if (a.cmp(b) <= 0 || !b.cmp(zero)) return zero;
  
  BigInt divident(a);
  BigInt divisor(b);
  divident.is_negative = false; 
  divisor.is_negative = false; 
  bool is_negative = (a.is_negative != b.is_negative ? true : false);
  
  BigInt i(0L); 
  while (divident.cmp(divisor) >= 0) {
    divident -= divisor; 
    i += 1; 
  }
  i.is_negative = is_negative; 
  
  BigInt new_quotient(i);
  return new_quotient; 
}

unsigned short *allocate_mem(unsigned long length) {
  unsigned short *mem = new unsigned short[length];
  assert(mem != nullptr);
  return mem; 
}

unsigned short *reallocate_mem(unsigned long new_length, unsigned long old_length ,unsigned short *arr) {
  unsigned short *mem = new unsigned short[new_length];
  assert(mem != nullptr);
  
  //init new array 
  for (unsigned long i = 0; i < new_length; i++)
  {
    mem[i] = 0; 
  }
  //copy old array content to new array if possible 
  for (unsigned long i = 0; i < old_length && i < new_length; i++)
  {
    mem[i] = arr[i]; 
  }
  
  return mem; 
}


#pragma warning( pop )