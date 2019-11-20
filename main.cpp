#include <iostream>
#include <ctime>
#include "BigInt.h"

using namespace std;

#define PRINT(exp) cout << (#exp) << " = " << (exp) << endl; 

const int arr_length = 23; 

void test_rand() {
    long v1 = rand() % 20000 - 10000;
    long v2 = rand() % 20000 - 10000;
    long compare_result = 0; 
    BigInt b1 = v1;
    BigInt b2 = v2;
    BigInt b_result = 0L; 

    cout << endl; 
    cout << "<<<<<BEGIN RANDOM TESTS>>>>>" << endl; 
    cout << "first number:" << b1 << endl;
    cout << "second number:" << b2 << endl;
    cout << endl; 
    //addition
    cout << "addition: " << endl; 
    b_result = b1 + b2;
    compare_result = v1 + v2;

    cout << "BigInt result : " << b_result << endl;
    cout << "compare result: " << compare_result << endl;
    cout << endl;

    //subtraction
    cout << "subtraktion: " << endl;
    b_result = b1 - b2;
    compare_result = v1 - v2;

    cout << "BigInt result : " << b_result << endl;
    cout << "compare result: " << compare_result << endl;
    cout << endl;

    //multiplication
    cout << "multiplikation: " << endl;
    b_result = b1 * b2;
    compare_result = v1 * v2;

    cout << "BigInt result : " << b_result << endl;
    cout << "compare result: " << compare_result << endl;
    cout << endl;

    //division
    cout << "division: " << endl;
    b_result = b1 / b2;
    compare_result = v1 / v2;

    cout << "BigInt result : " << b_result << endl;
    cout << "compare result: " << compare_result << endl;

    cout << endl;
}

