#ifndef __MyD0_H__
#define __MyD0_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include <iostream>

using namespace std;

class MyD0 : public MyPart {
  
 public :
   MyD0();
  virtual ~MyD0();
  
  void Reset();
  void Print();

  Int_t ntracksDstar, ntracksD0Kpi;
  Float_t D0Kpi_VtxProb,D0Kpipt,D0Kpieta,D0Kpiphi,D0Kpi_VtxPosx,D0Kpi_VtxPosy,D0Kpi_VtxPosz,D0Kpi_Vtxerrx,D0Kpi_Vtxerry,D0Kpi_Vtxerrz,D0Kpi_DispAngle;
  Float_t D0Kpimass,TrkD0Keta,TrkD0pieta,TrkD0Kphi,TrkD0piphi;
  Float_t TrkD0Kdxy,TrkD0pidxy,TrkD0Kdz,TrkD0pidz,TrkD0Knhits,TrkD0pinhits,TrkD0Kchi2,TrkD0pichi2,D0DeltaR,TrkD0Kpt,TrkD0pipt,D0KpisXY_vec,D0KpikT;

 private:
  ClassDef (MyD0,1)
};

#endif
