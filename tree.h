#pragma once
#include "product.h"
//#include "storage.h"

struct tree
{
   product prod;
   tree *left, *right;

   void Add( product p )
   {
      tree *b = this;
      for ( tree *t = b ; t = p.key < t->prod.key ? t->left : t->right; b = t );
      if ( p.key < b->prod.key ) b->left = new tree( p );
      else b->right = new tree( p );
   }

   tree( product _prod = 0, tree *_left = NULL, tree *_right = NULL ) :
      prod( _prod ), left( _left ), right( _right ) { }
};