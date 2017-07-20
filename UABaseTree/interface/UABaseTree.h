#ifndef __UABASETREE_H__
#define __UABASETREE_H__


// system include files
#include <string>
#include <vector>
#include <iostream>

// ROOT
#include "TFile.h"
#include "TTree.h"


// CMSSW Include files (Minimal)
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Point 3D
#include "DataFormats/Math/interface/Point3D.h"

// Trigger
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h" 

// Track
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h" 
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h" 

// Vertex
#include "DataFormats/VertexReco/interface/Vertex.h" 
#include "DataFormats/VertexReco/interface/VertexFwd.h" 

// Muon
#include "DataFormats/MuonReco/interface/MuonFwd.h" 
#include "DataFormats/MuonReco/interface/Muon.h" 

// Electron
#include "DataFormats/EgammaCandidates/interface/Electron.h" 
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h" 

// Jets
#include "DataFormats/JetReco/interface/PFJet.h" 
#include "DataFormats/JetReco/interface/PFJetCollection.h" 
#include "DataFormats/JetReco/interface/CaloJet.h" 
#include "DataFormats/JetReco/interface/CaloJetCollection.h" 
#include "DataFormats/JetReco/interface/TrackJet.h" 
#include "DataFormats/JetReco/interface/TrackJetCollection.h" 
#include "DataFormats/JetReco/interface/GenJet.h" 
#include "DataFormats/JetReco/interface/GenJetCollection.h" 
#include "DataFormats/JetReco/interface/JetID.h" 
#include "DataFormats/Common/interface/ValueMap.h" 

// MET
#include "DataFormats/METReco/interface/GenMET.h" 
#include "DataFormats/METReco/interface/GenMETCollection.h" 
 
#include "DataFormats/METReco/interface/PFMET.h" 
#include "DataFormats/METReco/interface/PFMETCollection.h" 
 
#include "DataFormats/METReco/interface/CaloMET.h" 
#include "DataFormats/METReco/interface/CaloMETCollection.h" 
 
#include "DataFormats/METReco/interface/MET.h" 
#include "DataFormats/METReco/interface/METCollection.h" 

// dEdx
#include "DataFormats/TrackReco/interface/DeDxData.h" 
#include "DataFormats/TrackReco/interface/DeDxHit.h" 
#include "DataFormats/TrackReco/interface/DeDxHitInfo.h" 


//L1
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/DataRecord/interface/L1TUtmTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1TUtmTriggerMenu.h"

// UATree Analysis class declaration

#include "UATree/UADataFormat/interface/MassParticles.h"

#include "UATree/UADataFormat/interface/MyPart.h"

#include "UATree/UADataFormat/interface/MyEvtId.h"
#include "UATree/UADataFormat/interface/MyL1Trig.h"
#include "UATree/UADataFormat/interface/MyL1TrigOld.h"
#include "UATree/UADataFormat/interface/MyL1TrigRun2.h"
#include "UATree/UADataFormat/interface/MyL1MenuRun2.h"
#include "UATree/UADataFormat/interface/MyHLTrig.h"

#include "UATree/UADataFormat/interface/MyGenKin.h"
#include "UATree/UADataFormat/interface/MyGenMet.h"
#include "UATree/UADataFormat/interface/MyGenPart.h"
#include "UATree/UADataFormat/interface/MySimVertex.h"
#include "UATree/UADataFormat/interface/MyPUSumInfo.h"

#include "UATree/UADataFormat/interface/MyBeamSpot.h"
#include "UATree/UADataFormat/interface/MyVertex.h"
#include "UATree/UADataFormat/interface/MyTracks.h"

#include "DataFormats/V0Candidate/interface/V0Candidate.h" 
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h" 
#include "UATree/UADataFormat/interface/MyKshorts.h" 
#include "UATree/UADataFormat/interface/MyLambdas.h" 
#include "UATree/UADataFormat/interface/MyD0.h"
#include "UATree/UADataFormat/interface/MyDstar.h"
#include "UATree/UADataFormat/interface/MySiPixelCluster.h"
#include "UATree/UADataFormat/interface/MySiStripCluster.h" 

#include "UATree/UADataFormat/interface/MyFwdGap.h"

// MIT code
#include "UATree/UADataFormat/interface/MyMITEvtSel.h"

// Jets
#include "UATree/UADataFormat/interface/MyCaloJet.h"
#include "UATree/UADataFormat/interface/MyTrackJet.h"
#include "UATree/UADataFormat/interface/MyPFJet.h"
#include "UATree/UADataFormat/interface/MyGenJet.h"

