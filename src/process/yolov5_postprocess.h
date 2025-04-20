#ifndef _RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
#define _RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_

#include <stdint.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include "types/datatype.h"

namespace yolov5
{
    int post_process_rgb(std::vector<tensor_data_s> &outputs, int height, int width,cv::Mat &output_rgb_image);
}

#endif // _RKNN_ZERO_COPY_DEMO_POSTPROCESS_H_
