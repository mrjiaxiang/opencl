#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include <malloc.h> // needed for alloca
#endif              // _WIN32

#if defined(linux) || defined(__APPLE__) || defined(__MACOSX)
#include <alloca.h>
#endif // linux

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

void displayPlatformInfo(cl_platform_id id, cl_platform_info name,
                         std::string str) {
    cl_int err_num;
    std::size_t param_value_size;

    err_num = clGetPlatformInfo(id, name, 0, NULL, &param_value_size);
    if (err_num != CL_SUCCESS) {
        std::cerr << "Failed to find OpenCL platform " << str << "."
                  << std::endl;
        return;
    }

    char *info = (char *)alloca(sizeof(char) * param_value_size);
    err_num = clGetPlatformInfo(id, name, param_value_size, info, NULL);
    if (err_num != CL_SUCCESS) {
        std::cerr << "Failed to find OpenCL platform " << str << "."
                  << std::endl;
        return;
    }

    std::cout << "\t" << str << ":\t" << info << std::endl;
}

int main(int argc, char **argv) {

    cl_int err_num;
    cl_uint num_platforms;
    cl_platform_id *platform_Ids;
    cl_context context = 0;

    err_num = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err_num != CL_SUCCESS || num_platforms <= 0) {
        std::cerr << "Failed to find any OpenCL platform." << std::endl;
    }
    std::cout << "err int : " << err_num << "  "
              << "num_platforms : " << num_platforms << std::endl;

    platform_Ids =
        (cl_platform_id *)alloca(sizeof(cl_platform_id) * num_platforms);

    err_num = clGetPlatformIDs(num_platforms, platform_Ids, NULL);
    if (err_num != CL_SUCCESS) {
        std::cerr << "Failed to find any OpenCL platforms." << std::endl;
    }

    std::cout << "Number of platforms: \t" << num_platforms << std::endl;

    for (cl_uint i = 0; i < num_platforms; i++) {
        displayPlatformInfo(platform_Ids[i], CL_PLATFORM_PROFILE,
                            "CL_PLATFORM_PROFILE");
        displayPlatformInfo(platform_Ids[i], CL_PLATFORM_VERSION,
                            "CL_PLATFORM_VERSION");
        displayPlatformInfo(platform_Ids[i], CL_PLATFORM_VENDOR,
                            "CL_PLATFORM_VENDOR");
        displayPlatformInfo(platform_Ids[i], CL_PLATFORM_EXTENSIONS,
                            "CL_PLATFORM_EXTENSIONS");
    }

    return 0;
}