/*
**	Filename : CommonHelpers.cpp
**	2022-10-25
**	username : rsehgal
*/
#include <iostream>
#include "CommonHelpers.h"
#ifndef USHRT_MAX
#define USHRT_MAX 65535
#endif
unsigned int GetUnFoldedQNear(unsigned int qlong)
{
  return (qlong >> 16);
}
unsigned int GetUnFoldedQFar(unsigned int qlong)
{
  unsigned short int maxU_16bits = USHRT_MAX;
  //UInt_t maskingVal              = maxU_16bits;
  unsigned int maskingVal              = maxU_16bits;
  return (qlong & maskingVal);
}
