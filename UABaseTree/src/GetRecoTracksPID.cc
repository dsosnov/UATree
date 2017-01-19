// Genaral Tracks and Vertex
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/src/Vertex.cc"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
//#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCPDeDxInfo.h" 
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/TrackReco/interface/DeDxHit.h"
#include "DataFormats/TrackReco/interface/DeDxHitInfo.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool TrackDebugPID = false;

void UABaseTree::GetRecoTracksPID(const edm::Event& iEvent, const string TrackCollName , vector<MyTracks>& TrackVector )
{
  //  using namespace susybsm; 
  
  TrackVector.clear(); 

  MyTracks mytrack;

  Handle<TrackCollection> tracks;
  iEvent.getByLabel(TrackCollName,tracks);

  // testing dEdx
  unsigned int iTrackCount = 0; 

  Handle<reco::DeDxHitInfoAss> dedxCollH;
  iEvent.getByLabel("hscpdedxHitInfo",dedxCollH);

 double scaleFactor=1.0; 
  //  bool usePixel=true; 

  bool useClusterCleaning=true; 
 
  std::vector<double> vect_scaledcharge; 
  std::vector<double> vect_charge; 
  std::vector<double> vect_pathlength; 
  std::vector<bool> vect_shapetest; 
  std::vector<uint32_t> vect_detIds; 
  // end JH

  // testing dE/dx
  for(TrackCollection::const_iterator tr = tracks->begin(); tr!=tracks->end(); ++tr){  
    reco::TrackRef trackref  = reco::TrackRef( tracks, iTrackCount ); 

    vect_scaledcharge.clear(); 
    vect_charge.clear(); 
    vect_pathlength.clear(); 
    vect_shapetest.clear(); 
    vect_detIds.clear(); 

    //    if(dEdxHitsH->isValid() && hscpHitsInfo.charges.size() > 0 && hscpHitsInfo.charges.size() < 999) 
    //    if(dEdxHitsH.isValid())
    const DeDxHitInfo* dEdxHitsH = NULL; 

    if(iTrackCount < dedxCollH->size())
      { 
	DeDxHitInfoRef dedxHitsRef = dedxCollH->get(trackref.key());  
	if(!dedxHitsRef.isNull()) 
	  {
	    dEdxHitsH = &(*dedxHitsRef); 
	    
	    for(unsigned int h=0;h<dEdxHitsH->size();h++){  
	      
	      DetId detid(dEdxHitsH->detId(h));  
	      
	      // Here we don't have the shapetest information in CMSSW_7X that was used in CMSSW_6X
	      //      if(!usePixel && detid.subdetId()<3){continue;} // skip pixels 
	      //          if((detid.subdetId()>=3) && (useClusterCleaning && !hscpHitsInfo.shapetest[h])){continue;} //skip strip hits failling the shape test. 
	      
	      // JH - new from Loic
	      bool shapetest = false;
	      if(useClusterCleaning && detid >= 3)
		{
		  shapetest = clusterCleaning(dEdxHitsH->stripCluster(h), 1);
		}
	      
	      double Norm = (detid.subdetId()<3)?3.61e-06:3.61e-06*265;  //compute the normalization factor to get the energy in MeV/cm 
	      Norm*=10.0; //mm --> cm 
	      
	      //save the dE/dx in MeV/cm to a vector.  The scalefactor can be used to correct for data/MC agreement. 
	      vect_scaledcharge.push_back(scaleFactor*Norm*dEdxHitsH->charge(h)/dEdxHitsH->pathlength(h));
	      vect_charge.push_back(dEdxHitsH->charge(h));  
	      vect_pathlength.push_back(dEdxHitsH->pathlength(h));  
	      vect_shapetest.push_back(shapetest);
	      vect_detIds.push_back(dEdxHitsH->detId(h));  
	      
	      //printf("%f ", Norm*hscpHitsInfo.charges[h]/hscpHitsInfo.pathlengths[h]); 
	    }
	  }
        else
	  {
	    std::cout << "\ttdedxHitsRef IS Null!!!!!!!!" << std::endl;
	    vect_scaledcharge.push_back(-999);
	    vect_charge.push_back(-999);
	    vect_pathlength.push_back(-999);
	    vect_shapetest.push_back(false);
	    vect_detIds.push_back(-999);
	  }
      } 
    else 
      { 
	std::cout << "\tInvalid dEdxHitInfo" << std::endl; 
      } 
    
    int size = vect_scaledcharge.size(); 
    
    double result=0; 
    
    //build the harmonic 2 dE/dx estimator 
    double expo = -2; 
    for(int i = 0; i< size; i ++){ 
      result+=pow(vect_scaledcharge[i],expo);  
    } 
    result = (size>0)?pow(result/size,1./expo):0.; 

    this->FillTrackPID(*tr , mytrack, result, vect_charge, vect_pathlength, vect_detIds, vect_shapetest); 
    TrackVector.push_back(mytrack);

    if(TrackDebugPID) mytrack.Print();

    // testing dE/dx
    vect_scaledcharge.clear(); 
    vect_charge.clear(); 
    vect_pathlength.clear(); 
    vect_shapetest.clear(); 
    vect_detIds.clear(); 
 
    iTrackCount++; 
  }
}


