#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <Windows.h>

#define FILE_PATH L"D:/3ks1/OS/Completed Labs/Lab9/OS09_01.txt"
BOOL printFileTxt(LPWSTR FileName);
HANDLE openFile(LPWSTR FileName);
BOOL delRowFileTxt(LPWSTR FileName, DWORD row);

int main()
{
	system("@chcp 1251 > nul");
	printFileTxt((LPWSTR)FILE_PATH);

    delRowFileTxt((LPWSTR)FILE_PATH, 1);
    delRowFileTxt((LPWSTR)FILE_PATH, 3);
    delRowFileTxt((LPWSTR)FILE_PATH, 8);
    delRowFileTxt((LPWSTR)FILE_PATH, 10);

    delRowFileTxt((LPWSTR)FILE_PATH, 100);

    printFileTxt((LPWSTR)FILE_PATH);
	system("pause");
	return 0;
}

BOOL delRowFileTxt(LPWSTR FileName, DWORD row)
{
    HANDLE file;
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int positionAfter = 0;
    bool rowFound = false;

    try
    {
        if (row <= 0)
        {
            throw "Invalid number of raw";
        }

        if ((file = openFile(FileName)) == NULL)
        {
            throw "Opening file failed";
        }

        if (GetFileSizeEx(file, fileSize))
        {
            char* buf = new char[fileSize->QuadPart + 1];
            char* bufAfterDel = new char[fileSize->QuadPart + 1];
            ZeroMemory(buf, fileSize->QuadPart);
            ZeroMemory(bufAfterDel, fileSize->QuadPart);
            DWORD n = NULL;

            try
            {
                if (ReadFile(file, buf, fileSize->QuadPart, &n, NULL))
                {
                    buf[fileSize->QuadPart] = '\0';
                    while (buf[position] != '\0')
                    {
                        if (buf[position] == '\n')
                        {
                            rowCount++;
                        }
                        if (rowCount == row)
                        {
                            rowFound = true;
                            rowCount++;
                            position++;
                            while (buf[position] != '\n' && buf[position] != '\0')
                            {
                                position++;
                            }
                            if (row == 1)
                            {
                                position++;
                            }
                        }
                        bufAfterDel[positionAfter++] = buf[position++];
                        if (buf[position] == '\0')
                        {
                            break;
                        }
                    }
                    bufAfterDel[positionAfter] = '\0';
                }
                if (rowFound)
                {
                    std::cout << "\n --- After deletion row #" << row << std::endl << bufAfterDel << std::endl;
                    if (SetFilePointer(file, 0, 0, FILE_BEGIN) == 0)
                    {
                        if (WriteFile(file, bufAfterDel, strlen(bufAfterDel), &n, NULL))
                        {
                            std::cout << "Row deleted succesfully" << std::endl;
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
                        delete[] bufAfterDel;
                    }
                    else
                    {
                        throw "SetFilePointer failed";
                    }
                }
                else
                {
                    throw "Row not found";
                }
            }
            catch (const char* error)
            {
                delete[] buf;
                delete[] bufAfterDel;
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
            NULL, NULL,
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