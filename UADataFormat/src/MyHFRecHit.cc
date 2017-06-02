#include "UATree/UADataFormat/interface/MyHFRecHit.h"
#include <iostream>

using namespace std;

ClassImp(MyHFRecHit)

MyHFRecHit::MyHFRecHit(){
  this->Reset();
}

MyHFRecHit::~MyHFRecHit(){}

void MyHFRecHit::Print() {

  cout<<"HF rechit information: "<<endl;

  cout<<"ieta: "<<this->ieta<<endl;
  cout<<"iphi: "<<this->iphi<<endl;
  cout<<"depth: "<<this->depth<<endl;
  cout<<"energy: "<<this->energy<<endl;
  cout<<"time: "<<this->time<<endl;
}

