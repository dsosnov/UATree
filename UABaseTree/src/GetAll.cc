// Description: Function to retrieve all the classes

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool AllDebug = false;

void UABaseTree::GetAll(const edm::Event& iEvent , const edm::EventSetup& iSetup){
  // General Info
  std::cout << "1\n";
                                    GetAllBeamSpots(iEvent);

  std::cout << "1.1\n";
  if(storeEvtId_)                   GetEvtId(iEvent);
  std::cout << "1.2\n";
  if(storeFwdGap_)                  GetFwdGap(iEvent); 
  std::cout << "1.3\n";
  if(storeGenKin_)		    GetGenKin (iEvent);
  if(storeGenPart_ || 
     enableGenMetFromGenPart_)      GetGenPart(iEvent,iSetup);
  std::cout << "1.4\n";
  if(storePUSumInfo_)               GetPUSumInfo(iEvent);
  std::cout << "1.5\n";
  if(hlt_paths_.size() > 0)         GetHLTrig(iEvent,iSetup);
  //  if(storeL1Trig_)		    GetL1Trig(iEvent,iSetup);
  std::cout << "1.6\n";
  if(storeL1TrigOld_)		    GetL1TrigOld(iEvent);
  std::cout << "1.6.5\n";
  if(storeL1TrigRun2_)		    GetL1TrigRun2(iEvent,iSetup);
  std::cout << "2\n";
  if(storeMITEvtSel_)               GetMITEvtSel(iEvent);

  // Reset vtx id and vector
  vtxid = 0;
  vtxid_xyz.clear();
  std::cout << "3\n";
  GetAllVertices(iEvent); // Needs to be before tracks & PFJets !!
  GetAllTracks(iEvent); 
  GetAllTracksPID(iEvent); 
  std::cout << "4\n";
  GetAllCaloJets(iEvent,iSetup);
  GetAllPFJets(iEvent,iSetup); 
  GetAllGenJets(iEvent); 
  GetAllBasicJets(iEvent); 
  GetAllTrackJets(iEvent, iSetup); 
  
  //GetAllKshorts(iEvent);
  //GetAllLambdas(iEvent);

  //GetAllCharm(iEvent,iSetup);
  std::cout << "5\n";
  if(castorrechits_.label().size() > 0) GetCastorRecHit(iEvent);
  if(castorjets_.label().size() > 0 &&
     castorjetid_.label().size() > 0)   GetCastorJet(iEvent); 
  if(castordigis_.label().size() > 0)   GetCastorDigi(iEvent,iSetup);
  std::cout << "6\n";
  GetAllElectrons(iEvent); 
  GetAllMuons(iEvent); 
  GetAllPFCands(iEvent); 
  std::cout << "7\n";
  GetAllMETs(iEvent); 
  std::cout << "8\n";
  //GetSiPixelClusters(iEvent, iSetup);
  //GetSiStripClusters(iEvent, iSetup);
  //if(storeCaloObjects_)
  GetCaloTower(iEvent);
  std::cout << "9\n";
}