//Castor
#include "UATree/UADataFormat/interface/MyCastorRecHit.h"
#include "UATree/UADataFormat/interface/MyCastorJet.h"
#include "UATree/UADataFormat/interface/MyCastorDigi.h"
#include "UATree/UADataFormat/interface/MyDiJet.h"

//Identified Particles
#include "UATree/UADataFormat/interface/MyElectron.h"
#include "UATree/UADataFormat/interface/MyMuon.h"
#include "UATree/UADataFormat/interface/MyPFCand.h"

#include "UATree/UADataFormat/interface/MyMet.h"

//CaloObjects
#include "UATree/UADataFormat/interface/MyCaloTower.h"

// FSC
#include "UATree/UADataFormat/interface/MyFSCHit.h"
#include "UATree/UADataFormat/interface/MyFSCDigi.h"
#include "UATree/UADataFormat/interface/MyFSCInfo.h"

// Charm
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"


using namespace std;
using namespace edm;
using namespace reco;

typedef ParameterSet PSet;

//
// Class declaration
//

class UABaseTree : public EDAnalyzer {
   public:
      explicit UABaseTree(const ParameterSet&);
      ~UABaseTree();

   private:
      virtual void beginJob() override;
      virtual void beginRun(Run const &, EventSetup const&) override;
      virtual void analyze(const Event&, const EventSetup&) override;
      virtual void endJob() override;

      // --------------------   Getters   --------------------
      virtual void GetAll(          const Event& , const EventSetup& );
      
      virtual void GetBeamSpot(     const Event& , const string& , MyBeamSpot& );
      virtual void GetAllBeamSpots( const Event& );
      virtual void GetEvtId(        const Event& );
      virtual void GetFwdGap(       const Event& );
      
      virtual void GetGenKin(       const Event& );
      virtual void GetGenPart(      const Event& , const EventSetup& ); 
      virtual void FillGenPart(     const GenParticle& , MyGenPart& );
      virtual void GetPUSumInfo(    const Event& );
      
      virtual void GetHLTrig(       const Event& , const EventSetup& );
      virtual void GetL1Trig(       const Event& , const EventSetup& );
      virtual void GetL1TrigOld(    const Event& );
      virtual void GetL1TrigRun2(   const Event& , const EventSetup& );
      virtual void StoreL1Menu( Run const &,       const EventSetup& );
      
      virtual void GetMITEvtSel(    const Event& );
      
      virtual void GetRecoTracks(    const Event& , const string , vector<MyTracks>& );
      virtual void GetRecoTracksPID( const Event& , const string , vector<MyTracks>& );
      virtual void GetAllTracks(     const Event& );
      virtual void GetAllTracksPID(  const Event& );
      virtual void FillTrack(       const Track& , MyTracks& , Double_t = MASS_PI );
      virtual void FillTrackPID(    const Track& , MyTracks& , Double_t = -999 , 
                                    const vector<double>& = vector<double>(), const vector<double>& = vector<double>(),
                                    const vector<unsigned int>& = vector<unsigned int>(), const vector<bool>& = vector<bool>(), Double_t = MASS_PI );

      virtual void GetRecoVertex(   const Event& , const string , vector<MyVertex>& ); 
      virtual void GetAllVertices(  const Event& ); 
      
      virtual void GetAllKshorts(    const Event& ); 
      virtual void GetAllLambdas(    const Event& ); 

      virtual void GetAllCharm(    const Event&, const EventSetup& );

      virtual void GetSiPixelClusters(    const Event& , const EventSetup& );
      virtual void GetSiStripClusters(    const Event& , const EventSetup& ); 

      template <class T,class U>
      void FillJetCorrections(      const Event& , const EventSetup& , const vector<T>& , const vector<string>& , vector<U>& );
      virtual void GetRecoCaloJets( const Event& , const EventSetup& , const PSet& , vector<MyCaloJet>& );
      virtual void GetAllCaloJets(  const Event& , const EventSetup& );
      virtual void GetRecoPFJets(   const Event& , const EventSetup& , const PSet& , vector<MyPFJet>& );
      virtual void GetAllPFJets(    const Event& , const EventSetup& );
      
      virtual void GetGenJets(      const Event& , const InputTag& , vector<MyGenJet>& );
      virtual void GetAllGenJets(   const Event& );
     
      template <class T>
      void FillBasicJet(            const vector<T>& , vector<MyBaseJet>& ); 
      virtual void GetBasicJet    ( const Event& , const InputTag& , vector<MyBaseJet>& );
      virtual void GetAllBasicJets( const Event& );

