 * Binary search tree using doubly-linked lists
 * COMP319 Algorithms, Fall 2019
 * School of Electronics Engineering, Kyungpook National University
 * Instructor: Gil-Jin Jang

### DATA STRUCTURE:
```
binary tree node definition using doubly linked lists
key is a string of a fixed length
KEYLENGTH	length of the key
BULK_SIZE	key is hidden in the "BULK"
to retrieve key, we have to dig into the "BULK"
so accessing key takes average "BULK_SIZE"/2 searches
this is INTENTIONALLY to add extra overhead for search
your program should reduce the number of key accesses at your best
```

BST Tree Algorithm
1. Get input as Left Half Binary Tree from file(i.txt)
2. Insertion sort of LHBT
3. Print sorted tree(several modes included)
4. Sorted tree into Complete Binary Tree
5. Quick sort of LHBT
--------------------------------------------------------------
