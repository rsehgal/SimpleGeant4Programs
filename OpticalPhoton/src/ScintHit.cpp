/*
**	Filename : ScintHit.cpp
**	2022-10-11
**	username : rsehgal
*/
#include "ScintHit.h"
#include <iostream>

ScintHit::ScintHit() {}

G4ThreadLocal G4Allocator<ScintHit>* ScintHitAllocator=0;

void ScintHit::SetEDep(double edep) { fEDep = edep; }

double ScintHit::GetEDep() const { return fEDep; }
