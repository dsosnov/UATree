#ifndef __MyHFRecHit_H__
#define __MyHFRecHit_H__

#include "TObject.h"
#include <vector>

using namespace std;

class MyHFRecHit : public TObject {
  
 public :
    MyHFRecHit();
  virtual ~MyHFRecHit();
  
  virtual void Reset(){};
  virtual void Print();
  
  Double_t energy, time;
  Int_t mod, ieta, iphi, depth;

 private:
  
  ClassDef (MyHFRecHit,1)
};

#endif

