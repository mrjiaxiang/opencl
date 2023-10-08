#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline void checkErr(cl_int err, const char *name) {
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
        exit(EXIT_FAILURE);
    }
}

const int ARRAY_SIZE = 1000;

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

    std::string cl_path = "/home/melody/slam/opencl/array_add/array_add.cl";
    std::ifstream srcFile(cl_path);
    checkErr(srcFile.is_open() ? CL_SUCCESS : -1, "reading array_add.cl");

    std::string srcProg(std::istreambuf_iterator<char>(srcFile),
                        (std::istreambuf_iterator<char>()));

    const char *src = srcProg.c_str();
    size_t length = srcProg.length();

    cl::Program::Sources sources;
    sources.push_back({src, length});

    cl::Program program(context, sources);
    program.build({intelDevice});

    cl::Kernel kernel(program, "arrayAdd");

    float result[ARRAY_SIZE];
    float a[ARRAY_SIZE];
    float b[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = (float)i;
        b[i] = (float)(i * 2);
    }

    cl::Buffer input_buffer_a(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                              sizeof(float) * ARRAY_SIZE, a);

    cl::Buffer input_buffer_b(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                              sizeof(float) * ARRAY_SIZE, b);

    cl::Buffer output_buffer(context, CL_MEM_WRITE_ONLY,
                             sizeof(float) * ARRAY_SIZE);

    kernel.setArg(0, input_buffer_a);
    kernel.setArg(1, input_buffer_b);
    kernel.setArg(2, output_buffer);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(ARRAY_SIZE),
                               cl::NullRange);
    queue.enqueueReadBuffer(output_buffer, CL_TRUE, 0,
                            sizeof(float) * ARRAY_SIZE, result);

    queue.finish();

    // 输出结果
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::cout << result[i] << " ";
    }

    return 0;
}