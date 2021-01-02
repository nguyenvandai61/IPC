#include <iostream>
#include <Windows.h>

int main()
{
    // char bufferRead[1024];
    char buffer[1024];
    char firstExp[] = "6+3*5";
    HANDLE pipe = CreateFileA("\\\\.\\pipe\\Cryst", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (pipe != INVALID_HANDLE_VALUE) {
        strcpy(buffer, firstExp);
        // strcat(buffer, "\0");
        
        // char buffer[] = "6+3";
        DWORD bytesRead;
        DWORD bytesWritten;
        while (strcmp(buffer, "q") != 0) {
            std::cout << "Sending expression " << buffer << " ";
            WriteFile(pipe, static_cast<LPCVOID>(buffer), sizeof(buffer)+1, &bytesWritten, NULL);
            std::cout << "Done!\n";
            while (ReadFile(pipe, static_cast<LPVOID>(buffer), sizeof(double)+1, &bytesRead, NULL))
            {
                double res;
                memcpy(&res, buffer, sizeof(double));
                std::cout << "Result: " << res << "\n";
                // memset(buffer, 0, sizeof(buffer));
                break;
            }
            
            std::cout << "Type the math expression(q - quit): "; 
            std::cin >> buffer;
        }
        std::cout << "Close pipe!"; 
        CloseHandle(pipe);
    }
    else {
        std::cout << "Could not get a handle to the pipe!\n";
        return 1;
    }
    return 0;
}