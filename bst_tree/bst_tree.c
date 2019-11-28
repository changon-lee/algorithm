/* Binary search tree using doubly-linked lists
 * COMP319 Algorithms, Fall 2019
 * School of Electronics Engineering, Kyungpook National University
 * Instructor: Gil-Jin Jang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MEASURE_TIME	// to measure time

/////////////////////////////////////////////////////////////
// DATA STRUCTURE:
// binary tree node definition using doubly linked lists
// key is a string of a fixed length
// KEYLENGTH	length of the key
// BULK_SIZE	key is hidden in the "BULK"
//	to retrieve key, we have to dig into the "BULK"
//	so accessing key takes average "BULK_SIZE"/2 searches
//	this is INTENTIONALLY to add extra overhead for search
//	your program should reduce the number of key accesses at your best
/////////////////////////////////////////////////////////////
#define KEYLENGTH	3
#define BULK_SIZE	4096

//#define BULK_SIZE	65536
typedef struct BTNode {
  char bulk[BULK_SIZE];	// null character to be added
  struct BTNode *left, *right;	// binary tree: left and right children
}T_NODE;

typedef struct{
  int count;
  int level;
  T_NODE* root;
}BST_TREE;

BST_TREE* create_bst_tree() {
    BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
    tree->count = 0;
    tree->root = NULL;
    tree->level = 0;
    return tree;
}
/////////////////////////////////////////////////////////////
// GIVEN: functions for binary tree node
// name and parameters only
// implementations are moved after "main" function
/////////////////////////////////////////////////////////////

const char* getkey(T_NODE *a);
// return value: char array of KEYLENGTH+1 (+1 for '\0' character)
//  key is hidden in "bulk", so use the following function to
//  read key string of length KEYLENGTH
//  it will make BULK_SIZE/2 searches on average
//  so try to use it as rarely as possible

int setkey(T_NODE *a, const char kw[]);
// return value: 0 for failure (NULL a), 1 for success
//  the following function hides a string "kw" of KEYLENGTH
//  by randomly selecting the location to save key

int copykey(T_NODE *dst, T_NODE *src)
{ return setkey(dst,getkey(src)); }
// copies the key of one node to the other
// very simple, single line, so implementation is given here

int comparekey(T_NODE *a, T_NODE *b);
// return value: (by character comparison)
//  -1 if a's key < b's key
//  0 if a's key == b's key
//  +1 if a's key > b's key
//  may be needed for binary search tree search and build-up

T_NODE *generate_btnode(const char kw[]);
// return value: pointer to a single BTNode (left/right are NULL)
//  generates a node for binary tree

void free_bt_recursive (T_NODE *bt);
// frees a binary tree

T_NODE *copy_bt_recursive (T_NODE *bt);
// return value: pointer to the root of the copy of the given binary tree "bt"

T_NODE *insert_left_bcnode(
    T_NODE *parent, T_NODE *newPtr );
//  adds a node to the left of a BTNode parent
//  it will be used to generate a left-half binary tree
//  (LHBT, all rights are NULL)
// pre-condition: left pointer to the new node should be NULL
// to store the left pointer to the parent node
// return value: parent if the given parent is not NULL; newPtr if parent NULL

BST_TREE *readkeys_textfile_LHBT( const char infile[], int *pN );
// File I/O: read key words from the given file
// and generate a binary tree which is left-half
// (all right children are NULL)

/////////////////////////////////////////////////////////////
// FILL 1: generate a binary search tree using insertion
/////////////////////////////////////////////////////////////
int find_tree_count(T_NODE* root, int count)
{
    if(!root) return count;
    else{
        count = find_tree_count(root->left,count);
        count++;
        count = find_tree_count(root->right,count);
    }
    return count;
}

int find_tree_level(T_NODE* root)
{
    if(!root) return 0;
    else{
        int le_h = find_tree_level(root->left);
        int rig_h = find_tree_level(root->right);
        if(le_h > rig_h) return le_h+1;
        else return rig_h+1;
    }
}
T_NODE *insert_to_BST_leaf(T_NODE *bst, T_NODE *newPtr)
{
  if ( bst == NULL )  return newPtr;	// new bst as the input node
  else if ( newPtr == NULL ) return bst;	// nothing to add
  else {
    if ( comparekey(bst, newPtr) < 0 ) { // if bst < newPtr;
        bst->right = insert_to_BST_leaf(bst->right,newPtr);
    }
    else {
        bst->left = insert_to_BST_leaf(bst->left, newPtr);
    }
  }
  return bst;
}

BST_TREE *generate_BST_by_insertion(BST_TREE *tree)
{
  T_NODE *newPtr, *savePtr;
  newPtr = tree->root->left;
  tree->root->left = NULL;

  if(tree->root != NULL) tree->count++;

  while(newPtr != NULL){
    tree->root = insert_to_BST_leaf(tree->root, newPtr);
    tree->count++;
    savePtr = newPtr;
    newPtr = newPtr->left;
    savePtr->left = NULL;
  }
  tree->level = find_tree_level(tree->root);
  return tree;
}

/////////////////////////////////////////////////////////////
// FILL 2: PRINT
/////////////////////////////////////////////////////////////
int print_LHBT(FILE *fp, T_NODE *lhbt)
  // prints left-half binary tree
  // ___-___-___
  // INPUT
  //   fp: file pointer for the output file, stdout for monitor output
  //   lhbt: left-half binary tree (right pointers are all null)
  // RETURNs number of NODES in the list
{
  int num_nodes;

  num_nodes=0;
  while ( lhbt ) {
    if ( lhbt->right != NULL ) {	// check if left-half
      fprintf(stderr,"Non-left-half binary tree for %s\n",__FUNCTION__);
      break;
    }
    else {
      fprintf(fp, "%s", getkey(lhbt));
      if ( lhbt->left != NULL ) fprintf(fp, "-");
    }
    num_nodes++;
    lhbt = lhbt->left;
  }

  fprintf(fp, "\n");	// change the line at the end

  return num_nodes;
}



void print_BST_sortedorder(FILE *fp, T_NODE* bst1, int level)
{
  if ( bst1 != NULL ) {
    level++;	// root node of the current subtree exists

    print_BST_sortedorder(fp, bst1->left,level);
    fprintf(fp, "%s ",getkey(bst1));
    print_BST_sortedorder(fp, bst1->right,level);

  }
  if ( level <= 1 ) fprintf(fp, "\n");
}

void print_BST_right_center_left(FILE *fp, T_NODE *bst1, int level)
{
  int i;	// to count the number of nodes
  if ( bst1 != NULL ) {
    level++;	// root node of the current subtree exists
    print_BST_right_center_left(fp, bst1->right,level);
    for(i=0;i<level-1;i++) fprintf(fp,"    ");
    fprintf(fp, "%s\n",getkey(bst1));
    print_BST_right_center_left(fp, bst1->left,level);
  }
}



void print_BST_1(FILE *fp, T_NODE *bst, int level)
{
  int i;
  fprintf(fp, "%s",getkey(bst));
  if(bst->right == NULL) fprintf(fp, "\n");
  else{
    fprintf(fp,"/"); level++;
    print_BST_1(fp,bst->right,level);
  }

  if(bst->left != NULL){
    if(bst->right == NULL) level++;
    for(i=0;i<level-1;i++){
        fprintf(fp, "    ");
    }
    fprintf(fp, "   +");
    print_BST_1(fp,bst->left,level);
    }
}


void print_BST_2(FILE *fp, T_NODE *bst, int level, int stack[])
{
  int i;

  if(bst->left != NULL && bst->right != NULL){
    if(bst->right->right != NULL || bst->right->left != NULL){
        *(stack+level) = 1;
    }
    else *(stack+level) = 0;
  }
  else *(stack+level) = 0;

  fprintf(fp, "%s",getkey(bst));

  if(bst->right == NULL) fprintf(fp, "\n");
  else{
    fprintf(fp,"/"); level++;
    print_BST_2(fp,bst->right,level,stack);
  }

  if(bst->left != NULL){
    if(bst->right == NULL) level++;
    for(i=0;i<level-1;i++){
        if(stack[i] == 1) fprintf(fp,"   |");
        else fprintf(fp,"    ");

    }
    fprintf(fp, "   +");
    *(stack+level-1) = 0;
    print_BST_2(fp,bst->left,level,stack);
  }
}


/////////////////////////////////////////////////////////////
// FILL 3: Conversion of an BST to a complete BST
/////////////////////////////////////////////////////////////
T_NODE* add_to_llist(T_NODE* root, T_NODE* llist)
{
    if(!llist) llist = root;
    else {llist->right = root;
        root->left = llist;
        llist = llist->right;
        }
    return llist;
}

T_NODE* flatten_bst(T_NODE* root, T_NODE* llist)
{
    T_NODE *cur, *pre;

    if (root == NULL) return NULL;
    cur = root;

    while (cur!= NULL) {
        if (cur->left == NULL) {
            llist = add_to_llist(cur, llist);
            cur = cur->right;
        }
        else {
            pre = cur->left;
            while (pre->right != NULL && pre->right != cur)
                pre = pre->right;

            if (pre->right == NULL) {
                pre->right = cur;
                cur = cur->left;
            }
            else {
                pre->right = NULL;
                llist = add_to_llist(cur, llist);
                cur = cur->right;
            }
        }
    }
    return llist;
}

T_NODE* pop_from_llist(T_NODE** llist)
{
    T_NODE* tmp = *llist;
    *llist = (*llist)->left;
    tmp->left = NULL;

    return tmp;
}

T_NODE *BST_to_completeBST(T_NODE *bst, int numElements, T_NODE** llist)
{
    if(numElements <= 0) return NULL;

    T_NODE* right = BST_to_completeBST(bst, numElements/2, llist);

    if(llist){
        bst = pop_from_llist(llist);
        bst->right = right;
        bst->left = BST_to_completeBST(bst, numElements - numElements/2 -1, llist);
    }
    return bst;
}

void *insert_left_node_to_bst(T_NODE *root, T_NODE *newPtr)
{
  if(root){
        if(root->left == NULL) root->left = newPtr;
        else{
            insert_left_node_to_bst(root->left, newPtr);
        }
  }
}
/////////////////////////////////////////////////////////////
// FILL 4: generate binary search tree from a left-half binary tree
// using quick sort
/////////////////////////////////////////////////////////////

T_NODE *generate_BST_quicksort_basic(T_NODE *lhbt)
  // gerate a BST using quick sort algorithm
  // the resultant tree should be identical to generate_BST_by_insertion
{
    T_NODE* newPtr, *savePtr;
    T_NODE* root = lhbt;

    if(!root) {return root;}
    newPtr = root->left;
    if(!newPtr)
    {
        root->left = NULL;
        return root;
    }
    root->left = NULL;

    while(newPtr != NULL){
        if(comparekey(root, newPtr) < 0 ){
            if(root->right == NULL){
                    root->right = newPtr;}
            else{
                insert_left_node_to_bst(root->right,newPtr);
            }
        }
        else{
            insert_left_node_to_bst(root, newPtr);

        }

        savePtr = newPtr;
        newPtr = newPtr->left;
        savePtr->left = NULL;
    }

    root->left = generate_BST_quicksort_basic(root->left);
    root->right = generate_BST_quicksort_basic(root->right);
    return root;
}
/*
T_NODE *generate_BST_quicksort_advanced(T_NODE *lhbt)
  // gerate a BST using quick sort algorithm
  // the resultant tree should be identical to generate_BST_by_insertion
{
    T_NODE* newPtr, *savePtr;
    T_NODE* root = lhbt;
    if(!root) {return root;}
    newPtr = root->left;
    if(!newPtr)
    {
        root->left = NULL;
        return root;
    }
    root->left = NULL;

    while(newPtr != NULL){
        if(comparekey(root, newPtr) < 0 ){
            if(root->right == NULL){
                    root->right = newPtr;}
            else{
                insert_left_node_to_bst(root->right,newPtr);
            }
        }
        else{
            insert_left_node_to_bst(root, newPtr);

        }
        savePtr = newPtr;
        newPtr = newPtr->left;
        savePtr->left = NULL;
    }
    root->left = generate_BST_quicksort_basic(root->left);
    root->right = generate_BST_quicksort_basic(root->right);

    return root;
}
T_NODE* search_lhbt_index(T_NODE* lhbt, int index)
{
    if(index == 0) return lhbt;
    T_NODE* tmp;
    while( index != 0)
    {
        tmp = lhbt;
        lhbt = lhbt->left;
    }

    return tmp;
}*/

