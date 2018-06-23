#include <iostream>
#include <signal.h>

#include "include/EvoSim.h"



void sighandler(int sig)
{
    std::cout << "Signal " << sig << " caught..." << std::endl;

}

//void chatterCallback(const std_msgs::String::ConstPtr& msg)
//{
//    ROS_INFO("I heard: [%s]", msg->data.c_str());
//}

int main (int argc, char *argv[])
{
    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);

    fprintf(stdout, "%s Version v%d.%d.%d\n\n", argv[0], VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);



    return 0;
}

