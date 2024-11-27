#define STB_IMAGE_IMPLEMENTATION

#include <stdexcept>

#include "VulkanApp.h"
#include "UtilRand.h"

int main() {

    //Set seed for Random Engine
    UtilRand::setRESeed();

    VulkanApp app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Entrypoint for Release build, when Linker subsystem is Windows
int WinMain() {
    return main();
}