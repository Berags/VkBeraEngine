#include <string>
#include <iostream>
#include "Application.h"

int main() {
#ifdef NDEBUG
    // Removing std::cout prints to the console if not in debug mode
    // https://stackoverflow.com/a/30185095/12445398
    std::cout.setstate(std::ios_base::failbit);
#endif
    Application app{};

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
