#pragma once
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "Data.h"
#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

#define BUFSIZE 512
Data _dt;
bool svstp = false;

int start_server() {
    /* hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"), 
                       GENERIC_READ | GENERIC_WRITE, 
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(hPipe,
                  "Hello Pipe\n",
                  12,   // = length of string + terminating '\0' !!!
                  &dwWritten,
                  NULL);

        CloseHandle(hPipe);
    }*/
    HANDLE hPipe;
    char  chBuf[BUFSIZE];
    BOOL   fSuccess = FALSE;
    DWORD  cbRead, cbToWrite, cbWritten, dwMode;
    const char* pReady = "ready";
    const char* pStop = "stop";
    list<string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    
    /*  HANDLE hPipe;
    char buffer[1024];
    DWORD dwRead;


    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
                            PIPE_ACCESS_DUPLEX,
                            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
                            1,
                            1024 * 16,
                            1024 * 16,
                            NMPWAIT_USE_DEFAULT_WAIT,
                            NULL);
    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
            {
    buffer[dwRead] = '\0';

    printf("%s", buffer);
}
        }

        DisconnectNamedPipe(hPipe);
    }*/
    while (1)
    {
        hPipe = CreateFile(
            TEXT("\\\\.\\pipe\\ICS0025"),
            GENERIC_READ |
            GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hPipe != INVALID_HANDLE_VALUE)
            break;

        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            printf("Can't open the pipe");
            return -1;
        }

        if (!WaitNamedPipe(TEXT("\\\\.\\pipe\\ICS0025"), 15000))
        {
            printf("Timed out after 15 seconds.");
            return -1;
        }
    }

    dwMode = PIPE_READMODE_MESSAGE;
    fSuccess = SetNamedPipeHandleState(
        hPipe,
        &dwMode,
        NULL,
        NULL);
    if (!fSuccess)
    {
        printf("SetNamedPipeHandleState failed.\n");
        return -1;
    }
    do
    {
        if (svstp) {
            fSuccess = WriteFile(
                hPipe,
                pStop,
                5,
                &cbWritten,
                NULL);
        }

        fSuccess = WriteFile(
            hPipe,
            pReady,
            6,
            &cbWritten,
            NULL);

        if (!fSuccess)
        {
            printf("WriteFile to pipe failed.\n");
            return -1;
        }

        printf("\nDelivered\n");

        fSuccess = ReadFile(
            hPipe,
            chBuf,
            BUFSIZE * sizeof(char),
            &cbRead,
            NULL);

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA) {
            printf("Connection lost\n");
            break;
        }

        char  group = chBuf[0];
        int subgroup = atoi(&chBuf[2]);
        char* delimiter = &(chBuf[5]);
        string* itemstring = new string;
        while (*delimiter != '>') {
            if (*delimiter != '<')
                itemstring->push_back(*delimiter);
            delimiter++;
        }
        delimiter += 2;
        int day = atoi(delimiter);
        delimiter += 3;
        string sMonth = string();
        for (int cMonth = 0; cMonth < 3; cMonth++) {
            sMonth.push_back(*delimiter);
            delimiter++;
        }
        int nMonth = distance(months.begin(), find(months.begin(), months.end(), sMonth)) + 1;
        delimiter++;
        int year = atoi(delimiter);
        std::chrono::milliseconds waitingTime(500);
        Date itemDate(day, nMonth, year);
        _dt.InsertItem(group, subgroup, *itemstring, itemDate);
    } while (fSuccess);
    return 1;
}

int main() {

    bool check = true;
    printf("Type one of the command word:\n1->connect\n2->stop\n3->exit\n");
    string main_cmd;
    int cmd_input;
    while (check) {
        cin >> main_cmd;
        if (main_cmd == "connect") {
            cmd_input = 0;
        }
        else if (main_cmd == "stop") {
            cmd_input = 1;
        }
        else if (main_cmd == "exit") {
            cmd_input = 2;
        }
        else {
            cmd_input = 3;
        }

        switch (cmd_input) {
        case 0: {
            if (svstp) {
                svstp = false;
            }
            thread connectThread(start_server);
            connectThread.detach();
            break;
        }

        case 1: {
            if (svstp) {
                printf("Connection closed");
                break;
            }
            svstp = true;
            break;
        }
        case 2: {
            check = false;
            printf("Item:");
            _dt.PrintAll();
            break;
        }
        default: {
            printf("Invalid");
            break;
        }
        }
    }
    return 0;
}