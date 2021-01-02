g++ MyStack.h MyStack.cpp Evaluate.h Evaluate.cpp  Pipe/Server.cpp -o Pipe/Server && cd Pipe && Server.exe

cd Client
g++ Client.cpp -o Client && Client.exe


>g++ _Memory.h _Memory.cpp SharedMemory.h SharedMemory.cpp Process.h Process.cpp ProcessA.cpp -o ProcessA && ProcessA.exe

g++ MyStack.h MyStack.cpp Evaluate.h Evaluate.cpp _Memory.h _Memory.cpp SharedMemory.h SharedMemory.cpp Process.h Process.cpp ProcessB.h ProcessB.cpp -o ProcessB && ProcessB.exe