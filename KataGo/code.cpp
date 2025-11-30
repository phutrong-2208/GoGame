#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
STARTUPINFOA si;
PROCESS_INFORMATION pi;
HANDLE hRead = NULL, hWrite = NULL;
int gridSize = 19;


bool StartKataGo() {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;


    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        cerr << "CreatePipe failed" << endl;
        return false;
    }

    if (!SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0)) {
        cerr << "SetHandleInformation failed" << endl;
        return false;
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdInput = hRead;   // Standard Input của Katago là đầu đọc của pipe
    si.hStdOutput = hWrite; // Standard Output của Katago là đầu ghi của pipe
    si.hStdError = hWrite;  // Standard Error cũng là đầu ghi của pipe
    si.dwFlags |= STARTF_USESTDHANDLES;

    ZeroMemory(&pi, sizeof(pi));

    string cmd = ".\\katago.exe gtp -model model.gz -config default_gtp.cfg";
    vector<char> cmdBuffer(cmd.begin(), cmd.end());
    cmdBuffer.push_back(0); // Null terminator

    if (!CreateProcessA(
        NULL,
        cmdBuffer.data(),
        NULL, NULL,
        TRUE,
        0,
        NULL, NULL,
        &si, &pi
    )) {
        cerr << "CreateProcess failed (" << GetLastError() << ") for Katago." << endl;
        return false;
    }

    string result;
    char buffer[300];
    DWORD bytesRead;
    while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        result += buffer;
    }

    return true;
}

#include <iostream> // Cần thiết cho cerr

// ... (Phần code trên) ...

string SendGtpCommand(const std::string& cmd) {
    if (hWrite == NULL || hRead == NULL) return "ERROR: KataGo not running.";

    // 1. Gửi lệnh (Write)
    string fullCmd = cmd + "\n";
    DWORD bytesWritten;
    if (!WriteFile(hWrite, fullCmd.c_str(), fullCmd.length(), &bytesWritten, NULL)) {
        return "ERROR: WriteFile failed.";
    }

    // 2. Đọc phản hồi (Read)
    string result;
    char buffer[512]; // Tăng buffer size để đảm bảo đọc đủ một lần
    DWORD bytesRead;

    // Đọc lặp cho đến khi nhận được một phản hồi GTP hoàn chỉnh
    while (true) {
        // Cố gắng đọc từ pipe. Sử dụng PeekNamedPipe để kiểm tra dữ liệu có sẵn.
        // Dùng ReadFile đơn giản hơn nếu bạn chấp nhận block (chờ)
        if (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            result += buffer;

            // Phản hồi GTP hợp lệ thường kết thúc bằng dòng trống ("\n\n")
            // hoặc dòng bắt đầu bằng dấu "=" (chỉ trong một số trường hợp đặc biệt)
            if (result.find("\n\n") != string::npos) {
                 // Cắt bớt phần sau dòng trống cuối cùng (nếu có)
                 size_t pos = result.rfind("\n\n");
                 if (pos != string::npos) {
                     result.resize(pos + 2); // Giữ lại cả hai ký tự xuống dòng
                 }
                 break; // Đã nhận đủ phản hồi
            }
        } else if (GetLastError() != ERROR_SUCCESS) {
            // Xử lý lỗi đọc pipe (nếu KataGo đóng hoặc lỗi khác)
            break;
        }
        // Thêm một chút độ trễ để tránh chiếm dụng CPU quá mức khi chờ phản hồi
        Sleep(10);
    }

    return result;
}

int main() {
    StartKataGo();
    // Cần đợi một chút để Katago khởi động và in thông báo chào mừng
    Sleep(2000);

    // Gửi lệnh và in phản hồi ra màn hình C++
    string boardsize_cmd = "boardsize " + to_string(gridSize);
    string boardsize_res = SendGtpCommand(boardsize_cmd);
    cout << "Boardsize Response: " << boardsize_res << "\n";

    // Bỏ chú thích vòng lặp để kiểm tra
    for (int x = 0; x < 2; x++) { // Chỉ chạy 2 lần để test
        int i = rand() % 19, j = rand() % 19;
        string play_cmd = "play b " + string(1, 'A' + j) + to_string(gridSize - i);
        string play_res = SendGtpCommand(play_cmd);
        cout << "Play Response: " << play_res << "\n";

        string respond = SendGtpCommand("genmove w");
        cout << "Genmove Response: " << respond << "\n";
    }

    SendGtpCommand("quit");
    WaitForSingleObject(pi.hProcess, 5000);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hRead);
    CloseHandle(hWrite);
}

