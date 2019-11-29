COMP319 Algorithms, Spring 2019
---
Programming Assignment 4
---
#### School of Electronics Engineering
---
### 1. 0-1 knapsack problem

Knapsack problem is finding a best subset of given items that satisfies:
- the sum of the item weights is less than the capacity of the knapsack (*W*).
- the sum of the item values is maximized.
If we allow 0-1 choices only, the items are indivisible, and the relaxed problem can be solved with dynamic programming.

* __To do:__ Design an algorithm that finds:
  - the subset of the items by their numbers (chosen from 1 to _N_).
  - the maximum value.
  
* __INPUT:__ The input is given by a text file, with each row represents each item's weight and value. The last line is the maximum weight followed by -1, so you can finish reading the file if the input number is -1.
```
2 3
3 4
4 6
5 7
8 -1
```
All the values are POSITIVE integers. You may use file I/O, or standard input. From the input file, number of items _n_ = 4, (weight, benefit) of the items are: `(2,3), (3,4), (4,6), (5,7)`, and _W_ = 8 (max weight). 

* __OUTPUT:__ 
```
2 4 11
```


### 2. 0-1 knapsack with one item split

In this problem, it is assumed that ONLY ONE item can be split by HALVES --- one item is split into two items with the same weight and the same value, half the weight and half the value, respectively. We may choose one half-split item, or whole item, whichever maximizes the value.

* __To do:__ Design an algorithm that finds:
  - the subset of the items by their numbers (chosen from 1 to _N_).
  - the maximum value.
  - if necessary, specify one item to be split by halves by appending __'x0.5'__ to the item number.
  
* __Note:__ when the weights and values are odd numbers, their split weights and values may have fractional parts (0.5). If you use a dynamic programming algorithm (probably), those odd number cases should be considered.

* __INPUT:__ The input is given by a text file, with each row represents each item's weight and value. The last line is the maximum weight followed by -1, so you can finish reading the file if the input number is -1.
```
2 3
3 4
4 6
5 7
8 -1
```
All the values are POSITIVE integers. You may use file I/O, or standard input. From the input file, number of items _n_ = 4, (weight, benefit) of the items are: `(2,3), (3,4), (4,6), (5,7)`, and _W_ = 8 (max weight).
<!-- - No other input files will be given. Find good examples yourself) -->

* __OUTPUT:__ 
```
1x0.5 2 3 11.5
```
<!-- (Note: the standard 0-1 knapsack solution is choosing items 2 and 4, and their value is 11, which is less than 11.5) -->

### 3. 0-1 knapsack with one duplicate item

Same as problem 2, except that __EXACTLY ONE ITEM__ and be added __TWICE__.

* __To do:__ Design an algorithm that finds:
  - the subset of the items by their numbers (chosen from 1 to _N_).
  - the maximum value.
  - if necessary, specify one item to be split by halves by appending __'x2'__ to the item number.

* __INPUT:__ The input is given by a text file, with each row represents each item's weight and value. The last line is the maximum weight followed by -1, so you can finish reading the file if the input number is -1.
```
2 3
3 4
4 6
5 7
8 -1
```
All the values are POSITIVE integers. You may use file I/O, or standard input. From the input file, number of items _n_ = 4, (weight, benefit) of the items are: `(2,3), (3,4), (4,6), (5,7)`, and _W_ = 8 (max weight). 

* __OUTPUT:__ 
```
3x2 12
```

### 4. 0-1 knapsack with two identical knapsacks

Same as problem 1, except there are __TWO KNAPSACKS__ to be filled.

* __To do:__ Design an algorithm that finds:
  - the subset of the items by their numbers (chosen from 1 to _N_) and __knapsack numbers__ (1 or 2).
  - the maximum value.

* __INPUT:__ The input is given by a text file, with each row represents each item's weight and value. The last line is the maximum weights of the __TWO KNAPSACKS__ followed by -1, so you can finish reading the file if the input number is -1.
```
2 3
3 4
4 6
5 7
8 7 -1
```
All the values are POSITIVE integers. You may use file I/O, or standard input. From the input file, number of items _n_ = `4`, (weight, benefit) of the items are: `(2,3), (3,4), (4,6), (5,7)`, and _W_ = `(8, 7)` (max weights).

* __OUTPUT:__ 
```
2 1 4 1 1 2 3 2 20
```

* __Note:__ may not be solvable by dynamic programming (even the instructor does not know). Consider greedy algorithm.


