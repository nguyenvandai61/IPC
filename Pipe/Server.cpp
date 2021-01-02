#include <iostream>
#include <array>
#include <Windows.h>
#include "../Evaluate.h"

int main()
{
    Evaluate* evaluate = new Evaluate();
    char buffer[1024];
    char *resultText;
    double result;
    HANDLE pipe = CreateNamedPipeA("\\\\.\\pipe\\Cryst", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, sizeof(buffer), sizeof(buffer), NMPWAIT_USE_DEFAULT_WAIT, NULL);
    while (pipe != INVALID_HANDLE_VALUE) {
        if (ConnectNamedPipe(pipe, NULL)) {
         //Setting a breakpoint here will never trigger.
            std::cout << "Client connect successfully!\n";
            DWORD bytesRead = 0;    
            DWORD bytesWritten;
            while (ReadFile(pipe, static_cast<LPVOID>(buffer), sizeof(buffer), &bytesRead, NULL)) {
                std::cout << "Expression: " << buffer << std::endl;
                if (strcmp(buffer, "") == 0) continue;

                result = evaluate->calc(buffer);
                std::cout << "Result: "<< result << "\n";
                // Clear buffer
                memset(buffer, 0, sizeof(buffer));
                memcpy(buffer, &result, sizeof(double));
                // // Convert result to text
                WriteFile(pipe, static_cast<LPVOID>(buffer), sizeof(double), &bytesWritten, NULL);
                memset(buffer, 0, sizeof(double));
            }
        }
        DisconnectNamedPipe(pipe);
    }
    return 0;
}