/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
#define MAXLINE	1024
int main()
{

  BST_TREE *tree, *insertion_tree, *quicksort_tree, *dup_tree;
  tree = create_bst_tree();
  int numWords;
  int numNodes;
  T_NODE *root, *bst1, *bst2, *dup;

  /* for file name, max length 1023 including path */
  char line[MAXLINE];
  char infile[MAXLINE], outfile[MAXLINE];
  FILE *fp;

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  /* input file name given by keyboard */
  memset(line,0,sizeof(char)*MAXLINE);	// clear the buffer
  fprintf(stderr,"Input file name? ");
  fgets(line,MAXLINE,stdin);
  if ( strlen(line) == 0 || sscanf(line,"%s",infile) != 1 ) {
    fprintf(stderr,"cannot read input file name from '%s'\n",line);
    exit(0);
  }

  /* output file name: enter for standard out */
  memset(line,0,sizeof(char)*MAXLINE);	// clear the buffer
  fprintf(stderr,"Output file name? ");
  fgets(line,MAXLINE,stdin);
  if ( strlen(line) == 0 || sscanf(line,"%s",outfile) != 1 ) {
    fprintf(stderr,"cannot read output file name from '%s'\n",line);
    fprintf(stderr,"output to stdout\n");
    fp = stdout;
    memset(outfile,0,sizeof(char)*MAXLINE);	// clear the buffer
  }
  else {
    /* open output file pointer */
    fp = fopen(outfile,"w");
    if ( fp == NULL ) {
      fprintf(stderr, "cannot open file '%s' for write\n",outfile);
      fprintf(stderr,"output to stdout\n");
      fp = stdout;
    }
  }

  /* read text file of integers:
   * number_of_intergers integer1 integer2 ...
   * then convert it to a linked list */
  tree = readkeys_textfile_LHBT(infile, &numWords);
  /*numNodes = print_LHBT(fp,tree->root);*/
  tree->level = find_tree_level(tree->root);
#ifdef MEASURE_TIME
  start = clock();
#endif
  if ( tree->root != NULL ) {

    // prints input
    fprintf(fp,"=====================================\n");
    numNodes = print_LHBT(fp, tree->root);
    fprintf(fp,"total %d nodes\n",numNodes);

    // BST construction by simple insertion
    // keep root unchanged
    dup_tree = create_bst_tree();
    dup_tree->root = copy_bt_recursive(tree->root);
    //dup_tree->level = find_tree_level(dup_tree);

    insertion_tree = generate_BST_by_insertion(dup_tree);

    fprintf(fp,"=====================================\n");
    print_BST_sortedorder(fp,insertion_tree->root,0);
    fprintf(fp,"total %d nodes (sorted)\n",insertion_tree->count);
    fprintf(fp,"=====================================\n");
    print_BST_right_center_left(fp,insertion_tree->root,0);
    fprintf(fp,"BST height %d\n",insertion_tree->level);
    fprintf(fp,"=====================================\n");
    print_BST_1(fp,insertion_tree->root,0);
    fprintf(fp,"BST height %d\n",insertion_tree->level);
    fprintf(fp,"=====================================\n");

    int stack[numNodes];

    print_BST_2(fp,insertion_tree->root,0,stack);
    fprintf(fp,"BST height %d\n",insertion_tree->level);
    fprintf(fp,"=====================================\n");

    BST_TREE* complete_tree = create_bst_tree();

    T_NODE* last = NULL;
    last = flatten_bst(insertion_tree->root,last);

    complete_tree->root = BST_to_completeBST(complete_tree->root, numNodes,&(last));

   // stack = (int*)malloc(sizeof(int*)*numNodes);


    print_BST_2(fp,complete_tree->root,0,stack);
   // free(stack);
    complete_tree->level = find_tree_level(complete_tree->root);
    complete_tree->count = find_tree_count(complete_tree->root, 0);

    fprintf(fp,"Complete BST height %d\n",complete_tree->level);
    fprintf(fp,"=====================================\n");
    // BST using quick sort, pivot as left, basic

    dup_tree = create_bst_tree();
    dup_tree->root = copy_bt_recursive(tree->root);

    quicksort_tree = create_bst_tree();
    quicksort_tree->root = generate_BST_quicksort_basic(dup_tree->root);
    print_BST_2(fp,quicksort_tree->root,0,stack);

    quicksort_tree->count = find_tree_count(quicksort_tree->root, 0);
    quicksort_tree->level = find_tree_level(quicksort_tree->root);
    fprintf(fp,"BST by QUICKSORT, height %d\n",quicksort_tree->level);
    fprintf(fp,"=====================================\n");
/*
    dup_tree = create_bst_tree();
    dup_tree->root = copy_bt_recursive(tree->root);

    // BST using quick sort, advanced, to reduce height
   quicksort_tree->root = generate_BST_quicksort_advanced(dup_tree->root,numNodes);
    print_BST_2(fp,bst2,0,stack);

    quicksort_tree->count = tree->count;
    quicksort_tree->level = find_tree_level(quicksort_tree->root);
    fprintf(fp,"BST by QUICKSORT (advanced), height %d\n",quicksort_tree->level);
    fprintf(fp,"=====================================\n");
*/
    free_bt_recursive(tree->root);
    free_bt_recursive(complete_tree->root);
    free_bt_recursive(quicksort_tree->root);
    free(tree);
    free(insertion_tree);
    free(quicksort_tree);
    free(dup_tree);
    free(complete_tree);
  }

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(fp,"TIME %.5f seconds\n",cpu_time_used);
#endif

  if ( fp != NULL && fp != stdout ) fclose(fp);
  return 0;
}


