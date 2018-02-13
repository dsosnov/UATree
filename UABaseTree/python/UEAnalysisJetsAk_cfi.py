import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.TrackJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
from RecoJets.JetProducers.ak4TrackJets_cfi import ak4TrackJets

FastjetWithAreaPU = cms.PSet(
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    UE_Subtraction = cms.string('no')
)


ueAk4ChgGenJet500 = ak4GenJets.clone(
    src = cms.InputTag("chargeParticles"),
    jetPtMin       = cms.double(1.0),
    inputEtMin     = cms.double(0.5)
)

ueAk4TracksJet500 =  ak4TrackJets.clone(
    src = cms.InputTag("goodTracks"),
    jetPtMin       = cms.double(1.0),
    inputEtMin     = cms.double(0.5)
)

#ueAk4TracksJet.jetType = 'BasicJet'

UEAnalysisJetsAkOnlyMC = cms.Sequence(ueAk4ChgGenJet500)
UEAnalysisJetsAkOnlyReco = cms.Sequence(ueAk4TracksJet500)
UEAnalysisJetsAk = cms.Sequence(UEAnalysisJetsAkOnlyMC*UEAnalysisJetsAkOnlyReco)
