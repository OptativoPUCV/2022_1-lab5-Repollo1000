#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap *alrbol = (TreeMap *)malloc(sizeof(TreeMap));
  alrbol->root = NULL;
  alrbol->current = NULL;
  
  alrbol->lower_than = lower_than;
  return alrbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree->root == NULL)return;

  TreeNode * aux = tree->root;

  while(aux != NULL)
  {
    if(tree->lower_than(key, aux->pair->key))
    {
      aux = aux->left;
    }
    else if(tree->lower_than(aux->pair->key,key))
    {
      aux = aux->right;
      
    }
    else
    {
      return;
    }
  }
  TreeNode * nuevo = createTreeNode(key,value);
 //aux->left = n; n->parent = aux

  if(tree == NULL)
  {
    tree->root = nuevo;
    
  }else if(tree->lower_than(nuevo->pair->key,aux->pair->key))
  {
    aux->left= nuevo;
    nuevo->parent = aux;
    
  }
  else
  {
    aux->right = nuevo;
    nuevo->parent = aux;
  }
  tree->current = nuevo;

}

TreeNode * minimum(TreeNode * x){
  TreeNode * aux = x;
  while(aux!=NULL)
  {
    if(aux->left == NULL)
        return aux;
    aux = aux->left;
  }
  return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode* aux = tree->root;
  while(aux != NULL)
  {
    if(tree->lower_than(key , aux->pair->key)==1)
    {
      aux = aux->left;
    }
    else if(tree->lower_than(aux->pair->key,key)==1)
    {
      aux = aux->right;
    }
    else
    {
      tree->current = aux;
      return aux->pair;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode * aux = minimum(tree->root);
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode * aux = tree->current;

  if(aux->right != NULL)
  {
    aux = minimum(tree->current);
    tree->current = aux;
    return aux->pair;
    
  }
  else
  {
    while (aux != NULL)
    {
      if(tree->lower_than(aux->pair->key,aux->parent->pair->key))
      {
        aux = aux->parent;
        tree->current = aux;
        return aux->pair;
      }
      else if(is_equal(tree,aux->pair->key,aux->parent->pair->key))
      {
        aux = aux->parent;
      }
      else if(tree->lower_than(aux->parent->pair->key, aux->pair->key))
      {
        aux = aux->parent;
      }      
    }
  }
  return NULL;
}