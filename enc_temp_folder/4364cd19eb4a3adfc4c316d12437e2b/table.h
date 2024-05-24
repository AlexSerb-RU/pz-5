#include <windows.h>

const UCHAR N = 40;
enum sortmode { QUICK, TREE, SHELL };
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
   price *p[N]{};

   inline bool IsFull( ) { return N == n; }
   inline bool IsEmpty( ) { return !n; }

   UCHAR Search( UINT key )
   {
      if ( IsEmpty( ) ) return 0;
      UCHAR m = 0, l = 0, r = n - 1;
      switch ( srchm )
      {
         case BINARY:
            m = (l + r) / 2;
            for ( ; l < r && key != p[m]->key; m = (l + r) / 2 )
               key >= p[m]->key ? l = m + 1 : r = m;
            /*for ( UCHAR b = 0 ; b < n && p[b]->key != key; ++b )
               m = b;*/
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
      memmove( &p[ind + 1], &p[ind], (N - ind) * sizeof( &p ) );
      p[ind] = r;
      n++;
      return 1;
   }
};

struct resault
{
   UINT key;
   const char *name;
   UCHAR cnt;

   resault( UINT _key = 0, const char *_name = "", UCHAR _cnt = 0 ) :
      key( _key ), name( _name ), cnt( _cnt ) {}
};

struct day
{
   UCHAR n = 0;
   sortmode srtm = QUICK; // sort mode
   searchmode srchm = LINEAR; // search mode
   resault *res[N]{ };

   inline bool IsFull( ) { return N == n; }
   inline bool IsEmpty( ) { return !n; }

   bool Search( UINT key, UCHAR *i )
   {
      if ( IsEmpty( ) ) return false;
      UCHAR m = 0, l = 0, r = n - 1;
      switch ( srchm )
      {
         case BINARY:
            /*m = (l + r) / 2;
            for ( UCHAR b = 0 ; b + 1 < n || res[b]->key == key; ++b )
               m = b;*/
            break;
         case LINEAR:
            for ( UCHAR b = 0 ; b + 1 < n && res[b]->key != key; ++b )
               m = b + 1;
      }
      *i = m + (res[m]->key < key);

      return res[m]->key == key;
   }

   UCHAR Add( resault *r, UCHAR ind )
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
            break;
         case SHELL:
            UCHAR l = 0;
            UCHAR *h = new UCHAR[29];
            for ( h[0] = 1; h[l] <= n / 9 ;
               l++, h[l] = 2 * h[l - 1] + 1 );
            for ( short m = l; m >= 0; m-- )
               for ( UCHAR k = 0; k < h[m]; k++ )
                  for ( UCHAR i = h[m] + k; i <= n - 1; i += h[m] )
                  {
                     short j = i - h[m];
                     while ( j >= 0 && res[i]->key > res[j]->key )
                     {
                        res[j + h[m]] = res[j];
                        j = j - h[m];
                     }
                     res[j + h[m]] = res[i];
                  }
      }
   }
};
