#include <iostream>
#include <windows.h>

// function for checking the the key is pressed or not
LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            // if the key is pressed
            KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

            char key = (char)p->vkCode;
            std::cout << key;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    // set the keyboard hook
    HHOOK hhkLowLevelKydb = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, 0, 0);

    // keep the program running to listen for the keyboard inout
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // unhook the keyboard hook when done
    UnhookWindowsHookEx(hhkLowLevelKydb);
    return 0;
}
