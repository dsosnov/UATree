// Trigger Inclides
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//#include "FWCore/Framework/interface/TriggerNames.h"
//#include "FWCore/Common/interface/TriggerNames.h"

// UAHiggsTree UAHiggs class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool HLTDebug = false;

void UABaseTree::GetHLTrig(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  HLTrig.Reset();
  
  //-- Find HLT Data Object Name
  edm::InputTag srcTriggerResults_("TriggerResults");
  if (srcTriggerResults_.process().empty()) {

    edm::InputTag srcTriggerEvent("hltTriggerSummaryAOD");
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByLabel(srcTriggerEvent,triggerEvent);

    string hltProcName = triggerEvent.provenance()->processName();
    if(HLTDebug) cout<<"HLT process = "<<hltProcName<<endl;
    srcTriggerResults_ = edm::InputTag(srcTriggerResults_.label()+"::"+hltProcName);
  }

  if(HLTDebug) cout<<srcTriggerResults_<<endl;

  //-- Fetch HLT Data Object
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByLabel(srcTriggerResults_,trigResults);

  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
  
  if(HLTDebug){
    cout << "Printing list of HLT paths present in the file ==========>" << endl;
    for(unsigned i=0 ; i < trigNames.size() ; ++i)
      cout << "    " << trigNames.triggerName(i) << endl;  
  }
  
  //https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHighLevelTrigger
  //HLTConfigProvider const& hltConfig = hltPrescales.hltConfigProvider();


  //-- Loop on triggers requested by user (config file)
  for(vector<string>::iterator hlt_name = hlt_paths_.begin(); hlt_name != hlt_paths_.end(); hlt_name++) {
    HLTrig.HLTmap[*hlt_name]= hasFired(*hlt_name,trigNames,*trigResults);

    std::cout << "HLT6\n";
    std::cout << *hlt_name << std::endl;


    // stolen from https://cmssdt.cern.ch/SDT/doxygen/CMSSW_8_0_24/doc/html/d2/dc0/HLTEventAnalyzerAOD_8cc_source.html
    const unsigned int triggerIndex(hltConfig_.triggerIndex(*hlt_name));
    std::cout << "HLT6.1\n";
    //const std::pair<int,int> prescales(hltPrescales.prescaleValues(iEvent,iSetup,*hlt_name));
    //std::cout << "HLT6.2\n";
    const std::pair<std::vector<std::pair<std::string,int> >,int> prescalesInDetail(hltPrescales.prescaleValuesInDetail(iEvent,iSetup,*hlt_name));

    std::cout << "HLT7\n";


    //std::pair<int,int> prescaleValues(iEvent, iSetup, *hlt_name);
    HLTrig.HLTprescale[*hlt_name]= hltPrescales.prescaleValue(iEvent,iSetup,*hlt_name);
/*
    170   for (unsigned int i=0; i<prescalesInDetail.first.size(); ++i) {
      171     message << " " << i << ":" << prescalesInDetail.first[i].first << "/" << prescalesInDetail.first[i].second;
      172   }
      173   LogVerbatim("HLTEventAnalyzerAOD") << "HLTEventAnalyzerAOD::analyzeTrigger: path "
      174        << triggerName << " [" << triggerIndex << "] "
      175        << endl
      176        << "prescales L1T: " << prescalesInDetail.first.size() <<  message.str()
      177        << endl
      178        << " prescale HLT: " << prescalesInDetail.second
      179        << endl;
      180
      */
    std::cout << "HLT8\n";
    //    HLTrig.HLTprescale[*hlt_name]= hltConfig.prescaleValue(iEvent,iSetup,*hlt_name);
  }

  if(HLTDebug) HLTrig.Print();

}



bool UABaseTree::hasFired(const std::string& triggerName, const edm::TriggerNames& trigNames, const edm::TriggerResults& trigResults) const {

  unsigned index = trigNames.triggerIndex(triggerName);

  if (index>=trigNames.size()) {
    if(HLTDebug) cout<<"[UABaseTree::hasFired] ERROR: unknown trigger name"<<triggerName<<endl;
    return false;
  }

  return trigResults.accept(index);
}


