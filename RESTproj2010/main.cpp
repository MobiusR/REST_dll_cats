//////////////////////////////////////////////////////////
// Author:	Dorian Snyder
// Desc:	Demonstrates REST API and dll functionality
// 
// Uses The Cat API by Aden Forshaw
// http://thecatapi.com/
//////////////////////////////////////////////////////////

#using <mscorlib.dll>
#using <System.dll>
#using <RESTdll.dll>

#include <urlmon.h>
#pragma comment (lib,"Urlmon.lib")
#include <iostream>
#include <string>

using namespace System;
using namespace System::Net;
using namespace RESTdll;

int main(array<System::String ^> ^args)
{
	// make an instance of the RESTRequest class
	RESTdll::RESTRequest mREST;

	// make a std::string to hold the result
	mREST.MakeRESTRequest();
	std::string result = mREST.result;

	// extract the image url from the string
	int first = result.find_first_of("\"");
	int last = result.find_last_of("\"");
	result = result.substr(first + 1, last - first - 1);

	// print the string to the console
	std::cout << "\n" << result << std::endl;

	// Convert to a wchar_t*
    size_t origsize = strlen(result.c_str()) + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t url[newsize];
    mbstowcs_s(&convertedChars, url, origsize, result.c_str(), _TRUNCATE);
	//wcscat_s(url, L" (wchar_t *)");	// append a string to the end

	wchar_t *dest = L"cat.jpg";

	HRESULT hr = URLDownloadToFile(NULL, url, dest, 0, NULL);

	// press enter
	Console::Read();

	return 0;
}
