//
#include "include/EvoSim.h"

#include <Eigen/Dense>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

EvoSim::EvoSim()
{
 
  
}

EvoSim::~EvoSim()
{

}

bool EvoSim::run()
{





    boost::asio::io_service io_service;
    boost::asio::steady_timer iteration_timer{io_service, std::chrono::seconds{2}};
//    iteration_timer.async_wait([](const boost::system::error_code &ec)
//		    { std::cout << "2 seconds have passed\n"; });
//    io_service.run();

    return true;
}

double EvoSim::calculate_sqrt(double value)
{
    return sqrt(value);
}

