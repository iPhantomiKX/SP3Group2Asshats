#include "Application.h"

#include "CheckMemoryLeak.h"

int main(void)
{
    Application &app = Application::GetInstance();
    app.Init();
    app.Run();
    app.Exit();

    CheckMemoryLeaks();
}