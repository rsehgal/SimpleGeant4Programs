/*
 * MyHit.h
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#ifndef INC_MYHIT_H_
#define INC_MYHIT_H_

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "colors.h"
using Vec_t = G4ThreeVector;

class MyHit : public G4VHit {

private:
  Vec_t fPosition;
  Vec_t fRandomPos;
  G4String fName;
  G4String fProcessName;

public:
  MyHit();
  virtual ~MyHit();
  MyHit(const MyHit &right);
  const MyHit &operator=(const MyHit &right);
  int operator==(const MyHit &right) const;
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
  void Draw() const {}
  void Print() const {

    std::cout << "--------------------------------------" << std::endl;
    std::cout << BLUE;
    std::cout << "Position : " << fPosition << std::endl;
    std::cout << "Random Pos : " << fRandomPos << std::endl;
    std::cout << "Vol Name : " << fName << std::endl;
    std::cout << RESET;
    // std::cout << "Process Name : " << fProcessName << std::endl;
  }

  void SetName(G4String name) { fName = name; }

  G4String GetName() { return fName; }

  void SetPosition(Vec_t position) { fPosition = position; }
  void SetRandomPosition(Vec_t position) { fRandomPos = position; }

  Vec_t GetPosition() { return fPosition; }
  Vec_t GetRandomPosition() { return fRandomPos; }
  G4String GetProcessName() const { return fProcessName; }
  void SetProcessName(G4String processName) { fProcessName = processName; }
};

typedef G4THitsCollection<MyHit> MyHitsCollection;

// extern G4Allocator<MyHit> MyHitAllocator;
extern G4ThreadLocal G4Allocator<MyHit> *MyHitAllocator;

inline void *MyHit::operator new(size_t) {
  if (!MyHitAllocator)
    MyHitAllocator = new G4Allocator<MyHit>;
  return (void *)MyHitAllocator->MallocSingle();
}

inline void MyHit::operator delete(void *aHit) { MyHitAllocator->FreeSingle((MyHit *)aHit); }

#endif /* INC_MYHIT_H_ */
