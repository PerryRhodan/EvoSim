#include <iostream>
#include <signal.h>
#include <string>

#include "include/EvoSim.h"


void sighandler(int sig)
{
    std::cout << "Signal " << sig << " caught..." << std::endl;
    std::cout << "Stopping simulation..." << std::endl;
}

int main (int argc, char *argv[])
{
    // set up ros node 
    ros::init(argc, argv, "evosim");

    //signal(SIGABRT, &sighandler);
    //signal(SIGTERM, &sighandler);
    //signal(SIGINT, &sighandler);
    fprintf(stdout, "%s Version v%d.%d.%d\n\n", argv[0], VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    
    // run simulation
    EvoSim sim;
    sim.run();

    std::cout << "main ended" << std::endl;

    return 0;
}

