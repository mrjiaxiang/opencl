#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

std::string readKernelFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

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

    // 读取内核代码文件
    const std::string kernel_file =
        "/home/melody/slam/opencl/hello_world/helloWorld.cl";
    std::string kernelCode = readKernelFile(kernel_file);

    // 定义并编译内核代码
    cl::Program::Sources sources;
    sources.push_back({kernelCode.c_str(), kernelCode.length()});

    cl::Program program(context, sources);
    program.build({intelDevice});

    // 创建内核
    cl::Kernel kernel(program, "helloWorld");

    // 创建输入缓冲区
    const char *message = "Hello, World!";
    cl::Buffer messageBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                             sizeof(char) * (strlen(message) + 1),
                             (void *)message);

    // 设置内核参数
    kernel.setArg(0, messageBuffer);

    // 在设备上执行内核
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1));

    // 等待内核执行完毕
    queue.finish();

    std::cout << "Kernel executed." << std::endl;

    return 0;
}