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

 if(tree == NULL)return;

  TreeNode * aux = tree->root;
  TreeNode * nuevo = createTreeNode(key,value);

  while(aux != NULL)
  {
    nuevo->parent = aux;
    if(tree->lower_than(key, aux->pair->key))
    {
      aux = aux->left;
      
    }
    else if(tree->lower_than(aux->pair->key, key))
    {
      aux = aux->right;
    }
    else
    {
      return;
    }
  }

  if(nuevo->parent == NULL)
  {
    tree->root = nuevo;
    
  }else if(tree->lower_than(key, nuevo->parent->pair->key))
  {
    nuevo->parent->left= nuevo;
  }
  else
  {
    nuevo->parent->right = nuevo;
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
  if(tree == NULL)return;

  TreeNode * aux = node;

  if(aux->right == NULL || aux->left == NULL)
  {
    if(aux->right != NULL)
    {
      if(aux->parent->left == NULL) 
        aux->parent->right = aux->right;
      else 
        aux->parent->left = aux->right;
    }
    else
    {
      if(aux->parent->right == NULL) 
        aux->parent->left = aux->left;
      else 
        aux->parent->right = aux->left;
    }
  }
 
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
  if(tree == NULL)
    return NULL;
  TreeNode * aux = tree->root;
  TreeNode * nodo = tree->root;

   if(searchTreeMap(tree,key) != NULL)
   {
     return searchTreeMap(tree,key);
   } 
   else
   {
    while(aux != NULL)
    {
      if((nodo == NULL || (tree->lower_than(aux->pair->key, nodo->pair->key) == 1)) && (tree->lower_than(key, aux->pair->key) == 1))
      {
        nodo = aux;
      } 
      if(tree->lower_than(key, aux->pair->key) == 1)
      {
        aux = aux->left;
      }
      else
      {
        aux = aux->right;
      }
    }
    if(nodo == NULL)return NULL;
   }
  return nodo->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode * aux = minimum(tree->root);
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {

  TreeNode * actual = tree->current;
  TreeNode * aux = tree->current;
 if(tree == NULL)
  {
    return NULL;
  }
  if(actual->right != NULL)
  {
    actual = minimum(tree->current);
    tree->current = actual;
    return actual->pair;
  }
  else
  {
    while (aux->parent != NULL)
    {
      if(tree->lower_than(actual->pair->key,aux->parent->pair->key)==1)
      {
        tree->current = aux->parent;
        return aux->parent->pair;
      }
      else if(tree->lower_than(aux->parent->pair->key,actual->pair->key)==1)
      {
        aux = aux->parent;
      }
      else
      {
        return aux->pair;
      }
    }
  }
  return NULL;
}