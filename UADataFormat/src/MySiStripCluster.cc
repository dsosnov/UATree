#include "UATree/UADataFormat/interface/MySiStripCluster.h"
#include <iostream>

using namespace std;

ClassImp(MySiStripCluster)

MySiStripCluster::MySiStripCluster(){
  this->Reset();
}

MySiStripCluster::~MySiStripCluster(){}

void MySiStripCluster::Reset() {
  nStripClusters = -1; 
}

void MySiStripCluster::Print() {
}
