#include "client_framework.h"
#include "include/file/file_utils.h"

int main(int argc, char* argv[])
{
    ToolEngine::FileUtils::getInstance().setExePath(argv[0]);
    ToolEngine::ClientFramework::run();
    return 0;
}