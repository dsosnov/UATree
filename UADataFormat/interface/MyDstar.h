#ifndef __MyDstar_H__
#define __MyDstar_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include <iostream>

using namespace std;

class MyDstar : public MyPart {
  
 public :
   MyDstar();
  virtual ~MyDstar();
  
  void Reset();
  void Print();

  Int_t ntracksDstar, ntracksD0Kpi;
  Float_t D0_VtxProb,D0pt,Dspt,D0eta,Dseta,D0phi,Dsphi,D0_VtxPosx,D0_VtxPosy,D0_VtxPosz,D0_Vtxerrx,D0_Vtxerry,D0_Vtxerrz,TrkKdxy;
  Float_t Dsmass,Trkpidxy,TrkSdxy,TrkKdz,Trkpidz,TrkSdz,TrkKnhits,Trkpinhits,TrkSnhits,TrkKchi2,Trkpichi2,TrkSchi2,DSDeltaR,TrkKpt,Trkpipt;
  Float_t D0mass,TrkSpt,TrkKeta,Trkpieta,TrkSeta,TrkKphi,Trkpiphi,TrkSphi,TrkScharge,D0fromDSsXY_vec;


 private:
  ClassDef (MyDstar,1)
};

#endif