void UABaseTree::GetAllTracksPID( const edm::Event& iEvent ){
  for(vector<InputTag>::iterator icoll = tracksPID_.begin() ; icoll!= tracksPID_.end() ; ++icoll)
    this->GetRecoTracksPID(iEvent , icoll->label() , allTracksPID[icoll->label()] );
}

// JH - 15/02/2016, from Loic for new cluster shape
std::vector<int> UABaseTree::convert(const vector<unsigned char>& input)
{
  std::vector<int> output;
  for(unsigned int i=0;i<input.size();i++){
    output.push_back((int)input[i]);
  }
  return output;
}


std::vector<int> UABaseTree::CrossTalkInv(const std::vector<int>&  Q, const float x1, const float x2, bool way,float threshold,float thresholdSat) {
  const unsigned N=Q.size();
  std::vector<int> QII;
  std::vector<float> QI(N,0);
  Double_t a=1-2*x1-2*x2;
  //  bool debugbool=false;
  TMatrix A(N,N);

  //---  que pour 1 max bien net 
  if(Q.size()<2 || Q.size()>8){
    for (unsigned int i=0;i<Q.size();i++){
      QII.push_back((int) Q[i]);
    }
    return QII;
  }
  if(way){ 
    vector<int>::const_iterator mQ = max_element(Q.begin(), Q.end());
    if(*mQ>253){
      if(*mQ==255 && *(mQ-1)>253 && *(mQ+1)>253 ) return Q ;
      if(*(mQ-1)>thresholdSat && *(mQ+1)>thresholdSat && *(mQ-1)<254 && *(mQ+1)<254 &&  abs(*(mQ-1) - *(mQ+1)) < 40 ){
	QII.push_back((10*(*(mQ-1))+10*(*(mQ+1)))/2); return QII;}
    }
  }
  //---

  for(unsigned int i=0; i<N; i++) {
    A(i,i) =a;
    if(i<N-1){ A(i+1,i)=x1;A(i,i+1)=x1;}
    else continue; 
    if(i<N-2){ A(i+2,i)=x2;A(i,i+2)=x2;}
  }

  if(N==1) A(0,0)=1/a;
  else  A.InvertFast();

  for(unsigned int i=0; i<N; i++) {
    for(unsigned int j=0; j<N; j++) {
      QI[i]+=A(i,j)*(float)Q[j];
    }
  }

  for (unsigned int i=0;i<QI.size();i++){
    if(QI[i]<threshold) QI[i]=0; 
    QII.push_back((int) QI[i]);
  }

  return QII;
}


