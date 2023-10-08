#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const unsigned int input_signal_width = 8;
const unsigned int input_signal_height = 8;
const int dataSize = input_signal_width * input_signal_height;
float inputSignal[input_signal_width][input_signal_height] = {
    {3, 1, 1, 4, 8, 2, 1, 3}, {4, 2, 1, 1, 2, 1, 2, 3},
    {4, 4, 4, 4, 3, 2, 2, 2}, {9, 8, 3, 8, 9, 0, 0, 0},
    {9, 3, 3, 9, 0, 0, 0, 0}, {0, 9, 0, 8, 0, 0, 0, 0},
    {3, 0, 8, 8, 9, 4, 4, 4}, {5, 9, 8, 1, 8, 1, 1, 1}};

const int kernelSize = 3;
const int kernelDataSize = kernelSize * kernelSize;
float kernelData[kernelSize][kernelSize] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

inline void checkErr(cl_int err, const char *name) {
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    // 获取所有可用的平台
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // 遍历平台，查找Intel的平台
    cl::Platform intelPlatform;
    for (const auto &platform : platforms) {
        std::string platformName = platform.getInfo<CL_PLATFORM_NAME>();
        if (platformName.find("Intel") != std::string::npos) {
            std::cout << "Found Intel platform: " << platformName << std::endl;
            intelPlatform = platform;
            break;
        }
    }

    // 获取平台上的所有设备
    std::vector<cl::Device> devices;
    intelPlatform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    // 遍历设备，选择Intel的GPU设备
    cl::Device intelDevice;
    for (const auto &device : devices) {
        std::string deviceName = device.getInfo<CL_DEVICE_NAME>();
        std::cout << "Found Intel GPU device: " << deviceName << std::endl;
        intelDevice = device;
        break;
    }

    cl::Context context({intelDevice});

    cl::CommandQueue queue(context, intelDevice);

    std::string cl_path = "/home/melody/slam/opencl/convolution/convolution.cl";
    std::ifstream srcFile(cl_path);
    checkErr(srcFile.is_open() ? CL_SUCCESS : -1, "reading Convolution.cl");

    std::string srcProg(std::istreambuf_iterator<char>(srcFile),
                        (std::istreambuf_iterator<char>()));

    const char *src = srcProg.c_str();
    size_t length = srcProg.length();

    cl::Program::Sources sources;
    sources.push_back({src, length});

    cl::Program program(context, sources);
    program.build({intelDevice});

    float output_data[36];
    cl::Kernel kernel(program, "convolve");

    cl::Buffer input_buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            sizeof(float) * dataSize, inputSignal);

    cl::Buffer output_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 36);

    kernel.setArg(0, input_buffer);
    kernel.setArg(1, cl::Local(sizeof(float) * kernelDataSize));
    kernel.setArg(2, output_buffer);
    kernel.setArg(3, input_signal_width);
    kernel.setArg(4, kernelSize);

    queue.enqueueWriteBuffer(input_buffer, CL_TRUE, 0, sizeof(float) * dataSize,
                             inputSignal);

    cl::LocalSpaceArg local_mem = cl::Local(sizeof(float) * kernelDataSize);

    queue.enqueueNDRangeKernel(
        kernel, cl::NullRange,
        cl::NDRange(input_signal_width, input_signal_height), cl::NullRange);

    queue.enqueueReadBuffer(output_buffer, CL_TRUE, 0, sizeof(float) * 36,
                            output_data);
    // 打印输出数据
    for (int i = 0; i < 36; i++) {
        std::cout << output_data[i] << " ";
        if ((i + 1) % 6 == 0) {
            std::cout << std::endl;
        }
    }

    return 0;
}