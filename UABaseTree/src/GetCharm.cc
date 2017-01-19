// Genaral Tracks and Vertex
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool CharmDebug = false;

void UABaseTree::GetAllCharm( const edm::Event& iEvent, const EventSetup& iSetup ){

  outd0.clear();
  outdstar.clear();

  double pi_mass=0.13957018; 
  double k_mass=0.493677;

  int ND0KpiCand, NKpiCand,Nd0Cand,NdsCand,ntracksDstar,ntracksD0Kpi;

  TLorentzVector vD0_1, vD0_2, vD0kaon, vD0pion;
  double mass1, mass2;
  bool comb1, comb2, combOR;

  std::vector<double> D0Kpi_VtxProb,D0Kpipt,D0Kpieta,D0Kpiphi,D0Kpi_VtxPosx,D0Kpi_VtxPosy,D0Kpi_VtxPosz,D0Kpi_Vtxerrx,D0Kpi_Vtxerry,D0Kpi_Vtxerrz,D0Kpi_DispAngle;
  std::vector<double> D0Kpimass,TrkD0Keta,TrkD0pieta,TrkD0Kphi,TrkD0piphi;
  std::vector<double> TrkD0Kdxy,TrkD0pidxy,TrkD0Kdz,TrkD0pidz,TrkD0Knhits,TrkD0pinhits,TrkD0Kchi2,TrkD0pichi2,D0DeltaR,TrkD0Kpt,TrkD0pipt,D0KpisXY_vec,D0Kpis3D_vec,D0_kT_vec;

  std::vector<double> D0_VtxProb,D0pt,Dspt,D0eta,Dseta,D0phi,Dsphi,D0_VtxPosx,D0_VtxPosy,D0_VtxPosz,D0_Vtxerrx,D0_Vtxerry,D0_Vtxerrz,TrkKdxy;
  std::vector<double> Dsmass,Trkpidxy,TrkSdxy,TrkKdz,Trkpidz,TrkSdz,TrkKnhits,Trkpinhits,TrkSnhits,TrkKchi2,Trkpichi2,TrkSchi2,DSDeltaR,TrkKpt,Trkpipt;
  std::vector<double> D0mass,TrkSpt,TrkKeta,Trkpieta,TrkSeta,TrkKphi,Trkpiphi,TrkSphi,TrkScharge,D0fromDSsXY_vec;

  TransientVertex v_D0;
  math::XYZTLorentzVector d0kpi_p4;

  std::vector<int> dScandsKpi;
  std::vector<reco::TransientTrack*> goodTracks;
  std::vector<reco::TransientTrack*>goodTracksD0;
  std::vector<reco::TransientTrack*> slowPiTracks;
  std::vector<reco::TransientTrack> t_tks;
  std::vector<reco::TransientTrack> tksD0;


  /*
   * Initialize
   */
  dScandsKpi.clear(); goodTracks.clear(); goodTracksD0.clear(); slowPiTracks.clear();
  NKpiCand=0; Nd0Cand=0; NdsCand=0; ND0KpiCand=0;
  ntracksDstar = -999; ntracksD0Kpi = -999;
  
  D0_VtxProb.clear(); D0mass.clear();Dsmass.clear();D0pt.clear();Dspt.clear();D0eta.clear();
  D0phi.clear();Dseta.clear();Dsphi.clear();D0_VtxPosx.clear();D0_VtxPosy.clear();D0_VtxPosz.clear();D0_Vtxerrx.clear(); D0_Vtxerry.clear();
  D0_Vtxerrz.clear();TrkKdxy.clear();Trkpidxy.clear();
  TrkSdxy.clear();TrkKdz.clear();Trkpidz.clear();TrkSdz.clear();
  TrkKnhits.clear();Trkpinhits.clear();TrkSnhits.clear();
  TrkKchi2.clear();Trkpichi2.clear();TrkSchi2.clear();
  DSDeltaR.clear();TrkKpt.clear();Trkpipt.clear();TrkSpt.clear();
  TrkKeta.clear();Trkpieta.clear();TrkSeta.clear();TrkKphi.clear();Trkpiphi.clear();TrkSphi.clear();TrkScharge.clear();
  D0fromDSsXY_vec.clear();

  D0_VtxProb.clear(); D0mass.clear();Dsmass.clear();D0pt.clear();Dspt.clear();D0eta.clear();
  D0phi.clear();Dseta.clear();Dsphi.clear();D0_VtxPosx.clear();D0_VtxPosy.clear();D0_VtxPosz.clear();D0_Vtxerrx.clear(); D0_Vtxerry.clear();
  D0_Vtxerrz.clear();TrkKdxy.clear();Trkpidxy.clear();
  TrkSdxy.clear();TrkKdz.clear();Trkpidz.clear();TrkSdz.clear();
  TrkKnhits.clear();Trkpinhits.clear();TrkSnhits.clear();
  TrkKchi2.clear();Trkpichi2.clear();TrkSchi2.clear();
  DSDeltaR.clear();TrkKpt.clear();Trkpipt.clear();TrkSpt.clear();
  TrkKeta.clear();Trkpieta.clear();TrkSeta.clear();TrkKphi.clear();Trkpiphi.clear();TrkSphi.clear();TrkScharge.clear();
  D0fromDSsXY_vec.clear();

  D0Kpi_VtxProb.clear();D0Kpimass.clear();D0Kpipt.clear();D0Kpieta.clear();
  D0Kpiphi.clear();D0Kpi_VtxPosx.clear();D0Kpi_VtxPosy.clear();
  D0Kpi_VtxPosz.clear();D0Kpi_Vtxerrx.clear();
  D0Kpi_Vtxerry.clear();D0Kpi_Vtxerrz.clear();
  D0Kpi_DispAngle.clear();TrkD0Kdxy.clear();
  TrkD0pidxy.clear();TrkD0Kdz.clear();
  TrkD0pidz.clear();TrkD0Knhits.clear();
  TrkD0pinhits.clear();TrkD0Kchi2.clear();TrkD0pichi2.clear();
  TrkD0Kpt.clear();TrkD0pipt.clear();TrkD0Keta.clear();
  TrkD0pieta.clear();TrkD0Kphi.clear();TrkD0piphi.clear();
  D0KpisXY_vec.clear();

  // Primary Vtx com muitos tra?os                                                                                                                                                       
  Handle<reco::VertexCollection> recVtxs;
  iEvent.getByLabel("offlinePrimaryVertices", recVtxs);

  size_t vtx_trk_size = (*recVtxs)[0].tracksSize();
  int VtxIn=0;
  for(size_t i = 0; i < recVtxs->size(); ++ i) {
    const Vertex &vtx = (*recVtxs)[i];
    if(vtx.tracksSize()>vtx_trk_size){
      VtxIn=i;
      vtx_trk_size=vtx.tracksSize();
    }
  }

  const Vertex& RecVtx = (*recVtxs)[VtxIn];

  Handle<TrackCollection> generalTracks;
  iEvent.getByLabel("generalTracks",generalTracks);

  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  t_tks = (*theB).build(generalTracks);
  
  // SELECTING TRACKS FOR DSTAR                                                                                                                                                          
  for(size_t i=0;i<t_tks.size();i++){
    TransientTrack t_trk = t_tks.at(i);
    if( fabs(t_trk.track().eta())<2.5 && fabs(t_trk.track().dxy(RecVtx.position()))<0.1 && fabs(t_trk.track().dz(RecVtx.position()))<1. &&
        t_trk.track().normalizedChi2() < 2.5 && t_trk.track().pt() > 0.15){
      slowPiTracks.push_back(&(t_tks.at(i)));
      if( (t_trk.track().numberOfValidHits() > 5) && (t_trk.track().pt() > 0.6) ){
	goodTracks.push_back(&(t_tks.at(i)));
      }
    }

    // SELECTING TRACKS FOR D0                                                                                                                                                             
    if(fabs(t_trk.track().eta())<2.5 && t_trk.track().normalizedChi2() < 5.0 && t_trk.track().numberOfValidHits() >= 5 && t_trk.track().pt() > 0.5
       && t_trk.track().p() >1.0 && fabs(t_trk.track().dz(RecVtx.position()))<0.5 && fabs(t_trk.track().dxy(RecVtx.position()))<0.1 ){
      
      goodTracksD0.push_back(&(t_tks.at(i)));      
    }
  }

  ntracksDstar = slowPiTracks.size();
  ntracksD0Kpi = goodTracksD0.size();

  /*
   * RecD0
   */
  for(size_t i=0;i<goodTracksD0.size();i++){

    TransientTrack* trk1D0 = goodTracksD0.at(i);

    for(size_t j=i+1;j<goodTracksD0.size();j++){

      TransientTrack* trk2D0 = goodTracksD0.at(j);
      //Testing charge and if tracks are equal                                                                          
      if(*trk1D0 == *trk2D0) continue;
      if(trk1D0->charge() == trk2D0->charge()) continue;
      //===============================================                                                                 
      math::XYZVector D0_p = trk1D0->track().momentum() + trk2D0->track().momentum();

      TransientTrack *KfromD0 = 0, *PifromD0 = 0;

      comb1 = comb2 = false ;
      mass1 = mass2 = 0 ;
      combOR = false;

      vD0kaon.SetPtEtaPhiM(trk1D0->track().pt(), trk1D0->track().eta(), trk1D0->track().phi(), k_mass);
      vD0pion.SetPtEtaPhiM(trk2D0->track().pt(), trk2D0->track().eta(), trk2D0->track().phi(), pi_mass);
      vD0_1 = vD0kaon + vD0kaon;
      mass1 = vD0_1.M() + vD0_1.M();

      vD0pion.SetPtEtaPhiM(trk1D0->track().pt(), trk1D0->track().eta(), trk1D0->track().phi(), pi_mass);
      vD0kaon.SetPtEtaPhiM(trk2D0->track().pt(), trk2D0->track().eta(), trk2D0->track().phi(), k_mass);
      vD0_2 = vD0kaon + vD0kaon;
      mass2 = vD0_2.M() + vD0_2.M();

      if( fabs(mass1-1.86484) < 1.0) comb1 = true;
      if( fabs(mass2-1.86484) < 1.0)  comb2 = true;

      //====================================                                                                            
      //If one of the conditions is satisfied                                                                           
      if(comb1 || comb2){

	if (comb1){
	  KfromD0 = trk1D0; PifromD0 = trk2D0;
	  math::XYZVector K_p = trk1D0->track().momentum();

	  vector<TransientTrack> tksD0;
	  tksD0.push_back(*KfromD0);
	  tksD0.push_back(*PifromD0);
	  KalmanVertexFitter kalman(true);
	  v_D0 = kalman.vertex(tksD0);
	  //TransientVertex v_D0 = kalman.vertex(tksD0);                                                            
	  if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
	  double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
	  TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
	  TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
	  //D0 Significance                                                                                         
	  VertexDistanceXY vD0KpidXY ;
	  double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
	  double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
	  double D0KpisXY = D0KpidXY / D0KpieXY;
	  //D0 significance 3D                                                                                      
	  VertexDistance3D vD0Kpid3D ;
	  double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
	  double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
	  double D0Kpis3D = D0Kpid3D / D0Kpie3D;

	  math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
	  math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
	  d0kpi_p4 = p4_KfromD0 + p4_pifromD0;

	  double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
	  double d0kpimass = d0kpi_p4.M();
	  if(fabs(d0kpimass - 1.86484)>0.15) continue;
	  ND0KpiCand++;

	  double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);

	  D0Kpi_VtxProb.push_back(D0KpivtxProb);
	  D0Kpimass.push_back(d0kpi_p4.M());
	  D0Kpipt.push_back(d0kpi_p4.Pt());
	  D0Kpieta.push_back(d0kpi_p4.eta());
	  D0Kpiphi.push_back(d0kpi_p4.phi());

	  D0Kpi_VtxPosx.push_back(v_D0.position().x());
	  D0Kpi_VtxPosy.push_back(v_D0.position().y());
	  D0Kpi_VtxPosz.push_back(v_D0.position().z());
	  D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
	  D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
	  D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
	  D0Kpi_DispAngle.push_back(dispAngle);
	  TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
	  TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

	  TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
	  TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());
	  TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
	  TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
	  TrkD0Kpt.push_back(KfromD0_f.track().pt());
	  TrkD0pipt.push_back(pifromD0_f.track().pt());

	  TrkD0Keta.push_back(KfromD0_f.track().eta());
	  TrkD0pieta.push_back(pifromD0_f.track().eta());
	  TrkD0Kphi.push_back(KfromD0_f.track().phi());
	  TrkD0piphi.push_back(pifromD0_f.track().phi());
	  D0KpisXY_vec.push_back(D0KpisXY);
	  D0Kpis3D_vec.push_back(D0Kpis3D);
	  D0_kT_vec.push_back(D0_kT);

	} // end of combination1                                                                          

	// -----                                                                                                  
	// end of comb1                                                                                                   

	if(comb2){

	  KfromD0 = trk2D0; PifromD0 = trk1D0;
	  math::XYZVector K_p = trk2D0->track().momentum();

	  vector<TransientTrack> tksD0;
	  tksD0.push_back(*KfromD0);
	  tksD0.push_back(*PifromD0);
	  KalmanVertexFitter kalman(true);
	  v_D0 = kalman.vertex(tksD0);


	  if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
	  double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
	  TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
	  TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
	  VertexDistanceXY vD0KpidXY ;
	  double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
	  double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
	  double D0KpisXY = D0KpidXY / D0KpieXY;
	  VertexDistance3D vD0Kpid3D ;
	  double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
	  double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
	  double D0Kpis3D = D0Kpid3D / D0Kpie3D;

	  math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
	  math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
	  d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
	  double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
	  double d0kpimass = d0kpi_p4.M();
	  if(fabs(d0kpimass - 1.86484)>0.15) continue;
	  ND0KpiCand++;

	  double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);

	  D0Kpi_VtxProb.push_back(D0KpivtxProb);
	  D0Kpimass.push_back(d0kpi_p4.M());
	  D0Kpipt.push_back(d0kpi_p4.Pt());
	  D0Kpieta.push_back(d0kpi_p4.eta());
	  D0Kpiphi.push_back(d0kpi_p4.phi());

	  D0Kpi_VtxPosx.push_back(v_D0.position().x());
	  D0Kpi_VtxPosy.push_back(v_D0.position().y());
	  D0Kpi_VtxPosz.push_back(v_D0.position().z());
	  D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
	  D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
	  D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
	  D0Kpi_DispAngle.push_back(dispAngle);
	  TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
	  TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

	  TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
	  TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());

	  TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
	  TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
	  TrkD0Kpt.push_back(KfromD0_f.track().pt());
	  TrkD0pipt.push_back(pifromD0_f.track().pt());
	  TrkD0Keta.push_back(KfromD0_f.track().eta());
	  TrkD0pieta.push_back(pifromD0_f.track().eta());
	  TrkD0Kphi.push_back(KfromD0_f.track().phi());
	  TrkD0piphi.push_back(pifromD0_f.track().phi());
	  D0KpisXY_vec.push_back(D0KpisXY);
	  D0Kpis3D_vec.push_back(D0Kpis3D);
	  D0_kT_vec.push_back(D0_kT);

	} // end of combination 2                                                                         

	combOR = true;
      } //end of comb1 OR comb 2                                                                                        

      //=============================                                                                                   
      //If both meet the requiremets                                                                                    
      if(comb1 && comb2 &! combOR){

	if(fabs( mass1-1.864 ) < fabs( mass2-1.864 )){

	  KfromD0 = trk1D0; PifromD0 = trk2D0;

	  math::XYZVector K_p = trk1D0->track().momentum();

	  vector<TransientTrack> tksD0;
	  tksD0.push_back(*KfromD0);
	  tksD0.push_back(*PifromD0);
	  KalmanVertexFitter kalman(true);
	  v_D0 = kalman.vertex(tksD0);

	  if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
	  double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
	  TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
	  TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
	  VertexDistanceXY vD0KpidXY ;
	  double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
	  double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
	  double D0KpisXY = D0KpidXY / D0KpieXY;
	  VertexDistance3D vD0Kpid3D ;
	  double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
	  double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
	  double D0Kpis3D = D0Kpid3D / D0Kpie3D;

	  math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
	  math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
	  d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
	  double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
	  double d0kpimass = d0kpi_p4.M();
	  if(fabs(d0kpimass - 1.86484)>0.15) continue;
	  ND0KpiCand++;

	  double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);
	  D0Kpi_VtxProb.push_back(D0KpivtxProb);
	  D0Kpimass.push_back(d0kpi_p4.M());
	  D0Kpipt.push_back(d0kpi_p4.Pt());
	  D0Kpieta.push_back(d0kpi_p4.eta());
	  D0Kpiphi.push_back(d0kpi_p4.phi());

	  D0Kpi_VtxPosx.push_back(v_D0.position().x());
	  D0Kpi_VtxPosy.push_back(v_D0.position().y());
	  D0Kpi_VtxPosz.push_back(v_D0.position().z());
	  D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
	  D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
	  D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
	  D0Kpi_DispAngle.push_back(dispAngle);
	  TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
	  TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

	  TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
	  TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());

	  TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
	  TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
	  TrkD0Kpt.push_back(KfromD0_f.track().pt());
	  TrkD0pipt.push_back(pifromD0_f.track().pt());

	  TrkD0Keta.push_back(KfromD0_f.track().eta());
	  TrkD0pieta.push_back(pifromD0_f.track().eta());
	  TrkD0Kphi.push_back(KfromD0_f.track().phi());
	  TrkD0piphi.push_back(pifromD0_f.track().phi());
	  D0KpisXY_vec.push_back(D0KpisXY);
	  D0Kpis3D_vec.push_back(D0Kpis3D);
	  D0_kT_vec.push_back(D0_kT);

	}

	if(fabs( mass2-1.864 ) < fabs( mass1-1.864 )){
	  KfromD0 = trk2D0; PifromD0 = trk1D0;

	  math::XYZVector K_p = trk2D0->track().momentum();

	  vector<TransientTrack> tksD0;
	  tksD0.push_back(*KfromD0);
	  tksD0.push_back(*PifromD0);
	  KalmanVertexFitter kalman(true);
	  v_D0 = kalman.vertex(tksD0);

	  if(!v_D0.isValid() || !v_D0.hasRefittedTracks()) continue;
	  double D0KpivtxProb =TMath::Prob( (Double_t) v_D0.totalChiSquared(), (Int_t) v_D0.degreesOfFreedom());
	  TransientTrack KfromD0_f = v_D0.refittedTrack(*KfromD0);
	  TransientTrack pifromD0_f = v_D0.refittedTrack(*PifromD0);
	  VertexDistanceXY vD0KpidXY ;
	  double D0KpidXY = vD0KpidXY.distance(RecVtx,v_D0).value() ;
	  double D0KpieXY = vD0KpidXY.distance(RecVtx,v_D0).error() ;
	  double D0KpisXY = D0KpidXY / D0KpieXY;
	  VertexDistance3D vD0Kpid3D ;
	  double D0Kpid3D = vD0Kpid3D.distance(RecVtx,v_D0).value() ;
	  double D0Kpie3D = vD0Kpid3D.distance(RecVtx,v_D0).error() ;
	  double D0Kpis3D = D0Kpid3D / D0Kpie3D;

	  math::XYZTLorentzVector p4_KfromD0(KfromD0_f.track().px(),KfromD0_f.track().py(),KfromD0_f.track().pz(),sqrt(pow(KfromD0_f.track().p(),2)+pow(k_mass,2)));
	  math::XYZTLorentzVector p4_pifromD0(pifromD0_f.track().px(),pifromD0_f.track().py(),pifromD0_f.track().pz(),sqrt(pow(pifromD0_f.track().p(),2)+pow(pi_mass,2)));
	  d0kpi_p4 = p4_KfromD0 + p4_pifromD0;
	  double D0_kT = sqrt(  (K_p).Cross(D0_p).Mag2() / D0_p .Mag2() ) ;
	  double d0kpimass = d0kpi_p4.M();
	  if(fabs(d0kpimass - 1.86484)>0.15) continue;
	  ND0KpiCand++;

	  double dispAngle = FindAngle(RecVtx,v_D0,d0kpi_p4);
	  D0Kpi_VtxProb.push_back(D0KpivtxProb);
	  D0Kpimass.push_back(d0kpi_p4.M());
	  D0Kpipt.push_back(d0kpi_p4.Pt());
	  D0Kpieta.push_back(d0kpi_p4.eta());
	  D0Kpiphi.push_back(d0kpi_p4.phi());

	  D0Kpi_VtxPosx.push_back(v_D0.position().x());
	  D0Kpi_VtxPosy.push_back(v_D0.position().y());
	  D0Kpi_VtxPosz.push_back(v_D0.position().z());
	  D0Kpi_Vtxerrx.push_back(v_D0.positionError().cxx());
	  D0Kpi_Vtxerry.push_back(v_D0.positionError().cyy());
	  D0Kpi_Vtxerrz.push_back(v_D0.positionError().czz());
	  D0Kpi_DispAngle.push_back(dispAngle);
	  TrkD0Kdxy.push_back(KfromD0_f.track().dxy(RecVtx.position()));
	  TrkD0pidxy.push_back(pifromD0_f.track().dxy(RecVtx.position()));

	  TrkD0Kdz.push_back(KfromD0_f.track().dz(RecVtx.position()));
	  TrkD0pidz.push_back(pifromD0_f.track().dz(RecVtx.position()));
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0Knhits.push_back(KfromD0->track().numberOfValidHits());
	  TrkD0pinhits.push_back(PifromD0->track().numberOfValidHits());

	  TrkD0Kchi2.push_back(KfromD0->track().normalizedChi2());
	  TrkD0pichi2.push_back(PifromD0->track().normalizedChi2());
	  TrkD0Kpt.push_back(KfromD0_f.track().pt());
	  TrkD0pipt.push_back(pifromD0_f.track().pt());

	  TrkD0Keta.push_back(KfromD0_f.track().eta());
	  TrkD0pieta.push_back(pifromD0_f.track().eta());
	  TrkD0Kphi.push_back(KfromD0_f.track().phi());
	  TrkD0piphi.push_back(pifromD0_f.track().phi());
	  D0KpisXY_vec.push_back(D0KpisXY);
	  D0Kpis3D_vec.push_back(D0Kpis3D);
	  D0_kT_vec.push_back(D0_kT);


	}

      }
      //end of comb1 AND comb 2                                                                                 
    }
  }

  /*
   * RecDstar
   */
  for(size_t i=0;i<goodTracks.size();i++){

    TransientTrack* trk1 = goodTracks.at(i);

    for(size_t j=i+1;j<goodTracks.size();j++){

      TransientTrack* trk2 = goodTracks.at(j);

      if(trk1->charge() == trk2->charge()) continue;

      math::XYZVector D0fromDstar_p = trk1->track().momentum() + trk2->track().momentum();

      if(sqrt(D0fromDstar_p.perp2()) < 3.) continue;

      for(size_t k=0;k<slowPiTracks.size();k++){

        TransientTrack* trkS = slowPiTracks.at(k);

        if(*trkS == *trk1 || *trkS == *trk2) continue;

	math::XYZVector DS_p = D0fromDstar_p + trkS->track().momentum();
        if(sqrt(DS_p.perp2())<4.) continue;

        TransientTrack *K=0,*pi=0;

	//COMBINACOES CORRETAS DE CARGAS                                                                                                                                        
        if(trk1->charge() == trkS->charge()){
          K = trk2;
          pi = trk1;
        }
        else{
          K = trk1;
          pi = trk2;
        }

        //Combina??es erradas dcarga - background                                                                                                                       
	/*                                                                                                                                                                      
        if(trk1->charge() == trkS->charge()){                                                                                                                           
          pi = trk2;                                                                                                                                                    
          K = trk1;                                                                                                                                                     
        }                                                                                                                                                               
        else{                                                                                                                                                           
          pi = trk1;                                                                                                                                                    
          K = trk2;                                                                                                                                                     
        }                                                                                                                                                               
	*/
	math::XYZTLorentzVector ip4_K(K->track().px(),K->track().py(),K->track().pz(),sqrt(pow(K->track().p(),2)+pow(k_mass,2)));
	math::XYZTLorentzVector ip4_pi(pi->track().px(),pi->track().py(),pi->track().pz(),sqrt(pow(pi->track().p(),2)+pow(pi_mass,2)));

	math::XYZTLorentzVector ip4_D0 = ip4_K + ip4_pi;

        if( fabs(ip4_D0.M()-1.86484)  > 1.) continue;

	math::XYZTLorentzVector p4_S(trkS->track().px(),trkS->track().py(),trkS->track().pz(),sqrt(pow(trkS->track().p(),2)+pow(pi_mass,2)));
	math::XYZTLorentzVector ip4_DS = ip4_D0 + p4_S;
        if((ip4_DS.M() - ip4_D0.M()) > 0.3) continue;

        // vertexing                                                                                                                                                    

        vector<TransientTrack> tks;
        tks.push_back(*K);
        tks.push_back(*pi);
        KalmanVertexFitter kalman(true);
        TransientVertex v = kalman.vertex(tks);
        if(!v.isValid() || !v.hasRefittedTracks()) continue;
        double vtxProb =TMath::Prob( (Double_t) v.totalChiSquared(), (Int_t) v.degreesOfFreedom());
        TransientTrack K_f = v.refittedTrack(*K);
        TransientTrack pi_f = v.refittedTrack(*pi);


        //D0 from D* Siginificance                                                                                                                                      
        VertexDistanceXY vD0fromDSdXY ;
        double D0fromDSdXY = vD0fromDSdXY.distance(RecVtx,v).value() ;
        double D0fromDSeXY = vD0fromDSdXY.distance(RecVtx,v).error() ;
        double D0fromDSsXY =  D0fromDSdXY / D0fromDSeXY;


	math::XYZTLorentzVector p4_K(K_f.track().px(),K_f.track().py(),K_f.track().pz(),sqrt(pow(K_f.track().p(),2)+pow(k_mass,2)));
	math::XYZTLorentzVector p4_pi(pi_f.track().px(),pi_f.track().py(),pi_f.track().pz(),sqrt(pow(pi_f.track().p(),2)+pow(pi_mass,2)));

	math::XYZTLorentzVector d0_p4 = p4_K + p4_pi;
        double d0mass = d0_p4.M();
        if(fabs(d0mass - 1.86484)>0.2) continue;
        Nd0Cand++;

	math::XYZTLorentzVector dS_p4 = d0_p4 + p4_S;
        double dsmass = dS_p4.M();
        if( (dsmass - d0mass) > 0.16) continue;
        NdsCand++;

        D0_VtxProb.push_back(vtxProb);
        D0mass.push_back(d0_p4.M());
        Dsmass.push_back(dS_p4.M());
        D0pt.push_back(d0_p4.Pt());
        Dspt.push_back(dS_p4.Pt());
        D0eta.push_back(d0_p4.eta());
        D0phi.push_back(d0_p4.phi());
        Dseta.push_back(dS_p4.eta());
        Dsphi.push_back(dS_p4.phi());

        D0_VtxPosx.push_back(v.position().x());
        D0_VtxPosy.push_back(v.position().y());
        D0_VtxPosz.push_back(v.position().z());
        D0_Vtxerrx.push_back(v.positionError().cxx());
        D0_Vtxerry.push_back(v.positionError().cyy());
        D0_Vtxerrz.push_back(v.positionError().czz());

        TrkKdxy.push_back(K_f.track().dxy(RecVtx.position()));
        Trkpidxy.push_back(pi_f.track().dxy(RecVtx.position()));
        TrkSdxy.push_back(trkS->track().dxy(RecVtx.position()));

        TrkKdz.push_back(K_f.track().dz(RecVtx.position()));
        Trkpidz.push_back(pi_f.track().dz(RecVtx.position()));
        TrkSdz.push_back(trkS->track().dz(RecVtx.position()));
        TrkKnhits.push_back(K->track().numberOfValidHits());
        Trkpinhits.push_back(pi->track().numberOfValidHits());
        TrkSnhits.push_back(trkS->track().numberOfValidHits());

        TrkKchi2.push_back(K->track().normalizedChi2());
        Trkpichi2.push_back(pi->track().normalizedChi2());
        TrkSchi2.push_back(trkS->track().normalizedChi2());

        DSDeltaR.push_back(deltaR(d0_p4.eta(),d0_p4.phi(),trkS->track().eta(),trkS->track().phi()));

        TrkKpt.push_back(K_f.track().pt());
        Trkpipt.push_back(pi_f.track().pt());
        TrkSpt.push_back(trkS->track().pt());

        TrkKeta.push_back(K_f.track().eta());
        Trkpieta.push_back(pi_f.track().eta());
        TrkSeta.push_back(trkS->track().eta());

        TrkKphi.push_back(K_f.track().phi());
        Trkpiphi.push_back(pi_f.track().phi());
        TrkSphi.push_back(trkS->track().phi());

        TrkScharge.push_back(trkS->charge());

        D0fromDSsXY_vec.push_back(D0fromDSsXY);

        NKpiCand++;

        if(NKpiCand>999) break;
      }
      if(NKpiCand>999) break;
    }
    if(NKpiCand>999) break;
  }

  /* 
   * Now fill UATree
   */
  outd0.assign( ND0KpiCand, MyD0() );

  for(Int_t iD0 = 0; iD0 < ND0KpiCand; iD0++)
    {
      outd0[iD0].D0Kpi_VtxProb = D0Kpi_VtxProb[iD0];
      outd0[iD0].D0Kpimass = D0Kpimass[iD0];

      outd0[iD0].D0Kpipt = D0Kpipt[iD0];
      outd0[iD0].D0Kpieta = D0Kpieta[iD0];
      outd0[iD0].D0Kpiphi = D0Kpiphi[iD0];

      outd0[iD0].D0Kpi_VtxPosx = D0Kpi_VtxPosx[iD0];
      outd0[iD0].D0Kpi_VtxPosy = D0Kpi_VtxPosy[iD0];
      outd0[iD0].D0Kpi_VtxPosz = D0Kpi_VtxPosz[iD0];
      outd0[iD0].D0Kpi_Vtxerrx = D0Kpi_Vtxerrx[iD0];
      outd0[iD0].D0Kpi_Vtxerry = D0Kpi_Vtxerry[iD0];
      outd0[iD0].D0Kpi_Vtxerrz = D0Kpi_Vtxerrz[iD0];
      outd0[iD0].D0Kpi_DispAngle = D0Kpi_DispAngle[iD0];
      outd0[iD0].TrkD0Kdxy = TrkD0Kdxy[iD0];
      outd0[iD0].TrkD0pidxy = TrkD0pidxy[iD0];

      outd0[iD0].TrkD0Kdz = TrkD0Kdz[iD0];
      outd0[iD0].TrkD0pidz = TrkD0pidz[iD0];

      outd0[iD0].TrkD0Knhits = TrkD0Knhits[iD0];
      outd0[iD0].TrkD0pinhits = TrkD0pinhits[iD0];

      outd0[iD0].TrkD0Kchi2 = TrkD0Kchi2[iD0];
      outd0[iD0].TrkD0pichi2 = TrkD0pichi2[iD0];

      outd0[iD0].TrkD0Kpt = TrkD0Kpt[iD0];
      outd0[iD0].TrkD0pipt = TrkD0pipt[iD0];

      outd0[iD0].TrkD0Keta = TrkD0Keta[iD0];

      outd0[iD0].TrkD0pieta = TrkD0pieta[iD0];
      outd0[iD0].TrkD0Kphi = TrkD0Kphi[iD0];
      outd0[iD0].TrkD0piphi = TrkD0piphi[iD0];
      outd0[iD0].D0KpisXY_vec = D0KpisXY_vec[iD0];
      outd0[iD0].D0KpikT = D0_kT_vec[iD0];

      outd0[iD0].ntracksDstar = ntracksDstar;
      outd0[iD0].ntracksD0Kpi = ntracksD0Kpi;      

      
    }

  outdstar.assign( NdsCand, MyDstar() );

  for(Int_t iDst = 0; iDst < NdsCand; iDst++)
    {
      outdstar[iDst].D0_VtxProb = D0_VtxProb[iDst];
      outdstar[iDst].D0mass = D0mass[iDst];
      outdstar[iDst].Dsmass = Dsmass[iDst];
      outdstar[iDst].D0pt = D0pt[iDst];
      outdstar[iDst].Dspt = Dspt[iDst];
      outdstar[iDst].D0eta = D0eta[iDst];
      outdstar[iDst].D0phi = D0phi[iDst];
      outdstar[iDst].Dseta = Dseta[iDst];
      outdstar[iDst].Dsphi = Dsphi[iDst];

      outdstar[iDst].D0_VtxPosx = D0_VtxPosx[iDst];
      outdstar[iDst].D0_VtxPosy = D0_VtxPosy[iDst];
      outdstar[iDst].D0_VtxPosz = D0_VtxPosz[iDst];
      outdstar[iDst].D0_Vtxerrx = D0_Vtxerrx[iDst];
      outdstar[iDst].D0_Vtxerry = D0_Vtxerry[iDst];
      outdstar[iDst].D0_Vtxerrz = D0_Vtxerrz[iDst];

      outdstar[iDst].TrkKdxy = TrkKdxy[iDst];
      outdstar[iDst].Trkpidxy = Trkpidxy[iDst];
      outdstar[iDst].TrkSdxy = TrkSdxy[iDst];

      outdstar[iDst].TrkKdz = TrkKdz[iDst];
      outdstar[iDst].Trkpidz = Trkpidz[iDst];
      outdstar[iDst].TrkSdz = TrkSdz[iDst];
      outdstar[iDst].TrkKnhits = TrkKnhits[iDst];
      outdstar[iDst].Trkpinhits = Trkpinhits[iDst];
      outdstar[iDst].Trkpinhits = Trkpinhits[iDst];
      outdstar[iDst].TrkSnhits = TrkSnhits[iDst];

      outdstar[iDst].TrkKchi2 = TrkKchi2[iDst];
      outdstar[iDst].Trkpichi2 = Trkpichi2[iDst];
      outdstar[iDst].TrkSchi2 = TrkSchi2[iDst];

      outdstar[iDst].DSDeltaR = DSDeltaR[iDst];

      outdstar[iDst].TrkKpt = TrkKpt[iDst];
      outdstar[iDst].Trkpipt = Trkpipt[iDst];
      outdstar[iDst].TrkSpt = TrkSpt[iDst];

      outdstar[iDst].TrkKeta = TrkKeta[iDst];
      outdstar[iDst].Trkpieta = Trkpieta[iDst];
      outdstar[iDst].TrkSeta = TrkSeta[iDst];

      outdstar[iDst].TrkKphi = TrkKphi[iDst];
      outdstar[iDst].Trkpiphi = Trkpiphi[iDst];
      outdstar[iDst].TrkSphi = TrkSphi[iDst];

      outdstar[iDst].TrkScharge = TrkScharge[iDst];

      outdstar[iDst].D0fromDSsXY_vec = D0fromDSsXY_vec[iDst];

      outdstar[iDst].ntracksDstar = ntracksDstar;
      outdstar[iDst].ntracksD0Kpi = ntracksD0Kpi;
    }
}

double UABaseTree::FindAngle(const reco::Vertex& pv , const TransientVertex& sv, const math::XYZTLorentzVector& vD0angle )
{
  CLHEP::Hep3Vector displacement( sv.position().x() - pv.position().x() ,
  				  sv.position().y() - pv.position().y() ,
  				  sv.position().z() - pv.position().z() ) ;

  CLHEP::Hep3Vector momentum( vD0angle.Px() , vD0angle.Py() , vD0angle.Pz() ) ;
  return momentum.angle(displacement) ;

}

