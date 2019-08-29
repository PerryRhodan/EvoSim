#pragma once

#include <memory>

#include "worlds/World.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Display
{
public:
Display();


void display(std::shared_ptr<World> p_world);


private:
cv::Mat evosim_image;


};