/////////////////////////////////////////////////////////////
// implementation: functions for binary tree node
/////////////////////////////////////////////////////////////

const char* getkey(T_NODE *a)
{
  int i;
  for (i=0; i<BULK_SIZE-KEYLENGTH; i++) {
    if ( a->bulk[i] != '\0' ) return a->bulk+i;
  }
  return NULL;	// not found
}

int setkey(T_NODE *a, const char kw[])
{
  int pos;
  if ( a != NULL ) {
    // fill with 0
    memset(a->bulk,0,sizeof(char)*BULK_SIZE);

    // find position randomly to store KEYLENGTH+1 characters
    pos = rand()%(BULK_SIZE-KEYLENGTH);
    if ( kw != NULL ) memcpy(a->bulk+pos,kw,sizeof(char)*KEYLENGTH);
    a->bulk[pos+KEYLENGTH] = '\0';	// to make it a C string

    // success
    return 1;
  }
  else return 0;
}

T_NODE *generate_btnode(const char kw[])
{
  T_NODE *tmp;

  tmp = (T_NODE*)malloc(sizeof(T_NODE));
  setkey(tmp,kw);

  // initial left and right children for the generated leaf node
  tmp->left = tmp->right = NULL;

  return tmp;
}

void free_bt_recursive (T_NODE *bt)
{
  if ( bt!= NULL ) {
    free_bt_recursive(bt->left);
    free_bt_recursive(bt->right);
    free(bt);
  }
}

