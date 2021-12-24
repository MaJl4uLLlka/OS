#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <Windows.h>

#define FILE_PATH L"D:/3ks1/OS/Completed Labs/Lab9/OS09_01.txt"
BOOL printFileTxt(LPWSTR FileName);
HANDLE openFile(LPWSTR FileName);
BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row);

int main()
{
    setlocale(LC_ALL, "");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printFileTxt((LPWSTR)FILE_PATH);

    insRowFileTxt((LPWSTR)FILE_PATH, (LPWSTR)L"Пятинкина Анита(0)", 0);
    insRowFileTxt((LPWSTR)FILE_PATH, (LPWSTR)L"Шабуня Алексей(-1)", -1);
    insRowFileTxt((LPWSTR)FILE_PATH, (LPWSTR)L"Шуст Юрий(5)", 5);
    insRowFileTxt((LPWSTR)FILE_PATH, (LPWSTR)L"Иван Гришин(7)", 7);

    insRowFileTxt((LPWSTR)FILE_PATH, (LPWSTR)L"Шуст Юрий(15)", 65);

    printFileTxt((LPWSTR)FILE_PATH);
    system("pause");
    return 0;
}

BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row)
{
    HANDLE file;
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int positionAfter = 0;
    bool rowFound = false;

    try
    {
        if ((file = openFile(FileName)) == NULL)
        {
            throw "Opening file failed";
        }

        LockFile(file, 0, 0, 0, 0);

        if (GetFileSizeEx(file, fileSize))
        {
            char* cstr = new char[wcslen(str) * sizeof(char)];
            wcstombs(cstr, str, strlen(cstr));
            char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
            char* bufAfterIns = new char[(fileSize->QuadPart + 3 + strlen(cstr)) * sizeof(char)];
            ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));

            ZeroMemory(bufAfterIns, (fileSize->QuadPart + 1 + strlen(cstr)) * sizeof(char));
            DWORD n = NULL;
            try
            {
                if (ReadFile(file, buf, fileSize->QuadPart, &n, NULL))
                {
                    buf[fileSize->QuadPart] = '\0';
                    while (buf[position] != '\0')
                    {
                        if ((rowCount == row || row == 0) && !rowFound)
                        {
                            for (int i = 0; i < strlen(cstr); i++)
                            {
                                bufAfterIns[positionAfter++] = cstr[i];
                            }
                            bufAfterIns[positionAfter++] = '\r';
                            bufAfterIns[positionAfter++] = '\n';
                            rowFound = true;
                            rowCount++;
                        }
                        if (buf[position] == '\n')
                        {
                            rowCount++;
                        }
                        bufAfterIns[positionAfter++] = buf[position++];
                        if (buf[position] == '\0')
                        {
                            break;
                        }

                    }
                    if (row == MAXDWORD)
                    {
                        bufAfterIns[positionAfter++] = '\r';
                        bufAfterIns[positionAfter++] = '\n';
                        for (int i = 0; i < strlen(cstr); i++)
                        {
                            bufAfterIns[positionAfter++] = cstr[i];
                        }
                        rowFound = true;
                        rowCount++;
                    }
                    bufAfterIns[positionAfter] = '\0';
                }
                if (rowFound)
                {
                    printf("\n--- After insertion row №%d:\n%s\n", row == MAXDWORD ? -1 : row, bufAfterIns);
                    if (SetFilePointer(file, 0, 0, FILE_BEGIN) == 0)
                    {
                        if (WriteFile(file, bufAfterIns, strlen(bufAfterIns), &n, NULL))
                        {
                            printf("\nRow inserted successfully\n");
                        }
                        else
                        {
                            throw "WriteFile failed";
                        }
                        if (!SetEndOfFile(file))
                        {
                            throw "SetEndOfFile failed";
                        }

                        delete[] buf;
                        delete[] bufAfterIns;
                    }
                    else
                    {
                        throw "SetFilePointer failed";
                    }
                }
                else
                {
                    throw "Row isn't found";
                }
            }
            catch (const char* error)
            {
                delete[] buf;
                delete[] bufAfterIns;
                CloseHandle(file);
                throw error;
            }
        }
        else
        {
            throw "GetFileSizeEx failed";
        }
    }
    catch (const char* error)
    {
        delete fileSize;
        std::cout << "Error: " << error << std::endl;
        return FALSE;
    }

    CloseHandle(file);
    delete fileSize;
    return TRUE;
}

BOOL printFileTxt(LPWSTR FileName)
{
    //7. Функция printFileTxt выводит 
    //в стандартный поток вывода содержимое файла. 
    try
    {
        HANDLE file;

        if ((file = openFile(FileName)) == NULL)
            return FALSE;

        char buf[2048];
        DWORD countBytes = NULL;
        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(file, &buf, 1000, &countBytes, NULL);
        if (!b) throw "write file failed";
        std::cout << "--Read file " << countBytes << "byte succesfull: " << std::endl << std::endl << buf << std::endl << std::endl;
        CloseHandle(file);
        return TRUE;
    }
    catch (const char* error)
    {
        std::cout << "Error: " << error << std::endl;
        return FALSE;
    }
}

HANDLE openFile(LPWSTR FileName)
{
    try
    {
        HANDLE fileHandle = CreateFile(FileName,
            GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_READ, NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            CloseHandle(fileHandle);
            throw "create file failed";
        }

        std::cout << "Create  or open file successfull\n";
        return fileHandle;
    }
    catch (const char* error)
    {
        std::cout << "Error: " << error << '\n';
        return NULL;
    }
}