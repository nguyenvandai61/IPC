#include <iostream>
#include <Windows.h>

int main()
{
    char bufferRead[1024];
    HANDLE pipe = CreateFileA("\\\\.\\pipe\\Cryst", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (pipe != INVALID_HANDLE_VALUE) {
        char buffer[] = "6+3*5";
        DWORD bytesRead;
        DWORD bytesWritten;
        WriteFile(pipe, static_cast<LPCVOID>(buffer), sizeof(buffer), &bytesWritten, NULL);
        std::cout << "Done!\n";
        while (ReadFile(pipe, static_cast<LPVOID>(buffer), sizeof(double), &bytesRead, NULL))
        {
            double res;
            memcpy(&res, buffer, sizeof(double));
            std::cout << "Result: " << res << "\n";
            
        }
        
        CloseHandle(pipe);
    }
    else {
        std::cout << "Could not get a handle to the pipe!\n";
        return 1;
    }
    return 0;
}