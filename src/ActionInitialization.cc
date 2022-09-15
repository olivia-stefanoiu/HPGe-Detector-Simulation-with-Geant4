#include "ActionInitialization.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::BuildForMaster() const {
    auto *runAction = new MyRunAction();
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const {

    auto *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    auto *runAction = new MyRunAction();
    SetUserAction(runAction);

    auto *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    auto *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);

}
