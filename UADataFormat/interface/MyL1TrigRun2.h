#ifndef __MyL1TrigRun2_H__
#define __MyL1TrigRun2_H__

#include "TObject.h"
#include <map>

class MyL1TrigRun2 : public TObject {

public :
  MyL1TrigRun2();
  virtual ~MyL1TrigRun2();

//   bool PhysTrigWord[128];
//   bool TechTrigWord[64];

  void Reset();
  void Print();

  std::vector<bool> triggerResults;

private:

  ClassDef (MyL1TrigRun2,1)
};

#endif
