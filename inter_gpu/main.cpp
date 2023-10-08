#include <CL/cl.hpp>
#include <iostream>

int main() {
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

    // 创建OpenCL上下文
    cl::Context context({intelDevice});

    // 创建命令队列
    cl::CommandQueue queue(context, intelDevice);

    // 定义并编译内核代码
    std::string kernelCode = R"(
        __kernel void helloWorld() {
            printf("Hello, World!\n");
        }
    )";

    cl::Program::Sources sources;
    sources.push_back({kernelCode.c_str(), kernelCode.length()});

    cl::Program program(context, sources);
    program.build({intelDevice});

    // 创建内核
    cl::Kernel kernel(program, "helloWorld");

    // 在设备上执行内核
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1));

    // 等待内核执行完毕
    queue.finish();

    std::cout << "Kernel executed." << std::endl;

    return 0;
}