#include <CL/cl.hpp>

#include <fstream>
#include <iostream>

int main() {
    // 获取所有可用的平台
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // 获取第一个平台
    cl::Platform platform = platforms[0];

    // 获取平台上的所有设备
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    // 获取第一个设备
    cl::Device device = devices[0];

    // 创建上下文
    cl::Context context(device);

    // 创建命令队列
    cl::CommandQueue queue(context, device);

    // 读取OpenCL内核源文件
    std::ifstream kernelFile("hello_world.cl");
    std::string kernelSource((std::istreambuf_iterator<char>(kernelFile)),
                             std::istreambuf_iterator<char>());

    // 创建程序对象
    cl::Program::Sources sources(
        1, std::make_pair(kernelSource.c_str(), kernelSource.length() + 1));
    cl::Program program(context, sources);

    // 构建程序
    program.build("-cl-std=CL1.2");

    // 创建内核对象
    cl::Kernel kernel(program, "hello_world");

    // 创建缓冲区对象
    const int bufferSize = 5;
    cl::Buffer buffer(context, CL_MEM_WRITE_ONLY, sizeof(char) * bufferSize);

    // 设置内核参数
    kernel.setArg(0, buffer);

    // 执行内核
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(bufferSize),
                               cl::NullRange);

    // 读取结果
    char result[bufferSize];
    queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(char) * bufferSize,
                            result);

    // 输出结果
    std::cout << "Result: " << result << std::endl;

    return 0;
}