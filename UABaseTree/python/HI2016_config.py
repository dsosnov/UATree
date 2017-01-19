import os
import FWCore.ParameterSet.Config as cms

process = cms.Process("UABaseTree")

process.maxEvents = cms.untracked.PSet(
   input = cms.untracked.int32(100)
)

#from UATree.UABaseTree.UABaseTree_cfi import *
#process.load("UATree.UABaseTree.UABaseTree_cfi")
from UATree.UABaseTree.UABaseTree_forward_all_cfi import *
process.load("UATree.UABaseTree.UABaseTree_forward_all_cfi")
isMonteCarlo = False
keepCMSData  = False

# initialize MessageLogger and output report ----------------------------------------

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
   wantSummary = cms.untracked.bool(True),
   SkipEvent = cms.untracked.vstring('ProductNotFound')

)

# Data source -----------------------------------------------------------------------
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
   'file:'+os.environ['HOME']+'/work/pA16/PAMinimumBiasBkg_AODPromptRecov1_285383_2CF47FC1-4DAE-E611-951D-02163E011B86.root'
                           )
   )                               

# configure modules via Global Tag --------------------------------------------------
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# https://twiki.cern.ch/twiki/bin/view/CMS/HIData2016
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v15'

#Geometry --------------------------------------------------------------------------
process.load("Configuration/Geometry/GeometryIdeal2015Reco_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


#process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.EventContent.EventContent_cff')

#HLT Stuff
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

#FileName of the output of the UATree. Needed here for AutoCrab.
process.uabasetree.outputfilename = cms.untracked.string("test2016data.root")

process.path = cms.Sequence()


#  ----------------------------   if MC   ----------------------------
if isMonteCarlo:
   #to be replaces   
   process.GlobalTag.globaltag = 'START50_V16A::All'
   
 
#  ----------------------------   Castor   ----------------------------
#if storeCastor:
   #process.castorDigis.InputLabel = 'source'
   #process.load("RecoLocalCalo.Castor.CastorCellReco_cfi")    #-- redo cell
   #process.load("RecoLocalCalo.Castor.CastorTowerReco_cfi")   #-- redo tower
   #process.load("RecoJets.JetProducers.ak7CastorJets_cfi")    #-- redo jet
   #process.load("RecoJets.JetProducers.ak7CastorJetID_cfi")   #-- redo jetid
   #process.path = cms.Sequence(process.path  * process.castorDigis*process.castorreco*process.CastorCellReco*process.CastorTowerReco*process.ak7BasicJets*process.ak7CastorJetID)

# --------------------------- Write CMS data -------------------------------

if keepCMSData:
   process.out = cms.OutputModule("PoolOutputModule",
       fileName = cms.untracked.string('/tmp/cmsdata.root')
   )

#  ----------------------------   Final Path   ----------------------------
process.path = cms.Sequence(process.path * process.uabasetree)

process.p = cms.Path( process.path )

if keepCMSData:
   process.outpath = cms.EndPath(process.out)