T_NODE *copy_bt_recursive (T_NODE *root)
{
  T_NODE *dup;

  if ( root != NULL ) {
    dup = (T_NODE*)malloc(sizeof(T_NODE));
    copykey(dup,root);
    dup->left = copy_bt_recursive(root->left);
    dup->right = copy_bt_recursive(root->right);
  }
  else dup = NULL;
  return dup;
}

T_NODE *insert_left_bcnode(T_NODE *parent, T_NODE *newPtr)
{
  if ( parent == NULL ) return newPtr;	// no parent
  else if ( newPtr == NULL ) return parent;	// Nothing to add
  else if ( newPtr->left != NULL ) {
    fprintf(stderr,"cannot add a node with non-null left tree\n");
    return parent;
  }
  else {
    newPtr->left = parent->left;
    parent->left=newPtr;
    return newPtr;	// returning new node as a new parent
  }
}

// static: internal use only
static int _compare_n_char(const char a[], const char b[], int L)
{
  int i;
  for (i=0; i<L; i++) {
    if ( a[i] < b[i] ) return -1;
    else if ( a[i] > b[i] ) return 1;
    else continue;	// to next character
  }
  return 0;
}

int comparekey(T_NODE *a, T_NODE *b)
{
  return _compare_n_char(getkey(a),getkey(b), KEYLENGTH);
}

