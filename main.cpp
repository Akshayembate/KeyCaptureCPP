#include <iostream>
#include <windows.h>

bool isShiftPressed()
{
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

bool isCapsLockActive()
{
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        BYTE keyboardState[256];
        GetKeyboardState(keyboardState);

        wchar_t buffer[5] = {0};
        int result = ToUnicode(p->vkCode, p->scanCode, keyboardState, buffer, 4, 0);

        if (result > 0)
        {
            wchar_t key = buffer[0];

            // Handle upper/lower case correctly based on Shift and Caps Lock
            bool shiftPressed = isShiftPressed();
            bool capsLockActive = isCapsLockActive();

            if (isalpha(key))
            {
                if (shiftPressed != capsLockActive)  // XOR to check if one is active but not both
                {
                    key = towupper(key);
                }
                else
                {
                    key = towlower(key);
                }
            }

            std::wcout << key;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    // Set the keyboard hook
    HHOOK hhkLowLevelKydb = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, 0, 0);

    // Keep the program running to listen for keyboard input
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook the keyboard hook when done
    UnhookWindowsHookEx(hhkLowLevelKydb);
    return 0;
}
