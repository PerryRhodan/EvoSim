#include "../include/Display.h"


Display::Display()
{
    /////////////////////////////////////////////////////////////////
    // display debug image with position of agents, TODO
    evosim_image = cv::Mat::zeros( 900, 900, CV_8UC3 );
    
}

void Display::display(std::shared_ptr<World> p_world)
{

    // TODO assuming world size of 10*10
    double tiles_size = 900 / p_world->width;

    // draw world tiles
    for (int w=0; w<p_world->width; ++w)
    {
        for (int h=0; h<p_world->height; ++h)
        {
            cv::Rect2i rect(w*tiles_size, h*tiles_size, tiles_size, tiles_size);
            cv::rectangle( evosim_image,
                rect,
                cv::Scalar(10,50,80),
                CV_FILLED
                );
        }
    }

    // draw agents
    for(const auto agent : p_world->m_vpagents)
    {
        agent->print();
        cv::Point center(agent->position(0,0) - agent->state.size/2
                        , agent->position(1,0) - agent->state.size/2);
        cv::circle( evosim_image,
            center,
            agent->state.size,
            cv::Scalar( 0, 150, 255 ),
            cv::FILLED,
            cv::LINE_8 );
    }

    cv::imshow( "EvoSim", evosim_image );
    cv::waitKey(10) & 0XFF;
}