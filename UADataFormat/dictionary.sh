#!/bin/bash

if [ ! -f interface/LinkDef.h ];then mv interface/LinkDefh interface/LinkDef.h;fi

rootcint -f eventdict.cc -c -p \
   UATree/UADataFormat/interface/MyBeamSpot.h \
   UATree/UADataFormat/interface/MyCastorDigi.h \
   UATree/UADataFormat/interface/MyCastorJet.h \
   UATree/UADataFormat/interface/MyCastorRecHit.h \
   UATree/UADataFormat/interface/MyDiJet.h \
   UATree/UADataFormat/interface/MyEvtId.h \
   UATree/UADataFormat/interface/MyFwdGap.h \
   UATree/UADataFormat/interface/MyMet.h \
   UATree/UADataFormat/interface/MyGenMet.h \
   UATree/UADataFormat/interface/MyGenKin.h \
   UATree/UADataFormat/interface/MyGenPart.h \
   UATree/UADataFormat/interface/MyGenJet.h \
   UATree/UADataFormat/interface/MyPUSumInfo.h \
   UATree/UADataFormat/interface/MyHLTrig.h \
   UATree/UADataFormat/interface/MyL1Trig.h \
   UATree/UADataFormat/interface/MyL1TrigOld.h \
   UATree/UADataFormat/interface/MyMITEvtSel.h \
   UATree/UADataFormat/interface/MyPart.h \
   UATree/UADataFormat/interface/MySimVertex.h \
   UATree/UADataFormat/interface/MyVertex.h \
   UATree/UADataFormat/interface/MyTracks.h \
   UATree/UADataFormat/interface/MyElectron.h \
   UATree/UADataFormat/interface/MyMuon.h \
   UATree/UADataFormat/interface/MyBaseJet.h \
   UATree/UADataFormat/interface/MyJet.h \
   UATree/UADataFormat/interface/MyCaloJet.h \
   UATree/UADataFormat/interface/MyTrackJet.h \
   UATree/UADataFormat/interface/MyPFJet.h \
   UATree/UADataFormat/interface/MyPFCand.h \
   UATree/UADataFormat/interface/MyCaloTower.h \
   UATree/UADataFormat/interface/MyFSCHit.h \
   UATree/UADataFormat/interface/MyFSCDigi.h \
   UATree/UADataFormat/interface/MyFSCInfo.h \
   UATree/UADataFormat/interface/MyKshorts.h \
   UATree/UADataFormat/interface/MyLambdas.h \
   UATree/UADataFormat/interface/MySiStripCluster.h \
   UATree/UADataFormat/interface/MySiPixelCluster.h \
   UATree/UADataFormat/interface/MyD0.h \
   UATree/UADataFormat/interface/MyDstar.h \
   UATree/UADataFormat/interface/MyZDCDigi.h \
   UATree/UADataFormat/interface/MyHFRecHit.h \
   UATree/UADataFormat/interface/LinkDef.h \

mv interface/LinkDef.h interface/LinkDefh
mv eventdict.cc src/
cp eventdict_rdict.pcm $CMSSW_BASE/lib/$SCRAM_ARCH/
