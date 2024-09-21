#include <iostream>
#include <windows.h>

// Function to convert virtual key code to character
char getCharFromKey(KBDLLHOOKSTRUCT* p)
{
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    // Check for shift and caps lock
    if (GetKeyState(VK_CAPITAL) & 0x0001) // Caps Lock is on
    {
        keyboardState[VK_SHIFT] = 0x80; // Simulate holding shift
    }

    // Prepare for the actual character conversion
    WORD charCode;
    ToAscii(p->vkCode, p->scanCode, keyboardState, &charCode, 0);
    
    return (char)charCode;
}

// Callback function for keyboard hook
LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            // If a key is pressed
            KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
            char key = getCharFromKey(p);
            std::cout << key;
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
