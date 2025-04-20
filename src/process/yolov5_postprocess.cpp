#include "yolov5_postprocess.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include "types/datatype.h"
#include <iostream>
#include <cfloat>

namespace yolov5
{
    // 打印张量形状和数据类型（可选调试用）
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
            
            // 打印张量的数据类型
            std::cout << "Data type: ";
            switch (tensor.attr.type) {
                case NN_TENSOR_INT8:
                    std::cout << "INT8" << std::endl;
                    break;
                case NN_TENSOR_UINT8:
                    std::cout << "UINT8" << std::endl;
                    break;
                case NN_TENSOR_FLOAT:
                    std::cout << "FLOAT" << std::endl;
                    break;
                case NN_TENSOR_FLOAT16:
                    std::cout << "FLOAT16" << std::endl;
                    break;
                default:
                    std::cout << "Unknown" << std::endl;
                    break;
            }
            
            // 打印张量的布局类型
            if (tensor.attr.layout == NN_TENSOR_NCHW) {
                std::cout << "Layout: NCHW" << std::endl;
            } else if (tensor.attr.layout == NN_TENSOR_NHWC) {
                std::cout << "Layout: NHWC" << std::endl;
            } else {
                std::cout << "Layout: Unknown" << std::endl;
            }
        }
    }
        // 标准版本
    float fp16_to_fp32(uint16_t h) {
        // 使用标准库函数（C++11及以上）
        return std::ldexp((h & 0x3ff) | ((h & 0x7c00) == 0 ? 0 : 0x400), (int)((h & 0x7c00) >> 10) - 25) * (h & 0x8000 ? -1 : 1);
    }
    int post_process_rgb(std::vector<tensor_data_s> &outputs, int height, int width, cv::Mat &output_rgb_image) {
        // 获取输出张量数据
        void* output_tensor = outputs[0].data;
        // 假设模型输出是FP32或FP16类型
        float* tensor_data_f32 = nullptr;
        uint16_t* tensor_data_f16 = nullptr;
        bool is_fp16 = true;  // 根据实际情况设置
        
        // 根据数据类型获取数据指针
        if (is_fp16) {
            tensor_data_f16 = static_cast<uint16_t*>(output_tensor);
        } else {
            tensor_data_f32 = static_cast<float*>(output_tensor);
        }
        
        // 创建OpenCV图像
        output_rgb_image = cv::Mat(height, width, CV_8UC3);
        
        // 处理NCHW格式的数据 (1, 3, height, width)
        int channel_size = height * width;
        
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                float r, g, b;
                int r_idx = h * width + w;
                int g_idx = channel_size + h * width + w;
                int b_idx = 2 * channel_size + h * width + w;
                
                if (is_fp16) {
                    float r = fp16_to_fp32(tensor_data_f16[r_idx]) * 255.0f;
                    float g = fp16_to_fp32(tensor_data_f16[g_idx]) * 255.0f;
                    float b = fp16_to_fp32(tensor_data_f16[b_idx]) * 255.0f;
                } else {
                    r = tensor_data_f32[r_idx] * 255.0f;
                    g = tensor_data_f32[g_idx] * 255.0f;
                    b = tensor_data_f32[b_idx] * 255.0f;
                }
                output_rgb_image.at<cv::Vec3b>(h, w) = cv::Vec3b(
                    static_cast<uint8_t>(b),
                    static_cast<uint8_t>(g),
                    static_cast<uint8_t>(r)
                );
            }
        }
        
        // 保存图像到文件（可选）
        cv::imwrite("output_image.jpg", output_rgb_image);
        
        return 0;  // 成功处理
    }
}