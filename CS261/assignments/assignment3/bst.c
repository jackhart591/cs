/*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "bst.h"

struct bst_node
{
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst
{
  struct bst_node* root;
};

struct bst* bst_create() {
  struct bst* temp = malloc(sizeof(struct bst));
  temp->root = NULL;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */


void bst_free(struct bst* bst)
{

}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */

int bst_size(struct bst* bst)
{

}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void bst_insert(struct bst* bst, int key, void* value) {
  assert(bst != NULL);

  struct bst_node* parent = NULL;
  struct bst_node* current = bst->root;

  while (current != NULL) { // find who the parent is going to be
    parent = current;
    if (current->key <= key) {
      current = current->right;
    } else {
      current = current->left;
    }
  }

  // create the node and insert it into position
  struct bst_node* new_node = malloc(sizeof(struct bst_node));
  new_node->key = key;
  new_node->value = value;

  if (parent->key <= new_node->key) {
    parent->right = new_node;
  } else {
    parent->left = new_node;
  }
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */


void bst_remove(struct bst* bst, int key)
{

}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key)
{

}