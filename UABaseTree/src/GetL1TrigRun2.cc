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

bool GetL1TrigRun2Debug = true;

void convertCuts (std::vector<L1TUtmCut> const& cIn, std::vector<MyL1TUtmCut> &cOut){
  for (auto i: cIn){
    cOut.push_back({
      i.getName(),
      i.getObjectType(),
      i.getCutType(),
      MyL1TUtmCutValue{i.getMinimum().value, i.getMinimum().index},
      MyL1TUtmCutValue{i.getMaximum().value, i.getMaximum().index},
      i.getData(),
      i.getKey()
    });
  };
}

void UABaseTree::StoreL1Menu(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  edm::ESHandle<L1TUtmTriggerMenu> menu;
  iSetup.get<L1TUtmTriggerMenuRcd>().get( menu );

  bool printL1TrigData = true;
  boost::shared_ptr<L1TUtmTriggerMenu> ptr1( new L1TUtmTriggerMenu( *( menu.product() ) ) );

  MyL1TUtmTriggerMenu triggerMenu;
  triggerMenu.name = ptr1->getName();
  triggerMenu.version = ptr1->getVersion();
  triggerMenu.comment = ptr1->getComment();
  triggerMenu.datetime = ptr1->getDatetime();
  triggerMenu.uuid_firmware = ptr1->getFirmwareUuid();
  triggerMenu.scale_set_name = ptr1->getScaleSetName();
  triggerMenu.n_modules = ptr1->getNmodules();

  for( auto a : ptr1->getAlgorithmMap() ) {
    MyL1TUtmAlgorithm algo{
      a.second.getName(),
      a.second.getExpression(),
      a.second.getExpression(),
      a.second.getIndex(),
      a.second.getModuleId(),
      a.second.getModuleIndex()
    };
    algo.rpn_vector.insert( algo.rpn_vector.begin(), a.second.getRpnVector().begin(), a.second.getRpnVector().end() );
    triggerMenu.algorithm_map.insert( std::make_pair( a.first, algo ) ); // or triggerMenu.algorithm_map[a.first] = algo;
  }
  for( auto a : ptr1->getConditionMap() ) {
    MyL1TUtmCondition condition{
      a.second.getName(),
      a.second.getType()
    };
    for(auto o: a.second.getObjects()){
      MyL1TUtmObject obj{
        o.getName(),
        o.getType(),
        o.getComparisonOperator(),
        o.getBxOffset(),
        o.getThreshold(),
        o.getExternalSignalName(),
        o.getExternalChannelId()
      };
      convertCuts(o.getCuts(), obj.cuts);
      condition.objects.push_back(obj);
    }
    convertCuts(a.second.getCuts(), condition.cuts);
    triggerMenu.condition_map.insert( std::make_pair( a.first, condition ) );
  };
  for( auto a : ptr1->getScaleMap() ){
    MyL1TUtmScale scale{
      a.second.getName(),
      a.second.getObjectType(),
      a.second.getScaleType(),
      a.second.getMinimum(),
      a.second.getMaximum(),
      a.second.getStep(),
      a.second.getNbits()
    };
    for (auto b: a.second.getBins())
      scale.bins.push_back(MyL1TUtmBin{b.hw_index, b.minimum, b.maximum});
    triggerMenu.scale_map.insert( std::make_pair( a.first, scale ) ); // or triggerMenu.algorithm_map[a.first] = algo;
  }
  L1MenuRun2.menu.insert(std::make_pair(iRun.run(), triggerMenu)); // or maybe be better as L1MenuRun2.menu[iRun.run()]=triggerMenu; for rewrite existed
  if(printL1TrigData) L1MenuRun2.Print();
}

void UABaseTree::GetL1TrigRun2(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<GlobalAlgBlkBxCollection> ugtBXhandle;
  iEvent.getByToken( L1R2_GABBCToken_, ugtBXhandle );
  //http://cmslxr.fnal.gov/source/DQM/HLTEvF/plugins/PSMonitor.cc?v=CMSSW_8_0_24
  // but I believe it is column#, the prescale to be found in menu...
  int psColumn = -1;
  GlobalAlgBlk const *results_;
  L1TrigRun2.triggerResults.clear();
  if( ugtBXhandle.isValid() and not ugtBXhandle->isEmpty( 0 ) ) {
    psColumn = ugtBXhandle->at( 0, 0 ).getPreScColumn();
    std::cout << "prescale column: " << psColumn << std::endl;
    results_ = & ugtBXhandle->at( 0, 0 );
    //http://cmslxr.fnal.gov/source/DataFormats/L1TGlobal/interface/GlobalAlgBlk.h?v=CMSSW_8_0_24
    L1TrigRun2.triggerResults.resize(results_->maxPhysicsTriggers, 0);
    for( unsigned int i = 0; i < results_->maxPhysicsTriggers; i++ ) {
      bool val = results_->getAlgoDecisionFinal( i );
      if( val ){
        L1TrigRun2.triggerResults.push_back(val);
        std::cout << "bit " << i << "(" << results_->maxPhysicsTriggers << ") : " << val << std::endl;
      }
    }
  }
}

