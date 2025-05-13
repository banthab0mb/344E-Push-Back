#include "autonomous.h"

rd::Selector selector = rd::Selector({
    {"Best auton", bestAuton},
    {"Simple auton", simpleAuton},
    {"Good auton", goodAuton},
});

void auton() {
    selector.run_auton();
}

void bestAuton() {
    // Add your best autonomous code here
}

void simpleAuton() {
    // Add your simple autonomous code here
}

void goodAuton() {
    // Add your good autonomous code here
}