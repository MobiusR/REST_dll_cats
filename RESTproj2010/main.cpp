//////////////////////////////////////////////////////////
// Author:	Dorian Snyder
// Desc:	Demonstrates REST API and dll functionality
// Desc:	Also: the magic of converting string types
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
	// the number of cats you want
	int numcats = 1;
	std::cout << "Input the number of cats (1-100): ";
	std::cin >> numcats;
	if (numcats < 1)
		numcats = 1;
	if (numcats > 100)
		numcats = 100;

	// make an instance of the RESTRequest class
	RESTdll::RESTRequest mREST;

	// make a std::string to hold the result
	mREST.MakeRESTRequest(numcats);
	char* result = mREST.result;
	std::string* results = new std::string[numcats];

	results[0] = strtok(result, "\n");
	int index = 1;
	while (index < numcats)
	{
		results[index++] = strtok(NULL, "\n");
	}

	// extract the image url from the string
	for (int i = 0; i < numcats; i++)
	{
		int first = results[i].find_first_of("\"");
		int last = results[i].find_last_of("\"");
		results[i] = results[i].substr(first + 1, last - first - 1);
	}

	// print the string to the console
	//for (int i = 0; i < numcats; i++)
	//{
	//	std::cout << results[i] << std::endl;
	//}

	// Convert url to a wchar_t*
	wchar_t** urls = new wchar_t*[numcats];
	for (int i = 0; i < numcats; i++)
	{
		urls[i] = new wchar_t[100];
	}

	for (int i = 0; i < numcats; i++)
	{
		size_t origsize = strlen(results[i].c_str()) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t url[newsize];
		mbstowcs_s(&convertedChars, url, origsize, results[i].c_str(), _TRUNCATE);

		for (int j = 0; j < 100; j++)
		{
			urls[i][j] = url[j];
		}
		//wcscat_s(url, L" (wchar_t *)");	// append a string to the end
	}

	// download the file to the program directory
	for (int i = 0; i < numcats; i++)
	{
		std::string temp = "cat";
		temp.append(_itoa(i+1, new char, 10));
		int extension = results[i].find_last_of(".");
		switch (results[i][extension+1])
		{
		case 'g':
			temp += ".gif";
			break;
		case 'j':
			temp += ".jpg";
			break;
		case 'p':
			temp += ".png";
			break;
		default:
			temp += ".WTF";
			break;
		}

		// convert to a wchar_t... again
		size_t origsize = strlen(temp.c_str()) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t dest[newsize];
		mbstowcs_s(&convertedChars, dest, origsize, temp.c_str(), _TRUNCATE);

		std::cout << "\nDownloading " << i+1 << " of " << numcats << ": " << std::endl;
		std::wcout << urls[i] << std::endl;
		HRESULT hr_url = URLDownloadToFile(NULL, urls[i], dest, 0, NULL);

		// if the download started successfully, set the desktop
		if (hr_url == S_OK)
			SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, dest, SPIF_SENDCHANGE);
	}

	// done
	std::cout << std::endl << "Done" << std::endl;

	// press enter
	Console::Read();

	return 0;
}
