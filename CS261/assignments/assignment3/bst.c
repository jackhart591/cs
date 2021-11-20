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

struct bst {
  struct bst_node* root;
};

struct bst* bst_create() {
  struct bst* temp = malloc(sizeof(struct bst));
  temp->root = NULL;
}

void free_from_node(struct bst_node* node) {
  if (node->left != NULL) {
    free_from_node(node->left);
    node->left = NULL;
  }

  if (node->right != NULL) {
    free_from_node(node->right);
    node->right = NULL;
  }

  free(node);
}

void bst_free(struct bst* bst) {
  assert(bst != NULL);

  free_from_node(bst->root);
  bst->root = NULL;

  free(bst);
  bst = NULL;
}

int bst_size_from_node(struct bst_node* node) {
  int size = 1;

  if (node->left != NULL) {
    size += bst_size_from_node(node->left);
  }

  if (node->right != NULL) {
    size += bst_size_from_node(node->right);
  }

  if (node->left == NULL && node->right == NULL) {
    return 1;
  } else {
    return size;
  }
}

int bst_size(struct bst* bst) {
  assert(bst != NULL);

  return (bst_size_from_node(bst->root));
}

void bst_insert(struct bst* bst, int key, void* value) {
  assert(bst != NULL);

  struct bst_node* parent = NULL;
  struct bst_node* current = bst->root;

  // create the node and insert it into position
  struct bst_node* new_node = malloc(sizeof(struct bst_node));
  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  if (current == NULL) {
    bst->root = new_node;
    return;
  }

  while (current != NULL) { // find who the parent is going to be
    parent = current;
    if (current->key <= key) {
      current = current->right;
    } else {
      current = current->left;
    }
  }

  if (parent->key <= new_node->key) {
    parent->right = new_node;
  } else {
    parent->left = new_node;
  }
}

void bst_remove(struct bst* bst, int key) {
  struct bst_node* parent = NULL;
  struct bst_node* current = bst->root;

  while (current->key != key) { // Get key-value pair to remove
    if (current->key > key) {
      parent = current;
      current = current->left;
    } else {
      parent = current;
      current = current->right;
    }
  }

  if (current->left == NULL && current->right == NULL) { // if node is a leaf
    if (parent->left != NULL) {
      parent->left = NULL;
    } else {
      parent->right = NULL;
    }
    free(current);
    current = NULL;

  } else if (current->left == NULL || current->right == NULL) { // if it has one child
    if (current->left != NULL) {
      if (parent->left != NULL) {
        parent->left = current->left;
      } else {
        parent->right = current->left;
      }
    } else if (current->right != NULL) {
      if (parent->left != NULL) {
        parent->left = current->right;
      } else {
        parent->right = current->right;
      }
    }
    free(current);
    current = NULL;

  } else { // if it has two children
    struct bst_node* successor = current->right;
    struct bst_node* succ_parent = current;
    while (successor->left != NULL) { // find in-order successor
      succ_parent = successor; 
      successor = successor->left; 
    }

    if (parent != NULL) {
      if (parent->left != NULL && parent->left->key == current->key) { parent->left = successor; } 
      else { parent->right = successor; }
    } else if (bst->root->key == current->key) {
      bst->root = successor;
    }

    if (successor->right != NULL) { // update successor connections
      if (succ_parent->key == current->key) {
        succ_parent->right = successor->right;
      } else {
        succ_parent->left = successor->right;
      }
    } else if (succ_parent->key != current->key) {
      succ_parent->left = NULL;
    }

    if (succ_parent->key != current->key) {
      successor->right = current->right;
    }

    successor->left = current->left;

    free(current);
    current = NULL;
  }
}

void* bst_get(struct bst* bst, int key) {
  assert(bst != NULL);

  struct bst_node* current = bst->root;
  while (current != NULL && current->key != key) {
    if (current->key > key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if(current != NULL && current->key == key) {
    return current->value;
  } else { return NULL; }
}