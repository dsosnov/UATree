#include "UATree/UADataFormat/interface/MyLambdas.h" 
#

ClassImp(MyLambdas)

MyLambdas::MyLambdas():MyPart(){
  this->Reset();
}

MyLambdas::~MyLambdas(){}

void MyLambdas::Print(){

  cout << "[MyLambdas::Print()]" << endl;

  cout << "chi2n : " << chi2n << endl;
  cout << "dz    : " << dz    << endl;  
  cout << "d0    : " << d0    << endl;  
  cout << "edz   : " << edz   << endl; 
  cout << "ed0   : " << ed0   << endl; 
  cout << "ept   : " << ept   << endl; 
  cout << "vx    : " << vx    << endl;  
  cout << "vy    : " << vy    << endl;  
  cout << "vz    : " << vz    << endl;  
  cout << "mass  : " << mass  << endl; 

}

void MyLambdas::Reset(){

  chi2n = 0;
  dz    = 0;
  d0    = 0;
  edz   = 0;
  ed0   = 0;
  ept   = 0;
  vx    = 0;
  vy    = 0;
  vz    = 0;
  mass  = 0;
  pt    = 0;
  eta   = 0;
  phi   = 0;
  vertexx = 0;
  vertexy = 0;
  vertexz = 0;
  
}