Bool_t UABaseTree::clusterCleaning(const SiStripCluster*   cluster,  int crosstalkInv, uint8_t* exitCode)
{
  if(!cluster) return true;
  vector<int>  ampls = convert(cluster->amplitudes());
  if(crosstalkInv==1)ampls = CrossTalkInv(ampls,0.10,0.04, true);
      

  // ----------------  COMPTAGE DU NOMBRE DE MAXIMA   --------------------------
  //----------------------------------------------------------------------------
  Int_t NofMax=0; Int_t recur255=1; Int_t recur254=1;
  bool MaxOnStart=false;bool MaxInMiddle=false, MaxOnEnd =false;
  Int_t MaxPos=0;
  // D	but avec max
  if(ampls.size()!=1 && ((ampls[0]>ampls[1])
			 || (ampls.size()>2 && ampls[0]==ampls[1] && ampls[1]>ampls[2] && ampls[0]!=254 && ampls[0]!=255) 
			 || (ampls.size()==2 && ampls[0]==ampls[1] && ampls[0]!=254 && ampls[0]!=255)) ){
    NofMax=NofMax+1;  MaxOnStart=true; }

  // Maximum entour	
  if(ampls.size()>2){
    for (unsigned int i =1; i < ampls.size()-1; i++) {
      if( (ampls[i]>ampls[i-1] && ampls[i]>ampls[i+1]) 
	  || (ampls.size()>3 && i>0 && i<ampls.size()-2 && ampls[i]==ampls[i+1] && ampls[i]>ampls[i-1] && ampls[i]>ampls[i+2] && ampls[i]!=254 && ampls[i]!=255) ){ 
	NofMax=NofMax+1; MaxInMiddle=true;  MaxPos=i; 
      }
      if(ampls[i]==255 && ampls[i]==ampls[i-1]) {
	recur255=recur255+1;
	MaxPos=i-(recur255/2);
	if(ampls[i]>ampls[i+1]){NofMax=NofMax+1;MaxInMiddle=true;}
      }
      if(ampls[i]==254 && ampls[i]==ampls[i-1]) {
	recur254=recur254+1;
	MaxPos=i-(recur254/2);
	if(ampls[i]>ampls[i+1]){NofMax=NofMax+1;MaxInMiddle=true;}
      }
    }
  }
  // Fin avec un max
  if(ampls.size()>1){
    if(ampls[ampls.size()-1]>ampls[ampls.size()-2]
       || (ampls.size()>2 && ampls[ampls.size()-1]==ampls[ampls.size()-2] && ampls[ampls.size()-2]>ampls[ampls.size()-3] ) 
       ||  ampls[ampls.size()-1]==255){
      NofMax=NofMax+1;  MaxOnEnd=true; }
  }
  // Si une seule strip touch	e
  if(ampls.size()==1){    NofMax=1;}



  // ---  SELECTION EN FONCTION DE LA FORME POUR LES MAXIMA UNIQUES ---------
  //------------------------------------------------------------------------
  //  
  //               ____
  //              |    |____
  //          ____|    |    |
  //         |    |    |    |____
  //     ____|    |    |    |    |
  //    |    |    |    |    |    |____
  //  __|____|____|____|____|____|____|__
  //    C_Mnn C_Mn C_M  C_D  C_Dn C_Dnn
  //  
  //   bool shapetest=true;
  bool shapecdtn=false;
  if (exitCode) *exitCode = 255;

  if(crosstalkInv==1){
    if(NofMax==1){shapecdtn=true; if (exitCode) *exitCode=0;}
    return shapecdtn;
  }

  //      Float_t C_M;    Float_t C_D;    Float_t C_Mn;   Float_t C_Dn;   Float_t C_Mnn;  Float_t C_Dnn;
  Float_t C_M=0.0;        Float_t C_D=0.0;        Float_t C_Mn=10000;     Float_t C_Dn=10000;     Float_t C_Mnn=10000;    Float_t C_Dnn=10000;
  Int_t CDPos;
  Float_t coeff1=1.7;     Float_t coeff2=2.0;
  Float_t coeffn=0.10;    Float_t coeffnn=0.02; Float_t noise=4.0;

  if(NofMax==1){

    if(MaxOnStart==true){
      C_M=(Float_t)ampls[0]; C_D=(Float_t)ampls[1];
      if(ampls.size()<3) shapecdtn=true ;
      else if(ampls.size()==3){C_Dn=(Float_t)ampls[2] ; if(C_Dn<=coeff1*coeffn*C_D+coeff2*coeffnn*C_M+2*noise || C_D==255) shapecdtn=true; else if (exitCode) *exitCode=2;}
      else if(ampls.size()>3){ C_Dn=(Float_t)ampls[2];  C_Dnn=(Float_t)ampls[3] ;
	if((C_Dn<=coeff1*coeffn*C_D+coeff2*coeffnn*C_M+2*noise || C_D==255)
	   && C_Dnn<=coeff1*coeffn*C_Dn+coeff2*coeffnn*C_D+2*noise){
	  shapecdtn=true;} else if (exitCode) *exitCode=3;
      }
    }

    if(MaxOnEnd==true){
      C_M=(Float_t)ampls[ampls.size()-1]; C_D=(Float_t)ampls[ampls.size()-2];
      if(ampls.size()<3) shapecdtn=true ;
      else if(ampls.size()==3){C_Dn=(Float_t)ampls[0] ; if(C_Dn<=coeff1*coeffn*C_D+coeff2*coeffnn*C_M+2*noise || C_D==255) shapecdtn=true; else if (exitCode) *exitCode=4;}
      else if(ampls.size()>3){C_Dn=(Float_t)ampls[ampls.size()-3] ; C_Dnn=(Float_t)ampls[ampls.size()-4] ; 
	if((C_Dn<=coeff1*coeffn*C_D+coeff2*coeffnn*C_M+2*noise || C_D==255)
	   && C_Dnn<=coeff1*coeffn*C_Dn+coeff2*coeffnn*C_D+2*noise){ 
	  shapecdtn=true;} else if (exitCode) *exitCode=5;
      }
    }

    if(MaxInMiddle==true){
      C_M=(Float_t)ampls[MaxPos];
      int LeftOfMaxPos=MaxPos-1;if(LeftOfMaxPos<=0)LeftOfMaxPos=0;
      int RightOfMaxPos=MaxPos+1;if(RightOfMaxPos>=(int)ampls.size())RightOfMaxPos=ampls.size()-1;
      //int after = RightOfMaxPos; int before = LeftOfMaxPos; if (after>=(int)ampls.size() ||  before<0)  std::cout<<"invalid read MaxPos:"<<MaxPos <<"size:"<<ampls.size() <<std::endl; 
      if(ampls[LeftOfMaxPos]<ampls[RightOfMaxPos]){ C_D=(Float_t)ampls[RightOfMaxPos]; C_Mn=(Float_t)ampls[LeftOfMaxPos];CDPos=RightOfMaxPos;} else{ C_D=(Float_t)ampls[LeftOfMaxPos]; C_Mn=(Float_t)ampls[RightOfMaxPos];CDPos=LeftOfMaxPos;}
      if(C_Mn<coeff1*coeffn*C_M+coeff2*coeffnn*C_D+2*noise || C_M==255){ 
	if(ampls.size()==3) shapecdtn=true ;
	else if(ampls.size()>3){
	  if(CDPos>MaxPos){
	    if(ampls.size()-CDPos-1==0){
	      C_Dn=0; C_Dnn=0;
	    }
	    if(ampls.size()-CDPos-1==1){
	      C_Dn=(Float_t)ampls[CDPos+1];
	      C_Dnn=0;
	    }
	    if(ampls.size()-CDPos-1>1){
	      C_Dn=(Float_t)ampls[CDPos+1];
	      C_Dnn=(Float_t)ampls[CDPos+2];
	    }
	    if(MaxPos>=2){
	      C_Mnn=(Float_t)ampls[MaxPos-2];
	    }
	    else if(MaxPos<2) C_Mnn=0;
	  }
	  if(CDPos<MaxPos){
	    if(CDPos==0){
	      C_Dn=0; C_Dnn=0;
	    }
	    if(CDPos==1){
	      C_Dn=(Float_t)ampls[0];
	      C_Dnn=0;
	    }
	    if(CDPos>1){
	      C_Dn=(Float_t)ampls[CDPos-1];
	      C_Dnn=(Float_t)ampls[CDPos-2];
	    }
	    if(ampls.size()-LeftOfMaxPos>1 && MaxPos+2<(int)(ampls.size())-1){
	      C_Mnn=(Float_t)ampls[MaxPos+2];
	    }else C_Mnn=0;                                                  
	  }
	  if((C_Dn<=coeff1*coeffn*C_D+coeff2*coeffnn*C_M+2*noise || C_D==255)
                                           && C_Mnn<=coeff1*coeffn*C_Mn+coeff2*coeffnn*C_M+2*noise
	     && C_Dnn<=coeff1*coeffn*C_Dn+coeff2*coeffnn*C_D+2*noise) {
	    shapecdtn=true;
	  }

	}
      } else if (exitCode) *exitCode=6;
    }
  }
  else if (NofMax>1 && exitCode) *exitCode = 1; // more than one maximum
  if(ampls.size()==1){shapecdtn=true;}
  if(shapecdtn && exitCode) *exitCode=0;

  return shapecdtn;
}

