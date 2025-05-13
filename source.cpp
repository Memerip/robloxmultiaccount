#include <windows.h>
#include <iostream>

bool debug = false;

void PrintHeader() {
    std::cout << R"(

  __  __       _ _   _   _____           _                       
 |  \/  |     | | | (_) |_   _|         | |                      
 | \  / |_   _| | |_ _    | |  _ __  ___| |_ __ _ _ __   ___ ___ 
 | |\/| | | | | | __| |   | | | '_ \/ __| __/ _` | '_ \ / __/ _ \
 | |  | | |_| | | |_| |  _| |_| | | \__ \ || (_| | | | | (_|  __/
 |_|  |_|\__,_|_|\__|_| |_____|_| |_|___/\__\__,_|_| |_|\___\___|

  By @memerip, version: a1.0
  ---------------------------------------------------------------
  This tool enables you to open multiple Roblox instances.
  Using this tool involves risks such as account bans

)";
}

int main() {
    PrintHeader();

    std::cout << "\n[?] Are you aware of the potential risks associated with using this tool? (Y/N): ";
    char response;
    std::cin >> response;

    if (response != 'Y' && response != 'y') {
        std::cout << "[*] Cancelled by user.\n";
        return 0;
    }

    HANDLE hMutex = CreateMutexW(nullptr, TRUE, L"ROBLOX_singletonMutex");
    if (!hMutex && debug) {
        std::cerr << "[-] Failed to create mutex.\n";
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        std::cout << "[*] Roblox might already be running. Close all instances first.\n";
    }
    else {
        if (debug) {
            std::cout << "[+] Mutex 'ROBLOX_singletonMutex' created successfully.\n";
        }
        std::cout << "[+] Complete! You may now open multiple Roblox instances.\n";
    }

    std::cout << "\n[*] Press Ctrl+C to exit. Leaving this window open keeps the mutex active.\n";
    while (true) Sleep(100000);

    return 0;
}
