#include <iostream>
#include "client_framework.h"
#include "tbb/tbb.h"


int main()
{
    tbb::parallel_invoke(
        []() {std::cout << "TBB!" << std::endl; },
        []() {std::cout << "Hello" << std::endl; }
    );
    ToolEngine::ClientFramework framework;
    framework.onStart();
    return 0;
}