#include <iostream>
#include <cstring>
char doubleText[1024];
int main() {
    double d = 21;
    std::cout << std::hex<<&d << "\n";
    strcpy(doubleText, (char*) &d);
    strcat(doubleText, "\0");
    std::cout << strlen(doubleText);
    for (int i = 0 ; i < strlen(doubleText); i++) {
        std::cout <<std::hex<< doubleText[i];
    }
    
}