#include <iostream>
#include <windows.h>
#include <cwctype>
#include <map>

// Function to check if Shift key is pressed
bool isShiftPressed()
{
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

// Function to check if Caps Lock is active
bool isCapsLockActive()
{
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}

// Mapping of numeric keys to their shifted counterparts
std::map<int, char> shiftedNumbers = {
    { '1', '!' }, { '2', '@' }, { '3', '#' }, { '4', '$' }, { '5', '%' },
    { '6', '^' }, { '7', '&' }, { '8', '*' }, { '9', '(' }, { '0', ')' }
};

// Mapping of shifted special characters
std::map<int, char> shiftedSpecialChars = {
    { VK_OEM_1, ':' }, { VK_OEM_PLUS, '+' }, { VK_OEM_COMMA, '<' },
    { VK_OEM_MINUS, '_' }, { VK_OEM_PERIOD, '>' }, { VK_OEM_2, '?' },
    { VK_OEM_3, '~' }, { VK_OEM_4, '{' }, { VK_OEM_5, '|' },
    { VK_OEM_6, '}' }, { VK_OEM_7, '"' }
};

// Keyboard hook callback function
LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        BYTE keyboardState[256];
        GetKeyboardState(keyboardState);

        wchar_t buffer[5] = { 0 };
        int result = ToUnicode(p->vkCode, p->scanCode, keyboardState, buffer, 4, 0);

        if (result > 0)
        {
            wchar_t key = buffer[0];

            // Handle Enter key for new lines
            if (p->vkCode == VK_RETURN)
            {
                std::wcout << std::endl;
            }
            else if (p->vkCode == VK_BACK)
            {
                // Handle backspace to simulate correct deletion on console
                std::wcout << L'\b' << L' ' << L'\b';
            }
            else
            {
                bool shiftPressed = isShiftPressed();
                bool capsLockActive = isCapsLockActive();

                // Handle shifted numbers and symbols
                if (shiftPressed && shiftedNumbers.find(p->vkCode) != shiftedNumbers.end())
                {
                    key = shiftedNumbers[p->vkCode]; // Convert number to corresponding symbol
                }
                else if (shiftPressed && shiftedSpecialChars.find(p->vkCode) != shiftedSpecialChars.end())
                {
                    key = shiftedSpecialChars[p->vkCode]; // Convert special character to its shifted counterpart
                }
                else if (iswalpha(key))
                {
                    // Handle upper/lower case correctly based on Shift and Caps Lock
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
