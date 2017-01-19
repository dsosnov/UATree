// Genaral Tracks and Vertex
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/V0Candidate/interface/V0Candidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool KshortDebug = false;
bool LambdaDebug = false;

void UABaseTree::GetAllKshorts( const edm::Event& iEvent ){
  outks.clear();

  edm::Handle<reco::VertexCompositeCandidateCollection> kshorts;
  iEvent.getByLabel(edm::InputTag("generalV0Candidates","Kshort"),kshorts);

  outks.assign( kshorts->size(), MyKshorts() );

  Int_t i = 0;
  for(reco::VertexCompositeCandidateCollection::const_iterator ks = kshorts->begin(); ks!=kshorts->end(); ++ks)
    {
      outks[i].mass = ks->mass();
      outks[i].pt   = ks->pt();
      outks[i].eta   = ks->eta();
      outks[i].phi   = ks->phi();
      outks[i].vertexx   = ks->vertex().X();
      outks[i].vertexy   = ks->vertex().Y();
      outks[i].vertexz   = ks->vertex().Z();
  

      if(KshortDebug) outks[i].Print();
    } // end for K0S

}

void UABaseTree::GetAllLambdas( const edm::Event& iEvent ){
  outlambda.clear();

  edm::Handle<reco::VertexCompositeCandidateCollection> lambdas;
  iEvent.getByLabel(edm::InputTag("generalV0Candidates","Lambda"),lambdas);

  outlambda.assign( lambdas->size(), MyLambdas() );

  Int_t i = 0;
  for(reco::VertexCompositeCandidateCollection::const_iterator lam = lambdas->begin(); lam!=lambdas->end(); ++lam)
    {
      outlambda[i].mass = lam->mass();
      outlambda[i].pt   = lam->pt();
      outlambda[i].eta   = lam->eta();
      outlambda[i].phi   = lam->phi();
      outlambda[i].vertexx   = lam->vertex().X();
      outlambda[i].vertexy   = lam->vertex().Y();
      outlambda[i].vertexz   = lam->vertex().Z();

      if(LambdaDebug) outlambda[i].Print();
    } // end for Lambda

}