      virtual void GetRecoTrackJets( const Event& , const EventSetup& , const PSet& ,  vector<MyTrackJet>& );
      virtual void GetAllTrackJets ( const Event& , const EventSetup& );
      //      virtual int  GetVertexId     ( const Vertex& );

      virtual void GetCastorRecHit( const Event& ); 
      virtual void GetCastorJet(    const Event& ); 
      virtual void GetCastorDigi(   const Event& , const EventSetup& ); 
      virtual void GetCentralDiJet( const vector<MyJet*>& , const string , MyDiJet& ); 
      
      virtual void GetRecoElectron( const Event& , const InputTag& , vector<MyElectron>& ); 
      virtual void GetAllElectrons( const Event& ); 
      virtual void GetRecoMuon(     const Event& , const InputTag& , vector<MyMuon>& ); 
      virtual void GetAllMuons(     const Event& ); 
      virtual void GetRecoPFCand(   const Event& , const InputTag& , vector<MyPFCand>& ); 
      virtual void GetAllPFCands(   const Event& ); 
      
      virtual void GetMET(          const Event& , const string& , vector<MyMet>& );
      virtual void GetAllMETs(      const Event& );
      template <class T>
      void FillAllMET(              const vector<T>& , vector<MyMet>& );
      
      virtual void GetCaloTower(    const Event& ); 

      virtual void GetFSCInfo( const Event&, const EventSetup& ); 

      // --------------------   Get All Parameters   --------------------
      virtual void GetParameters( const ParameterSet& );
     
      // --------------------   Init All Branches   --------------------
      virtual void Init();
      
      // --------------------      Filter Event      --------------------
      virtual Bool_t FilterEvents();
      
      // --------------------   Other Functions   --------------------
      bool hasFired(const std::string& , const TriggerNames& trigNames, const TriggerResults& ) const;
      Bool_t GetLooseCaloJetId(const MyCaloJet& , const string& );
      Bool_t GetTightCaloJetId(const MyCaloJet& , const string& );
      Bool_t GetLoosePFJetId(  const MyPFJet&   , const string& );
      Bool_t GetTightPFJetId(  const MyPFJet&   , const string& );
      Bool_t clusterCleaning(const SiStripCluster*   cluster,  int crosstalkInv=0, uint8_t* exitCode=NULL); 
      std::vector<int> convert(const vector<unsigned char>& input); 
      std::vector<int> CrossTalkInv(const std::vector<int>&  Q, const float x1=0.10, const float x2=0.04, bool way=true,float threshold=20,float thresholdSat=25); 
      double FindAngle(const reco::Vertex& , const TransientVertex& , const math::XYZTLorentzVector& );

      const string GetBranchName(InputTag& , Bool_t = 1);
      const string GetCollName(const string&);
      const string GetColl(const string&);
      const InputTag GetCollInputTag(const string&);


      // -------------------------------------------------------------------
      // --------------------   Vars From Config File   --------------------
      
      vector<InputTag> beamspots_ ;
      Bool_t           storeEvtId_;
      InputTag         calotower_ ;
      Bool_t           storeFwdGap_;
      InputTag         hepmc_ ;
      InputTag         genpart_ ;
      Bool_t           storeGenKin_;
      Bool_t           storeGenPart_;
      InputTag         pusuminfo_;
      Bool_t           storePUSumInfo_;
      vector<string>   hlt_paths_;
      Bool_t           storeL1Trig_;
      Bool_t           storeL1TrigOld_;
      Bool_t           storeL1TrigRun2_;
      Bool_t           storeMITEvtSel_;
      vector<InputTag> tracks_ ;
      vector<InputTag> tracksPID_ ;
      vector<InputTag> vertices_ ;
      vector<PSet>     vcalojets_;
      vector<PSet>     vpfjets_;
      vector<PSet>     vtrackjets_;
      vector<InputTag> genjets_;
      vector<InputTag> basicjets_;
      vector<InputTag> trackjets_;
      string           vtxcoll_for_trackjets_;
      vector<InputTag> electrons_;
      vector<InputTag> muons_;
      vector<InputTag> pfcands_;
      vector<InputTag> mets_;
      InputTag         calotowercoll_;
      Bool_t           storeCaloObjects_;
      
      InputTag         kshorts_ ; 
      InputTag         lambdas_ ; 

      // Castor Stuff
      InputTag         castorrechits_;
      InputTag         castorjets_;
      InputTag         castorjetid_;
      InputTag         castordigis_;
      
      // FSC
      Bool_t           storeFSCHits_;
      Bool_t           storeFSCDigis_;
      Bool_t           storeFSCInfo_;
      InputTag         fscrechits_;
      InputTag         fscdigis_;

