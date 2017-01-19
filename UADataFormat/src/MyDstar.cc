#include "UATree/UADataFormat/interface/MyDstar.h"
#include <iostream>

using namespace std;

ClassImp(MyDstar)

MyDstar::MyDstar():MyPart(){
  this->Reset();
}

MyDstar::~MyDstar(){}

void MyDstar::Reset() {
  ntracksDstar = 0;
  ntracksD0Kpi = 0; 
  D0_VtxProb = -999.; 
  D0pt = -999.; 
  Dspt = -999.; 
  D0eta = -999.; 
  Dseta = -999.; 
  D0phi = -999.; 
  Dsphi = -999.; 
  D0_VtxPosx = -999.; 
  D0_VtxPosy = -999.; 
  D0_VtxPosz = -999.; 
  D0_Vtxerrx = -999.; 
  D0_Vtxerry = -999.; 
  D0_Vtxerrz = -999.; 
  TrkKdxy = -999.;
  Dsmass = -999.; 
  Trkpidxy = -999.; 
  TrkSdxy = -999.; 
  TrkKdz = -999.; 
  Trkpidz = -999.; 
  TrkSdz = -999.; 
  TrkKnhits = -999.; 
  Trkpinhits = -999.; 
  TrkSnhits = -999.; 
  TrkKchi2 = -999.; 
  Trkpichi2 = -999.; 
  TrkSchi2 = -999.; 
  DSDeltaR = -999.; 
  TrkKpt = -999.; 
  Trkpipt = -999.;
  D0mass = -999.; 
  TrkSpt = -999.; 
  TrkKeta = -999.; 
  Trkpieta = -999.; 
  TrkSeta = -999.; 
  TrkKphi = -999.; 
  Trkpiphi = -999.; 
  TrkSphi = -999.; 
  TrkScharge = -999.; 
  D0fromDSsXY_vec = -999.;

}

void MyDstar::Print() {
}
