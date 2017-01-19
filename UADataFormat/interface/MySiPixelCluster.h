#ifndef __MySiPixelCluster_H__
#define __MySiPixelCluster_H__

#include "TObject.h"

class MySiPixelCluster : public TObject {
  
 public :
   MySiPixelCluster();
  ~MySiPixelCluster();
  
  void Reset();
  void Print();
 
  Int_t size;
  Int_t sizeX;
  Int_t sizeY;
  Float_t x;
  Float_t y;
  Float_t z;
  Float_t charge;

 private:
  ClassDef (MySiPixelCluster,1)
};

#endif
