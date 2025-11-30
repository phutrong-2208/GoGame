#include "modelEngine.hpp"
bool KataGo :: startProcess(const std :: string& kataGo, const std :: string& model, const std  :: string& config){
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
    
    std :: string cmd = "\"" + kataGo + "\" gtp" " -model \"" + model + "\" -config \"" + config + "\"";

    if(!CreateProcessA(NULL, cmd.data(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)){
        std :: cout << "CreateProcess Failed" << GetLastError() << "\n";
        return false;
    }

    CloseHandle(stdoutWrite);
    CloseHandle(stdinRead);
    return true;
}
void KataGo :: sendCommand(const std :: string& s){
    DWORD written;
    std :: string cmd = s + "\n";
    WriteFile(stdinWrite, cmd.c_str(), cmd.size(), &written, NULL);   
}
std :: string KataGo :: readCommand(void){
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
void KataGo :: stopProcess(void){
    sendCommand("quit");
    WaitForSingleObject(pi.hProcess, 3000);         
    CloseHandle(stdinWrite);
    CloseHandle(stdoutRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}