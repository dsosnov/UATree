#ifndef __MyTracks_H__
#define __MyTracks_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include <iostream>

using namespace std;

class MyTracks : public MyPart {

  public :
    MyTracks();
    virtual ~MyTracks();

    void Print();
    void Reset();

    Bool_t   quality[5];
    Int_t    trackAlgo;
    Int_t    nhit;
    Int_t    nValidPixelHits;
    Int_t    nValidStripHits;  //can also look individual layer but do it later if needed ...
    Int_t    nValidMuonCSCHits;
    Int_t    nValidMuonDTHits;
    Int_t    nValidMuonRPCHits;

    // JH 05-02-2016;
    Int_t    isLooper;
    
    
    Int_t    nValidTrackerHits(){return nValidPixelHits+nValidStripHits;                     };
    Int_t    nValidMuonHits   (){return nValidMuonCSCHits+nValidMuonDTHits+nValidMuonRPCHits;};

    Double_t chi2n;
    Double_t dz  , d0 ;
    Double_t edz , ed0 , ept ; 
    Double_t vx, vy, vz ;
    Double_t harmonic2_dEdx, p; 

    std::vector<Int_t>     vtxid;
    std::vector<Double_t>  vtxdxy  ;
    std::vector<Double_t>  vtxdz   ;

    // dEdx 
    std::vector<Float_t> hit_charge; 
    std::vector<Float_t> hit_pathlength; 
    std::vector<UInt_t> hit_detIds; 
    std::vector<Bool_t> hit_shapetest; 


  private:

  ClassDef (MyTracks,1)
};

#endif

