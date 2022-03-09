#ifndef HuffmanLibrary
#define HuffmanLibrary

#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers

// Includes
#include <windows.h>
#include "huffman.h"

using namespace StoneLayer;



// Entry point for the DLL
bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	// Reason the entry point is being called
	switch(ul_reason_for_call)
	{
		// The DLL is being loaded
		case DLL_PROCESS_ATTACH:
			// Initialize the huffman algorithm
			HUFFMAN_Construct();
			break;

		// The DLL is being unloaded
		case DLL_PROCESS_DETACH:
			// Free the table when the DLL is unloaded
			HUFFMAN_Destruct();
			break;
	}

	return true;
}

// Takes a binary string encrypted using huffman and decrypts it for other languages
extern "C" __declspec(dllexport) void __stdcall HuffmanEncode(char* huffdata, int datalength, char* dataresult, int* resultlength)
{
	// Decrypt the data, giving us the result and its length
	HUFFMAN_Encode((unsigned char*)huffdata, (unsigned char*)dataresult, datalength, resultlength);
}

// Takes a binary string and encrypts it using huffman for other languages
extern "C" __declspec(dllexport) void __stdcall HuffmanDecode(char* huffdata, int datalength, char* dataresult, int* resultlength)
{
	// Encrypt the data, giving us the result and its length
	HUFFMAN_Decode((unsigned char*)huffdata, (unsigned char*)dataresult, datalength, resultlength);
}

#endif