int main() {
  srand((unsigned int)time(NULL));
  unsigned short arr[arr_length] = {9, 2, 3, 4, 5, 6, 6, 4, 4, 2, 6, 2, 0, 3, 1, 5, 0, 9, 0, 8, 6, 4};
  unsigned short arr2[arr_length] = {1, 2, 3, 2, 3, 4, 5, 6, 8, 0, 1, 2, 3, 4, 5, 6, 7, 9, 0, 9, 0, 3};

  BigInt b1(999);
  BigInt b2 = 1001; 
  BigInt b3(1002);
  BigInt b4(10000);
  BigInt b5(b1);

  BigInt b6(100);
  BigInt b7(1000);
  BigInt b8(-100);
  BigInt b9(-1000);

  BigInt b10(arr, arr_length, false);
  BigInt b11(arr2, arr_length, false);
  BigInt b13(b8);
  BigInt b14(1); 
  
  PRINT(b1);
  PRINT(b2);
  PRINT(b3);
  PRINT(b4);
  PRINT(b5);
  
/**********************************************/
/*                  test cmp                  */
/**********************************************/ 
  {
    cout << endl;
    cout << "*****test cmp*****" << endl;
    cout << (b1 < b2) << " (b1 < b2) " << endl;
    cout << (b2 < b1) << " (b2 < b1) " << endl;

    cout << (b1 <= b2) << " (b1 <= b2) " << endl;
    cout << (b2 <= b1) << " (b2 <= b1) " << endl;
    cout << (b1 <= b5) << " (b1 <= b5) " << endl;

    cout << (b1 > b2) << " (b1 > b2) " << endl;
    cout << (b2 > b1) << " (b2 > b1) " << endl;

    cout << (b1 >= b2) << " (b1 >= b2) " << endl;
    cout << (b2 >= b1) << " (b2 >= b1) " << endl;
    cout << (b1 <= b5) << " (b1 <= b5) " << endl;
    
    cout << (b1 != b2) << " (b1 != b2) " << endl;
    cout << (b1 != b5) << " (b1 != b5) " << endl;

    cout << (b1 == b2) << " (b1 == b2) " << endl;
    cout << (b1 == b5) << " (b1 == b5) " << endl;
    cout << endl; 
  }

  {
    cout << "*****test cmp with negative numbers*****" << endl;
    PRINT(b6);
    PRINT(b8);
    PRINT(b13);

    cout << (b6 < b8) << " (b6 < b8) " << endl;
    cout << (b8 < b6) << " (b8 < b6) " << endl;
     
    cout << (b6 <= b8) << " (b6 <= b8) " << endl;
    cout << (b8 <= b6) << " (b8 <= b6) " << endl;
    cout << (b8 <= b13) << " (b8 <= b13) " << endl;

    cout << (b6 > b8) << " (b6 > b8) " << endl;
    cout << (b8 > b6) << " (b8 > b6) " << endl;

    cout << (b6 >= b8) << " (b6 >= b8) " << endl;
    cout << (b8 >= b6) << " (b8 >= b6) " << endl;
    cout << (b8 <= b13) << " (b8 <= b13) " << endl;

    cout << (b6 != b8) << " (b6 != b8) " << endl;
    cout << (b8 != b13) << " (b8 != b6) " << endl;

    cout << (b6 == b8) << " (b6 == b8) " << endl;
    cout << (b8 == b13) << " (b8 == b13) " << endl;
  }
  
  /**********************************************/
  //     test arithmetic operations + AND -     */
  /**********************************************/

  {
    cout << endl;
    cout << "*****test arithmetic operations + AND - *****" << endl;
    PRINT(b6);
    PRINT(b7);
    PRINT(b8);
    PRINT(b9);
    //smaller value - greater value tests
    BigInt c1 = b6 + b7; 
    BigInt c2 = b6 - b7;

    BigInt c3 = b6 + b9;
    BigInt c4 = b6 - b9;

    BigInt c5 = b8 + b7;
    BigInt c6 = b8 - b7;

    BigInt c7 = b8 + b9;
    BigInt c8 = b8 - b9;

    cout << endl;
    cout << "b6 + b7 = "; PRINT(c1);
    cout << "b6 - b7 = "; PRINT(c2);
    cout << "b6 + b9 = "; PRINT(c3);
    cout << "b6 - b9 = "; PRINT(c4);
    cout << "b8 + b7 = "; PRINT(c5);
    cout << "b8 - b7 = "; PRINT(c6);
    cout << "b8 + b9 = "; PRINT(c7);
    cout << "b8 - b9 = "; PRINT(c8);

    //greater value - smaller value tests
    BigInt c9 = b7 + b6;
    BigInt c10 = b7 - b6;

    BigInt c11 = b9 + b6;
    BigInt c12 = b9 - b6;

    BigInt c13 = b7 + b8;
    BigInt c14 = b7 - b8;

    BigInt c15 = b9 + b8;
    BigInt c16 = b9 - b8;
    
    cout << "b7 + b6 = "; PRINT(c9);
    cout << "b7 - b6 = "; PRINT(c10);
    cout << "b9 + b6 = "; PRINT(c11);
    cout << "b9 - b6 = "; PRINT(c12);
    cout << "b7 + b8 = "; PRINT(c13);
    cout << "b7 - b8 = "; PRINT(c14);
    cout << "b9 + b8 = "; PRINT(c15);
    cout << "b9 - b8 = "; PRINT(c16);
  }
  
/*********************************************/
/*            test huge numbers              */
/*********************************************/


  cout << endl;
  cout << "***** test huge numbers*****" << endl;
  PRINT(b10); 
  PRINT(b11); 
  BigInt result = b10 + b11;
  cout << "b10 + b11" << endl;   
  PRINT(result);

  result = b10 - b11;
  cout << "b10 - b11" << endl;
  PRINT(result);

  result = b10 * b11;
  cout << "b10 * b11" << endl;
  PRINT(result);
  
  result = b10 / b11;
  cout << "b10 / b11" << endl;
  PRINT(result);
  
/*********************************************/
/*    test arithmetic operations * AND /     */
/*********************************************/
  
  {
    cout << endl; 
    cout << "***** test arithmetic operations * AND / *****" << endl;
    PRINT(b6);
    PRINT(b7);
    PRINT(b8);
    PRINT(b9);
    //greater value - smaller value tests
    BigInt c1 = b7 * b6;
    BigInt c2 = b7 / b6;

    BigInt c3 = b9 * b6;
    BigInt c4 = b9 / b6;

    BigInt c5 = b7 * b8;
    BigInt c6 = b7 / b8;

    BigInt c7 = b9 * b8;
    BigInt c8 = b9 / b8;
    
    cout << "b7 * b6 = "; PRINT(c1);
    cout << "b7 / b6 = "; PRINT(c2);
    cout << "b9 * b6 = "; PRINT(c3);
    cout << "b9 / b6 = "; PRINT(c4);
    cout << "b7 * b8 = "; PRINT(c5);
    cout << "b7 / b8 = "; PRINT(c6);
    cout << "b9 * b8 = "; PRINT(c7);
    cout << "b9 / b8 = "; PRINT(c8);
  }

/*********************************************/
/*          test critical numbers            */
/*********************************************/

  cout << endl;
  cout << "***** test critical numbers *****" << endl;
  PRINT(b1);
  PRINT(b6);
  PRINT(b14);

  BigInt c1 = b14 + b1; 
  BigInt c2 = b6 - b14; 

  cout << "b14 + b1 = "; PRINT(c1);
  cout << "b6 - b14 = "; PRINT(c2);

/*********************************************/
/*               random tests                */
/*********************************************/

  cout << endl;
  cout << "***** random tests *****" << endl;
  for (int i = 0; i < 100; i++) {
    test_rand();
  }
  
  return 0;
} 