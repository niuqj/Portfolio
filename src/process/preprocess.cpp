// 预处理

#include "preprocess.h"

#include "utils/logging.h"
#include "im2d.h"
#include "rga.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>

void print_tensor_shapes(const std::vector<tensor_data_s>& tensors) {
    for (size_t i = 0; i < tensors.size(); ++i) {
        const tensor_data_s& tensor = tensors[i];
        
        // 打印张量的形状信息
        std::cout << "Tensor " << i << " shape: [";
        for (uint32_t j = 0; j < tensor.attr.n_dims; ++j) {
            std::cout << tensor.attr.dims[j];
            if (j < tensor.attr.n_dims - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}

// opencv resize
void cvimg2tensor(const cv::Mat &img, uint32_t width, uint32_t height, tensor_data_s &tensor)
{
    // img has to be 3 channels
    //
    if (img.channels() != 3)
    {
        NN_LOG_ERROR("img has to be 3 channels");
        exit(-1);
    }
    // BGR to RGB
    cv::Mat img_rgb;
    cv::cvtColor(img, img_rgb, cv::COLOR_BGR2RGB);
    // resize img
    cv::Mat img_resized;
    // resize img
    cv::resize(img_rgb, img_resized, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    // BGR to RGB
    memcpy(tensor.data, img_resized.data, tensor.attr.size);
    //void* inputs_tensor = tensor.data;
    //uint8_t* tensor_data = static_cast<uint8_t*>(tensor.data);
    //cv::Mat img1(height, width, CV_8UC3);  // 创建一个空的 8位 3通道图像
    // 遍历每个像素并填充图像
    //for (int i = 0; i < height; i++) {
        //for (int j = 0; j < width; j++) {
            //int pixel_index = (i * width + j) * 3; // 每个像素有三个通道（RGB）

            // 从 tensor_data 中获取 R、G、B 值
            //uint8_t r_value = tensor_data[pixel_index];        // 红色通道
            //uint8_t g_value = tensor_data[pixel_index + 1];    // 绿色通道
            //uint8_t b_value = tensor_data[pixel_index + 2];    // 蓝色通道

            // 将像素值填充到 OpenCV 图像中 (OpenCV 使用 BGR 顺序)
            //img1.at<cv::Vec3b>(i, j) = cv::Vec3b(b_value, g_value, r_value);  // OpenCV 默认是 BGR 顺序
        //}
    //}

    // 保存或显示图像
    //cv::imwrite("output_image.jpg", img1);  // 保存图像为 output_image.jpg
}