#include <stdio.h>
#include <locale.h>
#include "storage.h"
#include "price_list.h"
#include "tree.h"

#include <iostream>

const UCHAR name_w = 21;

void input( FILE *f, storage *d, price_list *p )
{
   if ( fopen_s( &f, "in.txt", "r" ) )
   {
      perror( "in.txt" );
      exit( EXIT_FAILURE );
   }

   // Search mod 0 - LINEAN, 1 - BINARY;
   fscanf_s( f, "%d%*c", &p->srchm );
   
   for ( ; !feof( f ) && fgetc( f ) != '\n'; )
   {
      fseek( f, -1, SEEK_CUR );
      UINT key = 0;
      UCHAR cost = 0;
      fscanf_s( f, "%x%hhu%*c", &key, &cost );
      p->Add( new price( key, cost ), p->Search( key ) );
   }

   // Sort mod 0 - QUICK, 1 - TREE, 2 - SHELL;
   fscanf_s( f, "%d", &d->srtm );

   for ( ; !feof( f ); )
   {
      UINT key = 0;
      const char *name = new char[name_w];
      UCHAR cnt = 0;
      fscanf_s( f, "%x%s%hhu", &key, name,
         sizeof( *name ) * name_w, &cnt );

      UCHAR i = 0;
      d->Search( key, &i ) ? d->res[i]->cnt += cnt :
         d->Add( new product( key, name, cnt ) );
   }
}

void output( FILE *f, storage *t )
{
   setlocale( 0, "" );
   fopen_s( &f, "out.txt", "w" );

   fprintf_s( f, "Таблица, отсортированная %s с помощью %s поиска: \n\n%-8s \t %-20s \t %s",
      t->srtm ? t->srtm - 1 ? "методом Шелла" : "с использованием структуры дерева" : "методом Qsort",
      /*t->srchm ?*/ "бинарного" /*: "последовательного"*/, "АРТИКУЛ", "НАИМЕНОВАНИЕ", "КОЛ-ВО" );
   for ( UINT i = 0; i < t->n ; i++ )
   {
      product *b = t->res[i];
      fprintf_s( f, "\n%08X \t %-20s \t %6hhu", b->key, b->name, b->cnt );
   }
}

int main( )
{
   tree t( 5 );
   storage *v = new storage;
   /*InsertTree( &t, 2 );
   InsertTree( &t, 1 );
   InsertTree( &t, 3 );*/
   /*t.Add( 2 );
   t.Add( 1 );
   t.Add( 3 );
   t.Add( 4 );
   t.Add( 6 );*/
   v->Add( new product( 5 ) );
   v->Add( new product( 2 ) );
   v->Add( new product( 3 ) );
   v->Add( new product( 1 ) );
   v->Add( new product( 7 ) );
   v->Add( new product( 6 ) );

   v->Sort( );
   std::cout << v->n;
   //WriteToTable( &t, v );
   //t.Search( 4, b );

   FILE *f = NULL;
   storage *s = new storage;
   price_list *p = new price_list;
   input( f, s, p );
   output( f, s );

   return 0;
}