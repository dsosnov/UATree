#from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *

import FWCore.ParameterSet.Config as cms
from JetMETCorrections.Configuration.DefaultJEC_cff import *

#Declare here your ESSources that are not in JetCorrectionServices_cff ...

#########################
## L1 Offset Correction #
#########################

##-------------------- Disable the CondDB for the L1Offset (until they are included in a new global tag) -------
#ak4CaloL1Offset.useCondDB = False
#ak4PFL1Offset.useCondDB = False

##########################
## L1 FastJet Correction #
##########################

##-------------------- Disable the CondDB for the L1FastJet (until they are included in a new global tag) -------
#ak4CaloL1Fastjet.useCondDB = False
#ak4PFL1Fastjet.useCondDB = False

##-------------------- Import the Jet RECO modules -----------------------
from RecoJets.Configuration.RecoPFJets_cff import *
##-------------------- Turn-on the FastJet density calculation -----------------------
#kt6CaloJets.doRhoFastjet = True
#kt6CaloJets.Rho_EtaMax= cms.double(4.4)
kt6PFJets.doRhoFastjet = True
kt6PFJets.Rho_EtaMax= cms.double(4.4)
##-------------------- Turn-on the FastJet jet area calculation for your favorite algorithm -----------------------
#ak4CaloJets.doAreaFastjet = True
#ak4CaloJets.Rho_EtaMax= cms.double(4.5)
ak4PFJets.doAreaFastjet = True
ak4PFJets.Rho_EtaMax= cms.double(4.5)

ak4PFJetsL1Offset   = ak4PFJetsL2L3.clone(correctors = ['ak4PFL1Offset'])
ak4PFJetsL1Area     = ak4PFJetsL2L3.clone(correctors = ['ak4PFL1Fastjet'])


# Residual corrections not in DB ? --------------------------------------------------------------------------------
#ak4CaloResidual.useCondDB = False
#ak4PFResidual.useCondDB = False 

# tests ------------------------------------------------------------------------------------------------------------
#ak4PFJets.Active_Area_Repeats = 5
#ak4PFJets.GhostArea = 0.005 
#kt6PFJets.Active_Area_Repeats = 5
#kt6PFJets.GhostArea = 0.005


L1FastJet = cms.Sequence (kt6PFJets * ak4PFJets) 
#L1FastJet = cms.Sequence (kt6PFJets * ak4PFJets * ak4PFJetsL1Area * ak4PFJetsL1Offset)
#L1FastJet = cms.Sequence (ak4PFJets * kt6PFJets * ak4PFJetsL1Area * ak4PFJetsL1Offset)
