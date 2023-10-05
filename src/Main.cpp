#include "Application.h"

int main(int argc, char *argv[])
{
    Application* app = new Application("window");
    return app->Run();
}