void UABaseTree::FillTrackPID(const Track& intrack , MyTracks& outtrack , Double_t dEdxEstimator, const vector<double>& hitcharge, const vector<double>& pathlength, const vector<unsigned int>& hitDetId, const vector<bool>& shapetest, Double_t mass){ 

  outtrack.Reset();

  outtrack.charge = intrack.charge();
  outtrack.SetPtEtaPhiM(intrack.pt(),intrack.eta(),intrack.phi(), mass );  
  outtrack.p = intrack.p(); 

  outtrack.nhit	              =  intrack.found() + intrack.lost();
  outtrack.nValidPixelHits    =  intrack.hitPattern().numberOfValidPixelHits  ();
  outtrack.nValidStripHits    =  intrack.hitPattern().numberOfValidStripHits  ();
  outtrack.nValidMuonCSCHits  =  intrack.hitPattern().numberOfValidMuonCSCHits();
  outtrack.nValidMuonDTHits   =  intrack.hitPattern().numberOfValidMuonDTHits ();
  outtrack.nValidMuonRPCHits  =  intrack.hitPattern().numberOfValidMuonRPCHits();
  
  outtrack.isLooper           =  intrack.isLooper();

  outtrack.chi2n   =  intrack.normalizedChi2();
  outtrack.dz	   =  intrack.dz();
  outtrack.d0	   =  intrack.d0();
  outtrack.edz	   =  intrack.dzError();
  outtrack.ed0	   =  intrack.d0Error();
  outtrack.ept	   =  intrack.ptError();

  outtrack.vx    =  intrack.referencePoint().x();
  outtrack.vy    =  intrack.referencePoint().y();
  outtrack.vz    =  intrack.referencePoint().z();

  outtrack.harmonic2_dEdx = dEdxEstimator; 

  outtrack.quality[0] = intrack.quality(TrackBase::qualityByName("loose"));
  outtrack.quality[1] = intrack.quality(TrackBase::qualityByName("tight"));
  outtrack.quality[2] = intrack.quality(TrackBase::qualityByName("highPurity"));
  outtrack.quality[3] = intrack.quality(TrackBase::qualityByName("confirmed"));
  outtrack.quality[4] = intrack.quality(TrackBase::qualityByName("goodIterative"));

  outtrack.trackAlgo = intrack.algo();

  // BeamSpot (id=0) and Vertex (id>0) Links
  outtrack.vtxid.clear();
  outtrack.vtxdxy.clear();
  outtrack.vtxdz.clear();

  for ( int i = 0 ; i != vtxid ; i++ ){
    outtrack.vtxid.push_back( i ); 
    outtrack.vtxdxy.push_back( intrack.dxy( vtxid_xyz[i] ) );
    outtrack.vtxdz.push_back(  intrack.dz( vtxid_xyz[i] )  );
  }

  // testing dE/dx
  int hitinfosize = hitcharge.size(); 
 
  for( int j = 0; j < hitinfosize; j++){ 
    outtrack.hit_charge.push_back( hitcharge[j] ); 
    outtrack.hit_pathlength.push_back( pathlength[j] ); 
    outtrack.hit_detIds.push_back( hitDetId[j] ); 
    outtrack.hit_shapetest.push_back( shapetest[j] ); 
  } 
}
