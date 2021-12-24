#include <Windows.h>
#include <iostream>

#define FILE_PATH L"D:/3ks1/OS/Completed Labs/Lab9/OS09_01.txt"

BOOL printFileInfo(LPWSTR FileName);
BOOL printFileTxt(LPWSTR FileName);
HANDLE openFile(LPWSTR FileName);
std::string writeTypeFile(HANDLE file);
std::string getFileName(wchar_t* filePath);
LARGE_INTEGER getSizeFile(HANDLE file);

int main()
{
    system("@chcp 1251 > nul");
    printFileInfo((LPWSTR)FILE_PATH);
    printFileTxt((LPWSTR)FILE_PATH);
    system("pause");
    return 0;
}

BOOL printFileInfo(LPWSTR FileName)
{
    //-имя файла;
    //-тип файла;
    //-размер файла;
    //-дата и время создания файла;
    //-дата и время последнего обновления.

    HANDLE file;
    SYSTEMTIME sysTime;
    BY_HANDLE_FILE_INFORMATION fileinfo;
    ZeroMemory(&sysTime, sizeof(SYSTEMTIME));
    ZeroMemory(&fileinfo, sizeof(BY_HANDLE_FILE_INFORMATION));
    if ((file = openFile(FileName)) == NULL)
    {
        return FALSE;
    }

    GetFileInformationByHandle(file, &fileinfo);

    if (&fileinfo == NULL)
    {
        CloseHandle(file);
        return FALSE;
    }

    std::cout << "FileName: " << getFileName((wchar_t*)FileName) << std::endl;
    std::cout << "Type: " << writeTypeFile(file) << std::endl;
    std::cout << "Size(GetFileSizeEx): " << getSizeFile(file).LowPart << "B" << std::endl;
    std::cout << "Size: " << fileinfo.nFileSizeLow << "B" << std::endl;
    FileTimeToSystemTime(&fileinfo.ftCreationTime, &sysTime);
    std::cout << "Creation Time: " << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear <<
        ' ' << sysTime.wHour + 3 << ":" << sysTime.wMinute << std::endl;
    FileTimeToSystemTime(&fileinfo.ftLastWriteTime, &sysTime);
    std::cout << "Update Time: " << sysTime.wDay << '.' << sysTime.wMonth << '.' << sysTime.wYear <<
        ' ' << sysTime.wHour + 3 << ':' << sysTime.wMinute << std::endl;
    CloseHandle(file);

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

LARGE_INTEGER getSizeFile(HANDLE file) {
    LARGE_INTEGER lpFileSize;
    ZeroMemory(&lpFileSize, sizeof(LARGE_INTEGER));
    GetFileSizeEx(file, &lpFileSize);
    return lpFileSize;
}


std::string getFileName(wchar_t* filePath) 
{
    std::wstring ws(filePath);
    std::string filename(ws.begin(), ws.end());
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }
    return filename;
}

std::string writeTypeFile(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return "FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return "FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return "FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return "FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return "FILE_TYPE_REMOTE";
    default:
        return "ERROR: WRITE FILE TYPE";
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