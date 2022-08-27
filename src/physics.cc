#include "physics.hh"

//pentru a descrie tipul interactiunilor care implica particulele generate...

//constructorul
MyPhysicsList::MyPhysicsList()
{
  RegisterPhysics (new G4EmStandardPhysics()); //Register for elm. interaction
  RegisterPhysics (new G4OpticalPhysics());  //for Optical phys interaction

  //for radioactive Decay laws;
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

//destructorul;
MyPhysicsList::~MyPhysicsList()
{}
