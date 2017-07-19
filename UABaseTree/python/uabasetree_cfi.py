#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !

import FWCore.ParameterSet.Config as cms

# Standard Parameters For UABaseTree Process   ----------------------------------------
uabasetree = cms.EDAnalyzer('UABaseTree',
  filterEvents = cms.untracked.bool(False),		#filterEvents for data. Switched Off for MC
  storeEvtId = cms.untracked.bool(True),		
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(False),
  storeL1TrigOld = cms.untracked.bool(False),		#old simple version. Deprecated.
  storeL1TrigRun2 = cms.untracked.bool(True),		#New version for Run2
  hlt_paths = cms.untracked.vstring(
	"HLT_PAL1MinimumBiasHF_OR_v1",
	"HLT_PARandom_v1",
	"HLT_PAZeroBias_v1",
	"HLT_PA*"	
  ),
  doDAvertex = cms.untracked.bool(True)
)
