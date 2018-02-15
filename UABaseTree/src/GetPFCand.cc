// Description: Function to retrieve PFCandidates

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"


Bool_t PFCandDebug = false;

void UABaseTree::GetRecoPFCand(const edm::Event& iEvent , const edm::EDGetTokenT<PFCandidateCollection>& PFCandidateToken_ , vector<MyPFCand>& PFCandVector){

   PFCandVector.clear();

   Handle<PFCandidateCollection> PFCands;
   iEvent.getByToken(PFCandidateToken_, PFCands);
   
   PFCandVector.assign( PFCands->size() , MyPFCand() );

   Int_t i = 0;
   for (PFCandidateCollection::const_iterator iPFCand = PFCands->begin() ; iPFCand != PFCands->end() ; ++iPFCand , ++i) {
     
     //PFCandVector[i].SetPxPyPzE(iPFCand->px() , iPFCand->py() , iPFCand->pz() , sqrt(iPFCand->momentum().mag2()+MASS_MU*MASS_MU));
     PFCandVector[i].SetPxPyPzE(iPFCand->px() , iPFCand->py() , iPFCand->pz() , iPFCand->energy() );
     PFCandVector[i].charge = iPFCand->charge();
     PFCandVector[i].particleId = static_cast<MyPFCand::ParticleType>(iPFCand->particleId());

     if(PFCandDebug) PFCandVector[i].Print();


   } // end for PFCandCollection 

}


void UABaseTree::GetAllPFCands( const edm::Event& iEvent ){
  for (auto i: pfcands_) this->GetRecoPFCand(iEvent , PFCandidateTokens_.at(i.label()), allPFCands[i.label()]);
}
