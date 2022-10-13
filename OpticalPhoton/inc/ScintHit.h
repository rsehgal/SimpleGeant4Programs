/*
**	Filename : ScintHit.h
**	2022-10-11
**	username : rsehgal
*/
#ifndef ScintHit_h
#define ScintHit_h

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class ScintHit : public G4VHit {
private:
  double fEDep;

public:
  ScintHit();
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
  double GetEDep() const;
  void SetEDep(double edep);
};

using ScintHitCollection = G4THitsCollection<ScintHit>;
extern G4ThreadLocal G4Allocator<ScintHit> *ScintHitAllocator;

inline void *ScintHit::operator new(size_t) {
  if (!ScintHitAllocator)
    ScintHitAllocator = new G4Allocator<ScintHit>;
  return (void *)ScintHitAllocator->MallocSingle();
}

inline void ScintHit::operator delete(void *aHit) { ScintHitAllocator->FreeSingle((ScintHit *)aHit); }

#endif
