Keyboard Hook Program
This C++ program captures and prints keyboard inputs at a system level. It uses a low-level keyboard hook to monitor all keyboard events and prints each key typed, handling cases like uppercase, lowercase, numbers, special characters, and functional keys like Enter and Backspace. The program runs indefinitely until it is terminated.

Features
Captures all keyboard inputs, including special characters and functional keys.
Handles shift and caps lock to distinguish between upper and lower case characters.
Supports detection of shifted numeric and special characters (e.g., Shift+1 produces !).
Outputs keys to the console in real-time, accurately representing what's typed, including handling the Enter and Backspace keys.
Dependencies
Windows OS: This program uses Windows-specific APIs such as SetWindowsHookEx and GetKeyState from the Windows API.
Compiler: The program is compatible with any C++ compiler that supports the Windows API (e.g., MinGW or MSVC).
How It Works
Keyboard Hook Setup: The program sets up a low-level keyboard hook using SetWindowsHookEx. It intercepts all keyboard events (keydown) at the system level.

Key Processing: The program uses the ToUnicode function to translate virtual key codes into readable characters. It also checks the status of the Shift and Caps Lock keys to determine the correct case for alphabetic characters.

Special Handling:

Shifted numbers and symbols are handled with specific mappings (e.g., Shift+1 becomes !, Shift+' becomes ").
Functional keys like Enter and Backspace are processed to simulate their normal behavior in the console (e.g., Enter adds a new line, Backspace deletes a character).
How to Build
Prerequisites
Windows OS: This code is Windows-specific due to the use of the Windows API.
C++ Compiler: Install any C++ compiler that supports Windows API functions. For example:
MinGW (for Windows)
Visual Studio (MSVC)
Compilation with MinGW
If you're using MinGW, you can compile the program using the following command:
g++ -o keyboard_hook.exe keyboard_hook.cpp -lgdi32

Running the Program
After compiling, run the generated executable:
./keyboard_hook.exe

The program will now print every key you type in real-time to the console. To stop the program, close the console window or terminate it manually.

Known Limitations
Windows-Specific: This program only works on Windows as it relies on Windows API functions like SetWindowsHookEx and GetKeyState.
No Termination Mechanism: The program runs indefinitely, so you'll need to close it manually (e.g., via Ctrl + C or closing the console window).
Special Characters Mapping: Some special characters may require custom mappings depending on the keyboard layout.