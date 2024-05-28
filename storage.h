#pragma once
#include "product.h"
#include "tree.h"

const UCHAR Np = 40;
enum sortmode { QUICK, TREE, SHELL };

struct tree;
struct storage;

void TreeSort( storage *s );

struct storage
{
   UCHAR n = 0;
   sortmode srtm = TREE; // sort mode
   product *res[Np]{ };

   inline bool IsFull( ) { return Np == n; }
   inline bool IsEmpty( ) { return !n; }

   bool Search( UINT key, UCHAR *i )
   {
      if ( IsEmpty( ) ) return false;
      UCHAR b = 0;
      for ( ; b + 1 < n && res[b]->key != key; )
         b++;
      *i = b;
      return res[b]->key == key;
   }

   UCHAR Add( product *r )
   {
      if ( IsFull( ) ) return 0;
      res[n] = r;
      n++;
      return 1;
   }

   void Sort( )
   {
      switch ( srtm )
      {
         case QUICK:
            break;
         case TREE:
            TreeSort( this );
            break;
         case SHELL:
            UCHAR l = 0;
            UCHAR *gap = new UCHAR[29];
            for ( gap[l] = 0; gap[l] <= n / 9 ; l = l + 1, gap[l] = 3 * gap[l - 1] + 1 );
            for ( short m = l; m >= 0; m-- )
            {
               for ( int i = gap[m]; i < n; i += 1 )
               {
                  product *x = res[i];
                  short j = i;
                  for ( ; j >= gap[m] && res[j - gap[m]]->key > x->key; j -= gap[m] )
                     res[j] = res[j - gap[m]];
                  res[j] = x;
               }
            }
      }
   }
};

void WriteToTable( tree *t, storage **s )
{
   if ( t->left ) WriteToTable( t->left, s );
   //product *b = WriteToTable( t );
   (*s)->Add( &t->prod );
   if ( t->right ) WriteToTable( t->right, s );
}

void TreeSort( storage *s )
{
   tree t( *s->res[0] );
   for ( UCHAR i = 1; i < s->n; i++ )
      t.Add( *s->res[i] );
   storage *new_s = new storage;
   WriteToTable( &t, &new_s );
   *s = *new_s;
}


