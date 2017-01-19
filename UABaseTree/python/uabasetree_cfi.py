#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !

import FWCore.ParameterSet.Config as cms

# Standard Parameters For UABaseTree Process   ----------------------------------------
uabasetree = cms.EDAnalyzer('UABaseTree',
  filterEvents = cms.untracked.bool(False),		#filterEvents for data. Switched Off for MC
  storeEvtId = cms.untracked.bool(True),		
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(True),
  storeL1TrigOld = cms.untracked.bool(True),		#old simple version. Deprecated.
  hlt_paths = cms.untracked.vstring(
	"HLT_PAL1MinimumBiasHF_OR_v1",
	"HLT_PARandom_v1",
	"HLT_PAZeroBias_v1",
	"HLT_PA*"	
  )
)
