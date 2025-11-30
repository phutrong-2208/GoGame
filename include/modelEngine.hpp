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
        bool startProcess(const std :: string& kataGo, const std :: string& model){
            SECURITY_ATTRIBUTES sa{};
            sa.nLength = sizeof(sa);
            sa.bInheritHandle = TRUE;
            
            //stdout pipe
            CreatePipe(&stdoutRead, &stdoutWrite, &sa, 0);
            SetHandleInformation(stdoutRead, HANDLE_FLAG_INHERIT, 0);

            //stdin pipe
            CreatePipe(&stdinRead, &stdinWrite, &sa, 0);
            SetHandleInformation(stdinWrite, HANDLE_FLAG_INHERIT, 0);

            STARTUPINFOA si{};
            si.cb = sizeof(si);
            si.hStdOutput = stdoutWrite;
            si.hStdError = stdoutWrite;
            si.hStdInput = stdinRead;
            si.dwFlags |= STARTF_USESTDHANDLES;
            
            std :: string cmd = "\"" + kataGo + "\" gtp" " -model \"" + model + "\"";

            if(!CreateProcessA(NULL, cmd.data(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)){
                std :: cout << "CreateProcess Failed" << GetLastError() << "\n";
                return false;
            }

            CloseHandle(stdoutWrite);
            CloseHandle(stdinRead);
            return true;
        }

        void sendCommand(const std :: string& s){
            DWORD written;
            std :: string cmd = s + "\n";
            WriteFile(stdinWrite, cmd.c_str(), cmd.size(), &written, NULL);   
        }

        std :: string readCommand(void){
            char buffer[4096];
            DWORD readBytes = 0;
            std :: string result;
            while(true){
                BOOL ok = ReadFile(stdoutRead, buffer, sizeof(buffer) - 1, &readBytes, NULL);
                if(!ok || readBytes == 0) break;
                buffer[readBytes] = '\0';
                result += buffer; 
                if(result.find("\n\n") != std :: string :: npos || 
                   result.find("\r\n\r\n") != std :: string :: npos)
                    break;
            }
            return result;
        }        

        void stopProcess(void){
            sendCommand("quit");
            WaitForSingleObject(pi.hProcess, 3000);         
            CloseHandle(stdinWrite);
            CloseHandle(stdoutRead);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
};

    