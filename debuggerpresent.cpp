#include <windows.h>
#include <stdio.h>
#include <winternl.h>

    #ifdef _WIN64
    PPEB  pPEB = (PPEB)__readgsqword(0x60);/* x63 _PEB = gs:[60h]*/
    #elif _Win32
    PPEB pPEB = (PPEB)__readgsqword(0x30); /* x86 _PEB = fs:[30h]*/
    #endif // _WIN64

int main(void){

    if (pPEB->BeingDebugged !=0){
        printf("Can not execute program is being Debugged");
        return EXIT_FAILURE;
    }

    printf("Not being being debugged, running code");
    MessageBoxW(NULL,L"GOODBYE",L"This is over for your PC",MB_ICONEXCLAMATION | MB_OK);

return EXIT_SUCCESS;
}



















