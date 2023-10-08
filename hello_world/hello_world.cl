kernel void hello_world(global char* message) {
    int index = get_global_id(0);
    message[index] = 'H';
}
