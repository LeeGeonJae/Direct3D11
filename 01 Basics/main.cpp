#include <Windows.h>
#include "TutorialApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    TutorialApp Game(hInstance);

    Game.Initialize(1024, 768);
    Game.Run();

    return 0;
}
