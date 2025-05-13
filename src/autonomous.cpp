#include "autonomous.h"

rd::Selector selector = rd::Selector({
    {"Best auton", best_auton},
    {"Simple auton", simple_auton},
    {"Good auton", good_auton},
});

void auton() {
    selector.run_auton();
}

void best_auton() {
    // Add your best autonomous code here
}

void simple_auton() {
    // Add your simple autonomous code here
}

void good_auton() {
    // Add your good autonomous code here
}