#include "noether.hpp"
#include "lighting.hpp"

int main(int argc, char** argv) {
    Noether::LightingExample* lighting = new Noether::LightingExample();
    lighting->Run();
    return 0;
}