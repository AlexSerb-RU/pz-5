#include <stdio.h>
#include <locale.h>
#include "table.h"
#include <iostream>

const UCHAR name_w = 21;

void input( FILE *f, day *d, price_list *p )
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
   fscanf_s( f, "%d", &d->srchm );

   for ( ; !feof( f ); )
   {
      UINT key = 0;
      const char *name = new char[name_w];
      UCHAR cnt = 0;
      fscanf_s( f, "%x%s%hhu", &key, name,
         sizeof( *name ) * name_w, &cnt );

      UCHAR i = 0;
      d->Search( key, &i ) ? d->res[i]->cnt += cnt :
         d->Add( new resault( key, name, cnt ), i );
   }
   std::cout << p->n << d->n;

}

void output( FILE *f, day *t )
{
   setlocale( 0, "" );
   fopen_s( &f, "out.txt", "w" );

   fprintf_s( f, "Таблица, отсортированная %s с помощью %s поиска: \n\n%-8s \t %-20s \t %s",
      t->srtm ? t->srtm - 1 ? "методом Шелла" : "с использованием структуры дерева" : "методом Qsort",
      t->srchm ? "бинарного" : "последовательного", "АРТИКУЛ", "НАИМЕНОВАНИЕ", "КОЛ-ВО" );
   for ( UINT i = 0; i < t->n ; i++ )
   {
      resault *b = t->res[i];
      fprintf_s( f, "\n%08X \t %-20s \t %6hhu", b->key, b->name, b->cnt );
   }
}

int main( )
{
   FILE *f = NULL;
   day *resaults = new day, *products = new day;
   price_list *prices = new price_list;
   input( f, resaults, prices );
   //t->Sort( );
   //products_create( ... );
   output( f, products );

   return 0;
}