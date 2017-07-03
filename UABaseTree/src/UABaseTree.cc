// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


UABaseTree::UABaseTree(const edm::ParameterSet& iConfig) : 
  hltPrescales(iConfig, consumesCollector(), *this),
  L1GTUtility(iConfig, consumesCollector(), true, *this)
{
	std::cout << "constructor\n";
  //Getting all standard parameters
  this->GetParameters(iConfig);
	std::cout << "1...\n";

  // Consumes migration for CMSSW_7_6_X
  // Ugly, but this needs to be done in the constructor for all products...
  for(vector<InputTag>::iterator it = beamspots_.begin() ; it != beamspots_.end() ; ++it)  
    { 
      consumes<reco::BeamSpot>(edm::InputTag(it->label())); 
    } 
  consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD"));
  consumes<edm::TriggerResults>(edm::InputTag("TriggerResults::HLT"));
  L1GTRRToken_ = consumes<L1GlobalTriggerReadoutRecord>(edm::InputTag("gtDigis"));
	std::cout << "1...2...\n";

  for(vector<InputTag>::iterator icoll = vertices_.begin() ; icoll!= vertices_.end() ; ++icoll) 
    {
      consumes<reco::VertexCollection>(edm::InputTag(icoll->label()));
    }
  for(vector<InputTag>::iterator icoll = tracks_.begin() ; icoll!= tracks_.end() ; ++icoll) 
    {
      consumes<TrackCollection>(edm::InputTag(icoll->label()));
    }
  for(vector<InputTag>::iterator icoll = tracksPID_.begin() ; icoll!= tracksPID_.end() ; ++icoll) 
    {
      consumes<TrackCollection>(edm::InputTag(icoll->label())); 
    }
	std::cout << "1...2...3...\n";

  consumes<reco::VertexCompositeCandidateCollection>(edm::InputTag("generalV0Candidates","Kshort"));
  consumes<reco::VertexCompositeCandidateCollection>(edm::InputTag("generalV0Candidates","Lambda")); 

  consumes<edmNew::DetSetVector<SiStripCluster>>(edm::InputTag("siStripClusters"));
  consumes<edmNew::DetSetVector<SiPixelCluster>>(edm::InputTag("siPixelClusters")); 

	std::cout << "1...2...3...4...\n";
  for(vector<InputTag>::iterator icoll = muons_.begin() ; icoll!= muons_.end() ; ++icoll) 
    {
      consumes<MuonCollection>(edm::InputTag(icoll->label()));
    }
  for(vector<InputTag>::iterator icoll = electrons_.begin() ; icoll!= electrons_.end() ; ++icoll) 
    {
      consumes<reco::GsfElectronCollection>(edm::InputTag(icoll->label()));
    }
  for(vector<InputTag>::iterator icoll = pfcands_.begin() ; icoll!= pfcands_.end() ; ++icoll) 
    {
      consumes<PFCandidateCollection>(edm::InputTag(icoll->label()));
    }

	std::cout << "1...2...3...5...\n";

  for(vector<InputTag>::iterator icoll = basicjets_.begin() ; icoll != basicjets_.end() ; ++icoll)
    {
      consumes<TrackJetCollection>(edm::InputTag(icoll->label()));
      consumes<PFJetCollection>(edm::InputTag(icoll->label())); 
      consumes<CaloJetCollection>(edm::InputTag(icoll->label()));  
      consumes<GenJetCollection>(edm::InputTag(icoll->label()));  
    }

  InputTag jetcoll_; 
  InputTag jetid_;
  for(vector<PSet>::iterator it = vcalojets_.begin() ; it != vcalojets_.end() ; ++it)
    { 
      jetcoll_ = it->getUntrackedParameter<InputTag>("jetcoll",InputTag());
      InputTag jetid_  = it->getUntrackedParameter<InputTag>("calojetid",InputTag()); 
      consumes<CaloJetCollection>(edm::InputTag(jetcoll_.label()));
      consumes<reco::JetIDValueMap>(edm::InputTag(jetid_));
    }
  for(vector<PSet>::iterator it = vpfjets_.begin() ; it != vpfjets_.end() ; ++it)
    {  
      jetcoll_ = it->getUntrackedParameter<InputTag>("jetcoll",InputTag());
      consumes<PFJetCollection>(edm::InputTag(jetcoll_.label())); 
    } 
  for(vector<PSet>::iterator it = vtrackjets_.begin() ; it != vtrackjets_.end() ; ++it)
    {   
      jetcoll_ = it->getUntrackedParameter<InputTag>("jetcoll",InputTag());  
      consumes<TrackJetCollection>(edm::InputTag(jetcoll_.label()));  
    }  
  for(vector<InputTag>::iterator icoll = genjets_.begin() ; icoll!= genjets_.end() ; ++icoll) 
    {
      consumes<GenJetCollection>(edm::InputTag(icoll->label()));
    }
  for(vector<InputTag>::iterator icoll = mets_.begin() ; icoll!= mets_.end() ; ++icoll) 
    {
      consumes<GenMETCollection>(edm::InputTag(icoll->label()));
      consumes<PFMETCollection>(edm::InputTag(icoll->label())); 
      consumes<CaloMETCollection>(edm::InputTag(icoll->label())); 
      consumes<METCollection>(edm::InputTag(icoll->label())); 
    }
	std::cout << "1...2...3...5...6...\n";

  consumes<reco::DeDxHitInfoAss>(edm::InputTag("hscpdedxHitInfo"));

  isValidHltConfig_ = false;
  isValidHltPrescales_ = false;
	std::cout << "                    ...done\n";
}


UABaseTree::~UABaseTree(){
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


// ------------ method called to for each event  ------------
void
UABaseTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  this->GetAll(iEvent , iSetup);

  if(filterEvents_){
     if(this->FilterEvents())
       tree->Fill();
  }
  else
    tree->Fill(); 
}


// ------------ method called once each job just before starting event loop  ------------
void UABaseTree::beginJob(){
  this->Init();
}


//-- method called to for each run
void UABaseTree::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup){
  //isValidHltConfig_ = hltConfig.init(iRun,iSetup,"HLT",changed);

  //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHighLevelTrigger
  bool changed(true);
  if (hltConfig_.init(iRun,iSetup,"HLT",changed)) {
    // if init returns TRUE, initialisation has succeeded!
    if (changed) {
    	std::cout << "/n/n changed HLT configuration/n/n" << std::endl;
    };
  } else {
    // if init returns FALSE, initialisation has NOT succeeded, which indicates a problem
    // with the file and/or code and needs to be investigated!
    std::cout << "/n/nHLT config extraction failure with process name HLT" << std::endl;
    // In this case, all access methods will return empty values!
  }
  if(storeL1Trig_) {
    // JH, 76
    //    L1GtUtils L1GTUtility;
    // end JH
    L1GTUtility.retrieveL1EventSetup(iSetup);
    //-- input tag for L1GtTriggerMenuLite retrieved from provenance                                            
    edm::InputTag l1GtTriggerMenuLiteInputTag("l1GtTriggerMenuLite");
    // JH, 76
    //    L1GTUtility.retrieveL1GtTriggerMenuLite(iRun, l1GtTriggerMenuLiteInputTag);
    L1GTUtility.retrieveL1GtTriggerMenuLite(iRun);
    // end JH
  }
  
}


// ------------ method called once each job just after ending the event loop  ------------
void UABaseTree::endJob(){
   fout->Write() ;
   fout->Close() ;
}


//define this as a plug-in
DEFINE_FWK_MODULE(UABaseTree);
