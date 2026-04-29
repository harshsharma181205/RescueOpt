#include "Dispatcher.h"
#include<iostream>
using namespace std;

int main() {
    system("chcp 65001 > nul");
    cout << "\n🚨 RESCUEOPT - Intelligent Disaster Response System 🚨\n";
    cout << "================================================\n";
    
    Dispatcher dispatcher;
    dispatcher.run();
    
    return 0;
}