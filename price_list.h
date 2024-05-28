#pragma once
#include <windows.h>

//const UCHAR Np = 40;
enum searchmode { LINEAR, BINARY };

struct price
{
   UINT key;
   UCHAR cost;

   price( UINT _key = 0, UCHAR _cost = 0 ) :
      key( _key ), cost( _cost ) {}
};

struct price_list
{
   UCHAR n = 0;
   searchmode srchm = LINEAR;
   price *p[40]{};

   inline bool IsFull( ) { return Np == n; }
   inline bool IsEmpty( ) { return !n; }

   UCHAR Search( UINT key )
   {
      if ( IsEmpty( ) ) return 0;
      UCHAR l = 0, r = n - 1, m = (l + r) / 2;
      switch ( srchm )
      {
         case BINARY:
            for ( ; l < r && key != p[m]->key; m = (l + r) / 2 )
               key >= p[m]->key ? l = m + 1 : r = m;
            break;
         case LINEAR:
            for ( UCHAR b = 0 ; b < n && p[b]->key < key; ++b )
               m = b;
      }
      return m + (p[m]->key < key);
   }

   UCHAR Add( price *r, UCHAR ind )
   {
      if ( IsFull( ) ) return 0;
      memmove( &p[ind + 1], &p[ind], (Np - ind) * sizeof( &p ) );
      p[ind] = r;
      n++;
      return 1;
   }
};
