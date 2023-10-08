__kernel void helloWorld(__global const char* message) {
    printf("%s\n", message);
}