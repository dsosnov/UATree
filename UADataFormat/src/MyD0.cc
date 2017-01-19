#include "UATree/UADataFormat/interface/MyD0.h"
#include <iostream>

using namespace std;

ClassImp(MyD0)

MyD0::MyD0():MyPart(){
  this->Reset();
}

MyD0::~MyD0(){}

void MyD0::Reset() {
  ntracksDstar = 0;
  ntracksD0Kpi = 0;
  D0Kpi_VtxProb = -999.; 
  D0Kpipt = -999.; 
  D0Kpieta = -999.; 
  D0Kpiphi = -999.; 
  D0Kpi_VtxPosx = -999.; 
  D0Kpi_VtxPosy = -999.; 
  D0Kpi_VtxPosz = -999.; 
  D0Kpi_Vtxerrx = -999.; 
  D0Kpi_Vtxerry = -999.; 
  D0Kpi_Vtxerrz = -999.; 
  D0Kpi_DispAngle = -999.;
  D0Kpimass = -999.; 
  TrkD0Keta = -999.; 
  TrkD0pieta = -999.; 
  TrkD0Kphi = -999.; 
  TrkD0piphi = -999.;
  TrkD0Kdxy = -999.; 
  TrkD0pidxy = -999.; 
  TrkD0Kdz = -999.; 
  TrkD0pidz = -999.; 
  TrkD0Knhits = -999.; 
  TrkD0pinhits = -999.; 
  TrkD0Kchi2 = -999.; 
  TrkD0pichi2 = -999.; 
  D0DeltaR = -999.; 
  TrkD0Kpt = -999.; 
  TrkD0pipt = -999.; 
  D0KpisXY_vec = -999.;
  D0KpikT = -999.;
}

void MyD0::Print() {
  std::cout << "Here I am!" << std::endl;
}