      //for fwdGap
      double energyThresholdHB_ ;
      double energyThresholdHE_ ;
      double energyThresholdHF_ ;
      double energyThresholdEB_ ;
      double energyThresholdEE_ ;
      
      //for genPart
      Bool_t saveMothersAndDaughters_;
      Bool_t onlyStableGenPart_;
      Bool_t onlyChargedGenPart_;
      Bool_t enableGenMetFromGenPart_;
      Bool_t saveGenPartsInDifferentColls_;
      
      //for PFJets
      Bool_t storeTracksInPFJets_;
      
      //for jet ID
      PSet ParaSetLooseCaloJetID_;
      PSet ParaSetTightCaloJetID_;
      PSet ParaSetLoosePFJetID_;
      PSet ParaSetTightPFJetID_;
      
      //for DiJets
      Double_t   jetPtCut_;
      Double_t   jetEtaCut_;
     
      Bool_t     filterEvents_; 
      
      string outputfilename_ ;

      // ----------------------------------------------------------
      // --------------------   Tree Content   --------------------
     
      map<string,MyBeamSpot>        allBeamSpots;
      MyEvtId                       evtId;
      MyFwdGap                      fwdGap;
      
      MyGenKin                      genKin;
      MyPart                        genMetfromGenPartst1;
      MyPart                        genMetfromGenPartst3;
      vector<MyGenPart>             genPart;
      vector<MyGenPart>             genElec;
      vector<MyGenPart>             genMu;
      vector<MyGenPart>             genNu;
      MySimVertex                   simVertex;
      MyPUSumInfo                   pusuminfo;      

      MyL1Trig                      L1Trig;
      MyL1TrigOld                   L1TrigOld; 
      MyL1TrigRun2                  L1TrigRun2; 
      MyL1MenuRun2                  L1MenuRun2; 
      MyHLTrig                      HLTrig;
      
      MyMITEvtSel                   MITEvtSel;
      
      map<string,vector<MyTracks> > allTracks;
      map<string,vector<MyTracks> > allTracksPID;
      map<string,vector<MyVertex> > allVertices;

      map<string,vector<MyKshorts> > allKshorts; 
      map<string,vector<MyLambdas> > allLambdas; 

      map<string,vector<MyD0> >      allD0s;  
      map<string,vector<MyDstar> >   allDstar;
 
      map<string,vector<MyCaloJet> > allCaloJets;
      map<string,vector<MyPFJet> >   allPFJets;
      
      map<string,vector<MyGenJet> >   allGenJets;
      map<string,vector<MyBaseJet> >  allBasicJets;
      map<string,vector<MyTrackJet> > allTrackJets;
 
      vector<MyCastorRecHit>        castorRecHits;
      vector<MyCastorJet>           castorJets;
      vector<MyCastorDigi>          castorDigis;
      map<string , MyDiJet>         allDiJets;

      map<string,vector<MyElectron> > allElectrons;
      map<string,vector<MyMuon> >     allMuons;
      map<string,vector<MyPFCand> >   allPFCands;

      map<string,vector<MyMet> >      allMETs;

      vector<MyCaloTower>             caloTowers;

      vector<MyKshorts>               outks; 
      vector<MyLambdas>               outlambda; 

      vector<MyD0>                    outd0;  
      vector<MyDstar>                 outdstar;

      // Si clusters
      vector<MySiPixelCluster>        outsipixelcluster;
      MySiStripCluster                outsistripcluster;

      // FSC
      vector<MyFSCHit>  fscHits;
      vector<MyFSCDigi> fscDigis;
      MyFSCInfo         fscInfo;

      // -------------------------------------------------------
      // --------------------   Vertex Id   --------------------
      Int_t vtxid;
      vector<math::XYZPoint> vtxid_xyz;

      // map<int,string> HLT_map;

      // --------------------   Needed For HLT   --------------------
      bool isValidHltConfig_;
      bool isValidHltPrescales_;
      HLTConfigProvider hltConfig_;
      HLTPrescaleProvider hltPrescales;
      L1GtUtils L1GTUtility;
  

      // for L1TrigOld
      edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> L1GTRRToken_;

      // for L1TrigRun2
      edm::EDGetTokenT<GlobalAlgBlkBxCollection> L1R2_GABBCToken_;

      // --------------------   File & Tree   --------------------
      TFile*   fout;
      TTree*   tree;
      TBranch* L1MenuRun2Branch;
};

#include "TemplateFunctions_jets.h"

#endif

