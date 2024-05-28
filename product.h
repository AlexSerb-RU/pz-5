#pragma once
#include <windows.h>

struct product
{
   UINT key;
   const char *name;
   UCHAR cnt, cost;

   product( UINT _key = 0, const char *_name = "", UCHAR _cnt = 0, UCHAR _cost = 0 ) :
      key( _key ), name( _name ), cnt( _cnt ), cost( _cost ) { }
};