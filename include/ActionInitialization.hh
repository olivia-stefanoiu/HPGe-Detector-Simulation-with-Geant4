#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
     MyActionInitialization();
     ~MyActionInitialization()override;

   void BuildForMaster() const override;
   void Build() const override; //particle gun function("main") - compute the steps... build particles
};

#endif
