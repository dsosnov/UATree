#ifndef __MySiStripCluster_H__
#define __MySiStripCluster_H__

#include "TObject.h"

class MySiStripCluster : public TObject {
  
 public :
   MySiStripCluster();
  ~MySiStripCluster();
  
  void Reset();
  void Print();
 
  Int_t nStripClusters; 

 private:
  ClassDef (MySiStripCluster,1)
};

#endif
