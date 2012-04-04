//////////////////////////////////////////////////////////
// Author:	Dorian Snyder
// Desc:	Demonstrates REST API and dll functionality
// 
// Uses The Cat API by Aden Forshaw
// http://thecatapi.com/
//////////////////////////////////////////////////////////

The dll (RESTdll.dll) uses the REST API - The Cat API - to get a random
url of a cat picture. It then sends this url to the calling program.

The calling program - RESTproj2010.exe - uses the above dll, and when
it receives the url, it uses the urlmon API (urlmon.h) to save the
file to the program directory.

UPDATE 1:
The program now sets the desktop to the downloaded image.

UPDATE 2:
The program now has some minor error checking.

UPDATE 3:
You can now specify how many cats you want to download (1-100).
You can now get all 3 file types (.gif, .jpg, .png).

UPDATE 4:
You can now enter 0 (or less) to quit the program.
