#ifndef __MyPart_H__
#define __MyPart_H__

#include "Math/PxPyPzE4D.h"
#include "Math/LorentzVector.h"
#include "TLorentzVector.h"

class MyPart : public TObject {

  public :

    typedef double Scalar;
    typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<Scalar> > LorentzVector;

    MyPart();
    virtual ~MyPart();
    
    virtual void Reset();
    virtual void Print();

    Double_t       charge;
    LorentzVector  fP4;

    TLorentzVector vmpi();
    virtual Bool_t operator< ( const MyPart& );
    
    // ROOT LorentzVector interface
    Scalar Px()     const { return fP4.Px();    }
    Scalar X()      const { return fP4.Px();    }
    Scalar Py()     const { return fP4.Py();    }
    Scalar Y()      const { return fP4.Py();    }
    Scalar Pz()     const { return fP4.Pz();    }
    Scalar Z()      const { return fP4.Pz();    }
    Scalar E()      const { return fP4.E();     }
    Scalar T()      const { return fP4.E();     }
    Scalar M2()     const { return fP4.M2();    }
    Scalar M()      const { return fP4.M();     }
    Scalar R()      const { return fP4.R();     }
    Scalar P()      const { return fP4.R();     }
    Scalar P2()     const { return P() * P();   }
    Scalar Perp2( ) const { return fP4.Perp2(); }
    Scalar Pt()     const { return fP4.Pt();    }
    Scalar Rho()    const { return fP4.Pt();    }
    Scalar Mt2()    const { return fP4.Mt2();   }
    Scalar Mt()     const { return fP4.Mt();    }
    Scalar Et2()    const { return fP4.Et2();   }
    Scalar Et()     const { return fP4.Et();    }
    Scalar Phi()    const { return fP4.Phi();   }
    Scalar Theta()  const { return fP4.Theta(); }
    Scalar Eta()    const { return fP4.Eta();   }

    Scalar x()     const { return fP4.Px();     }
    Scalar y()     const { return fP4.Py();     }
    Scalar z()     const { return fP4.Pz();     }
    Scalar t()     const { return fP4.E();      }
    Scalar px()    const { return fP4.Px();     }
    Scalar py()    const { return fP4.Py();     }
    Scalar pz()    const { return fP4.Pz();     }
    Scalar e()     const { return fP4.E();      }
    Scalar r()     const { return fP4.R();      }
    Scalar theta() const { return fP4.Theta();  }
    Scalar phi()   const { return fP4.Phi();    }
    Scalar rho()   const { return fP4.Rho();    }
    Scalar eta()   const { return fP4.Eta();    }
    Scalar pt()    const { return fP4.Pt();     }
    Scalar perp2() const { return fP4.Perp2();  }
    Scalar mag2()  const { return fP4.M2();     }
    Scalar mag()   const { return fP4.M();      }
    Scalar mt()    const { return fP4.Mt();     }
    Scalar mt2()   const { return fP4.Mt2();    }

    Scalar energy() const { return fP4.E();      }
    Scalar mass()   const { return fP4.M();      }
    Scalar mass2()  const { return fP4.M2();     }

    /*LorentzVector& SetE  ( Scalar a )  { LorentzVector& p4 = fP4.SetE  (a);
                                                                 return p4; }
    LorentzVector& SetEta( Scalar a )  { LorentzVector& p4 = fP4.SetEta(a);
                                                                 return p4; }
    LorentzVector& SetM  ( Scalar a )  { LorentzVector& p4 = fP4.SetM  (a);
                                                                 return p4; }
    LorentzVector& SetPhi( Scalar a )  { LorentzVector& p4 = fP4.SetPhi(a);
                                                                 return p4; }
    LorentzVector& SetPt ( Scalar a )  { LorentzVector& p4 = fP4.SetPt (a);
                                                                 return p4; }
    LorentzVector& SetPx ( Scalar a )  { LorentzVector& p4 = fP4.SetPx (a);
                                                                 return p4; }
    LorentzVector& SetPy ( Scalar a )  { LorentzVector& p4 = fP4.SetPy (a);
                                                                 return p4; }
    LorentzVector& SetPz ( Scalar a )  { LorentzVector& p4 = fP4.SetPz (a);
                                                                 return p4; }*/

    LorentzVector& SetXYZT (Scalar xx, Scalar yy, Scalar zz, Scalar tt) {
       LorentzVector& p4 = fP4.SetPxPyPzE(xx,yy,zz,tt);
       return p4;
    }
    LorentzVector& SetPxPyPzE (Scalar xx, Scalar yy, Scalar zz, Scalar ee) {
       LorentzVector& p4 = fP4.SetPxPyPzE(xx,yy,zz,ee);
       return p4;
    }
    LorentzVector& SetPtEtaPhiM (Scalar pt, Scalar eta, Scalar phi, Scalar m) { 
       TLorentzVector p4_aux; p4_aux.SetPtEtaPhiM(pt,eta,phi,m);
       Scalar xx = p4_aux.Px(); Scalar yy = p4_aux.Py(); Scalar zz = p4_aux.Pz(); Scalar ee = p4_aux.E();
       LorentzVector& p4 = fP4.SetPxPyPzE(xx,yy,zz,ee);
       return p4;
    }

  private:

    ClassDef (MyPart,1)
};



#endif


