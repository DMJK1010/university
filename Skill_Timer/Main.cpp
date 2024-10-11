#include <iostream>
#include <Windows.h>
#include <thread>

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // 키보드 후킹 처리 코드 작성
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        int vkCode = kbStruct->vkCode;

        // 특정 키에 대한 처리를 추가합니다.
        // 예를 들어, 'A' 키를 누르면 "A 키 눌림"을 출력하도록 할 수 있습니다.
        std::cout << "Key pressed: " << char(vkCode) << std::endl;
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void HookThread()
{
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, NULL, 0);
    if (hook == NULL)
    {
        std::cerr << "Hook installation failed." << std::endl;
        return;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
}

int main()
{
    std::thread hookThread(HookThread);
    hookThread.join(); // 쓰레드 종료 대기

    return 0;
}
