// Trigger Inclides
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool L1TrigOldDebug = false;

void UABaseTree::GetL1TrigOld(const edm::Event& iEvent)
{

  // Tests
/*
  if (L1TrigOldDebug)
  {  
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();

   for (CItAlgo algo = menu->gtAlgorithmMap().begin(); 
                algo!=menu->gtAlgorithmMap().end(); 
                ++algo) 
   {
     cout << "Name: " << (algo->second).algoName() 
          << " Alias: " << (algo->second).algoAlias() 
          << " Bit: " << (algo->second).algoBitNumber()
           << " Result: " << l1AlgorithmResult(iEvent, iSetup, (algo->second).algoName() )
          << std::endl;
   }
  }
*/
	//std::cout << "trying get trigger...\n";
   edm::Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
   iEvent.getByLabel("gtDigis",L1GTRR);
   int maxL1 = L1GTRR->decisionWord().size();
   //std::cout << "            L1 size = " << maxL1 << std::endl;
   for (int i=0 ; i <maxL1 ; i++)
   {
     if (L1TrigOldDebug) cout << "PhysicsTriggerWord :" << i << " " << L1GTRR->decisionWord()[i] << endl;
     L1TrigOld.PhysTrigWord[i] = L1GTRR->decisionWord()[i];
   }

   int maxTT = L1GTRR->decisionWord().size();
   //std::cout << "           TT size = " << maxL1 << std::endl;
   for (int i=0 ; i <maxTT  ; i++)
   {
    if (L1TrigOldDebug) cout << "technicalTriggerWord :" << i << " " << L1GTRR->technicalTriggerWord()[i] << endl;
     L1TrigOld.TechTrigWord[i] = L1GTRR->technicalTriggerWord()[i]; 
   }

}

