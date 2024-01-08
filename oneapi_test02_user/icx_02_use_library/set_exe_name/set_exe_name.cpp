#include <set_exe_name.hpp>

int main(void) {
    try {

        static_setup();

        test_std();

        test_sycl();

        test_compare();

    }
    catch (std::exception& e) {
        printf("Exception : %s\n", e.what());
    }
    catch (...) {
        printf("Exception : unknown exception.\n");
    }

    return 0;
}