/////////////////////////////////////////////////////////////
// File I/O
/////////////////////////////////////////////////////////////
BST_TREE *readkeys_textfile_LHBT( const char infile[], int *pN )
  // read key words from the given file
  // and generate a binary tree which is skewed to the left
  // (all right children are NULL)
{
  BST_TREE* make_tree = create_bst_tree();
  T_NODE *cur, *tmp;
  char word[1024];
  FILE *fp;
  int i;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }

  // check for number of keys
  if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
    fprintf(stderr, "File %s: ",infile);
    fprintf(stderr, "number of keys cannot be read or or wrong\n");
    fclose(fp);
    return NULL;
  }

  /*
  // check for number of characters per key
  if ( fscanf(fp, "%d", pL) != 1 || *pL <= 0 ) {
    fprintf(stderr, "File %s: ",infile);
    fprintf(stderr, "number of characters per key cannot be read or or wrong\n");
    fclose(fp);
    return NULL;
  }
  */

  // reading keys
  make_tree->root = cur = tmp = NULL;

  for (i=0; i<(*pN); i++) {
    if ( fscanf(fp, "%s", word) != 1 ) {
      fprintf(stderr, "cannot read a word at %d/%d\n",i+1,(*pN));
      *pN = i;	// number of read keys so far
      break;
    }
    else {
      //check_and_correct_word(word, KEYLENGTH);

      // generate a new node
      tmp = generate_btnode(word);

      if ( make_tree->root == NULL ){make_tree->root = cur = tmp;}
      else{ cur = insert_left_bcnode(cur,tmp);}

      make_tree->count++;
    }
  }

  return make_tree;
}


