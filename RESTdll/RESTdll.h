//////////////////////////////////////////////////////////
// Author:	Dorian Snyder
// Desc:	Demonstrates REST API and dll functionality
// 
// Uses The Cat API by Aden Forshaw
// http://thecatapi.com/
//////////////////////////////////////////////////////////

#pragma once

#using <mscorlib.dll>
#using <System.dll>

#include <string>

using namespace System;
using namespace System::Net;

namespace RESTdll
{
	public ref class RESTRequest
	{
	public:

		RESTRequest()
		{

		}

		char* result;
		int resultSize;

		void MakeRESTRequest(int numcats)
		{
			System::Net::HttpWebRequest^ myRequest = dynamic_cast<HttpWebRequest^>(WebRequest::Create( "http://thecatapi.com/api/images/get.php?format=html&type=jpg" ));
			System::Net::WebResponse^ myResponse = myRequest->GetResponse();

			// Obtain a 'Stream' object associated with the response object.
			System::IO::Stream^ ReceiveStream = myResponse->GetResponseStream();

			System::Text::Encoding^ encode = System::Text::Encoding::GetEncoding( "utf-8" );

			// Pipe the stream to a higher level stream reader with the required encoding format.
			System::IO::StreamReader^ readStream = gcnew System::IO::StreamReader( ReceiveStream,encode );
			//Console::WriteLine( "\nResponse stream received" );
			array<Char>^ read = gcnew array<Char>(256);

			// Read 256 charcters at a time.
			int count = readStream->Read( read, 0, 256 );
			//Console::WriteLine( "HTML...\r\n" );

			std::string theString;
			while (count > 0)
			{
				// Dump the 256 characters on a string.
				String^ str = gcnew String( read,0,count );

				// convert the System::String to std::string
				array<Char>^ chr = gcnew array<Char>(256);
				chr = str->ToCharArray();
				for (int i = 0; i < count; i++)
				{
					theString += chr[i];
				}

				count = readStream->Read( read, 0, 256 );
			}

			// since we can't have a std::string member, conver to char*
			resultSize = theString.length();
			result = new char[resultSize];
			for (int i = 0; i < resultSize; i++)
			{
				result[i] = theString[i];
			}

			// Release the resources of stream object.
			readStream->Close();

			// Release the resources of response object.
			myResponse->Close();
		}
	};
}