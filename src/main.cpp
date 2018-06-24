#include <iostream>
#include <signal.h>
#include <string>

#include "include/EvoSim.h"


int main (int argc, char *argv[])
{
    // set up ros node 
    ros::init(argc, argv, "evosim");
    fprintf(stdout, "%s Version v%d.%d.%d\n\n", argv[0], VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    
    // run simulation
    EvoSim sim;
    sim.run();

    std::cout << "Done" << std::endl;
    return 0;
}

