#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>

class KataGo {
    private:
        HANDLE stdinWrite = NULL;
        HANDLE stdinRead = NULL;
        HANDLE stdoutWrite = NULL;
        HANDLE stdoutRead = NULL;
        PROCESS_INFORMATION pi{};
    public:
        bool startProcess(const std :: string& kataGo, const std :: string& model, const std :: string& config);
        void sendCommand(const std :: string& s);
        std :: string readCommand(void);
        void stopProcess(void);
};

extern KataGo katago;

    