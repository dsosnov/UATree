#include "UATree/UADataFormat/interface/MySiPixelCluster.h"
#include <iostream>

using namespace std;

ClassImp(MySiPixelCluster)

MySiPixelCluster::MySiPixelCluster(){
  this->Reset();
}

MySiPixelCluster::~MySiPixelCluster(){}

void MySiPixelCluster::Reset() {
  charge = -1;
  x = -1;
  y = -1;
  z = -1;
  sizeX = -1;
  sizeY = -1;
}

void MySiPixelCluster::Print() {
}
