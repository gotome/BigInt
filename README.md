# BigInt

BigInt Class C++ for all basic arithmetic operations.

This class allows you to calculate verry large numbers.
The numbers are stored in dynamic arrays. This allows to calculate almost unlimited large numbers. 


**Numbers will get stored internally as follows:** 
<pre>
| example  | number     | index   0  1  2  |
| -------- |:----------:| ----------------:|
| 1        |    23      | array: [3][2]    |
| 2        |   100      | array: [0][0][1] |
</pre>

Following arithmetical operations are possible: 
* add
* subtract
* multiply
* divide

I've overloadet some operators that comparison is possible for two BigInt's. 
You can use following operators to compare BigInt's: 
* <, <=, \>, >=, ==, !=

**NOTE:**
The division algorithm returns an integer and no floating point value. The remainder is discarded.
