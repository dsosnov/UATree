#ifndef __MyLambdas_H__
#define __MyLambdas_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"
#include <iostream>

using namespace std;

class MyLambdas : public MyPart {

  public :
    MyLambdas();
    virtual ~MyLambdas();

    void Print();
    void Reset();

    Double_t chi2n;
    Double_t dz  , d0 ;
    Double_t edz , ed0 , ept ; 
    Double_t vx, vy, vz ;
    Double_t mass, pt, eta, phi ;
    Double_t vertexx, vertexy, vertexz;


  private:

  ClassDef (MyLambdas,1)
};

#endif

