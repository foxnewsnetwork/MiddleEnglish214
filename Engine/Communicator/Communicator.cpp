#include "StdAfx.h"

namespace Communicator
{
	LPCWSTR AddStringsTogether( LPCWSTR str1, CString * str2 )
	{
		int l2 = str2->GetLength();
		int l1 = 0;
		while(str1[l1])
		{
			l1++;
		}
		int totalLengh = l1 + l2;
		WCHAR * output = new WCHAR[totalLengh];
		int k,j;
		for(k = 0; k < l1 - 1; k++)
		{
			output[k] = str1[k];
		}
		for(j = 0; j < l2; j++) 
		{
			output[k+j] = str2->GetAt(j);
		}
		output[k+j] = 0;
		return output;
	}

	LPCWSTR AddStringsTogether( LPCWSTR str1, LPCWSTR str2 )
	{
		int l2 = 0;
		int l1 = 0;
		while(str1[l1])
			l1++;
		while(str2[l2])
			l2++;
		int totalLengh = l1 + l2;
		WCHAR * output = new WCHAR[totalLengh];
		int k,j;
		for(k = 0; k < l1 - 1; k++)
		{
			output[k] = str1[k];
		}
		for(j = 0; j < l2; j++) 
		{
			output[k+j] = str2[j];
		}
		output[k+j] = 0;
		return output;
	}

	CommunicatorBase::CommunicatorBase(void)
		: mpsz_password(NULL)
		, mpsz_serverUrl(NULL)
		, mpsz_username(NULL)
		, mdw_errorCode(0)
	{
	}

	CommunicatorBase::~CommunicatorBase(void)
	{
		// We clear out everything that isn't null
		if(this->mpsz_password)
			delete[] this->mpsz_password;
		if(this->mpsz_serverUrl)
			delete[] this->mpsz_serverUrl;
		if(this->mpsz_username)
			delete[] this->mpsz_username;
	}

	BOOL CommunicatorBase::Authenticate( CString username, CString password )
	{
		// Call this function to before doing anything else
		HINTERNET hInternet = InternetOpen(L"Indigio-Desktop-App", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if(!hInternet)
			return -1; // No internet
		HINTERNET hConnect = InternetConnect(hInternet, this->mpsz_serverUrl, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		if(!hConnect)
			return -2; // Can't access server for whatever reason
		WCHAR tag1[] = L"user/signin?username="; WCHAR tag2[] = L"&password=";
		// The following code would be a lot more elegant if I overloaded the + operator
		// but that will be left as an exercise for the student
		LPCWSTR objecturl = AddStringsTogether( AddStringsTogether( tag1, &username ), AddStringsTogether( tag2, &password ) );
		LPCWSTR httpVersion = NULL; // evenually I hsould
		LPCWSTR httpReferer = NULL;
		LPCWSTR acceptType[2]; acceptType[0] = L"*/*"; acceptType[1] = 0; // all types
		HINTERNET hRequest = HttpOpenRequest( hConnect, L"GET", objecturl, httpVersion, httpReferer, acceptType, NULL, NULL);   
		
		BOOL result1 = HttpSendRequest( hRequest, NULL, NULL, NULL, NULL);
		DWORD dwContentLength;
		DWORD dwBufLen = sizeof( dwContentLength );
		BOOL result2 = HttpQueryInfo( hRequest, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (void*)&dwContentLength, &dwBufLen, 0);
		char * lpBuffer = new char[dwContentLength];
		DWORD dwNumberofBytesRead;
		BOOL result3 = InternetReadFile( hRequest, (void*)lpBuffer, dwContentLength, &dwNumberofBytesRead);

		// Now we do a scan throughout the entire given file to see if we encounter the words success
		const char keyword[] = "success"; bool success_found = false; 
		for(int k = 0; k < dwNumberofBytesRead - strlen(keyword); k++)
		{
			for(int j = 0; j < strlen(keyword); j++)
				if(lpBuffer[k+j] != keyword[j])
					break;
				else
					if( j == strlen(keyword)-1 )
						success_found = true;
			if(success_found == true)
				break;
		}
		// clean up the buffer, we need it no longer
		delete[] lpBuffer;

		// Clean up the internet handles
		InternetCloseHandle(hInternet);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hRequest);

		// Dealing with the success or failure
		if(success_found == true)
		{
			this->mpsz_username = AddStringsTogether(L"", username);
			this->mpsz_password = AddStringsTogether(L"", password);
			return 1; // successful authentiation
		}
		else
			return 0; // failed authentication
	}

	CommunicatorBase CommunicatorBase::Initialize( CString server )
	{
		CommunicatorBase * com_out = new CommunicatorBase;
		com_out->mpsz_serverUrl = AddStringsTogether(L"", server);

		//TODO: more initialization code would go here as necessary
	}

	// Sends a get request to the server where the params part is a string like:
	// Params should be a string like "user_id=4&is_admin=1"
	// Target should be a string like "ad/interact"
	// Type should be a string like "text" or "jpg" or whatever
	InternetPackage CommunicatorBase::GetServer( CString target, CString params, DWORD type )
	{
		// Step 0: Test the internet and establish connection
		InternetPackage * out_pack = new InternetPackage;
		// Call this function to before doing anything else
		HINTERNET hInternet = InternetOpen(L"Indigio-Desktop-App", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if(!hInternet)
		{
			out_pack->ErrorCode = -1; // no internet
			return *out_pack;
		}
			
		HINTERNET hConnect = InternetConnect(hInternet, this->mpsz_serverUrl, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
		if(!hConnect)
		{
			InternetCloseHandle( hInternet );
			out_pack->ErrorCode = -2; // can't access server
			return *out_pack;
		}

		// Step 0.5: Make the flags and stuff
		LPCWSTR lpsz_objectName = AddStringsTogether(AddStringsTogether(target,L"?"), AddStringsTogether(L"", params));
		LPCWSTR lpsz_versionNumber = NULL;
		LPCWSTR lpsz_referrer = NULL;
		LPCWSTR lplpsz_acceptType[2]; lplpsz_acceptType[0] = L"*/*"; lplpsz_acceptType[1] = 0;
		DWORD dw_flags = NULL;
		DWORD dw_context = NULL;

		// Step 1: Send the GET request
		HINTERNET hRequest = HttpOpenRequest(hConnect, L"GET", lpsz_objectName, lpsz_versionNumber, lpsz_referrer, lplpsz_acceptType, dw_flags, dw_context);
		delete [] lpsz_objectName;
		if(!hRequest)
		{
			InternetCloseHandle( hInternet );
			InternetCloseHandle( hConnect );
			out_pack->ErrorCode = -3; // server busy
			// TODO: set a timer so we know when shit times out
			return *out_pack;
		}

		// Step 1.5: send the request and check results
		LPCWSTR lpsz_headers = NULL;
		LPCWSTR lpPostinfo = NULL;
		DWORD dw_headerlengh = 0;
		DWORD dwpostlengh = 0;
		BOOL bResult = HttpSendRequest(hRequest, lpsz_headers, dw_headerlengh, (void*)lpPostinfo, dwpostlengh );
		if( !bResult )
		{
			InternetCloseHandle( hInternet );
			InternetCloseHandle( hConnect );
			InternetCloseHandle( hRequest );
			out_pack->ErrorCode = -4; // request didn't go through for some reason
			// TODO: set a timer so we know when shit times out
			return *out_pack;
		}

		// Step 2: Query the file length
		DWORD dwInfoLevel = HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER;
		DWORD dwBuffer;
		DWORD dwBufferLength = sizeof(dwBuffer);
		DWORD * lpdwIndex = 0;
		bResult = HttpQueryInfo( hRequest, dwInfoLevel, (void*)&dwBuffer, &dwBufferLength, lpdwIndex );
		if( !bResult )
		{
			InternetCloseHandle( hInternet );
			InternetCloseHandle( hConnect );
			InternetCloseHandle( hRequest );
			out_pack->ErrorCode = -5; // request didn't go through for some reason; couldn't query server
			// TODO: set a timer so we know when shit times out
			return *out_pack;
		}

		// Step 3: Read the output from the internet
		char * lpszBuffer = new char[dwBuffer];
		DWORD dwNoBR;
		bResult = InternetReadFile( hRequest, (void*)lpszBuffer, dwBuffer, &dwNoBR );
		if( !bResult )
		{
			InternetCloseHandle( hInternet );
			InternetCloseHandle( hConnect );
			InternetCloseHandle( hRequest );
			out_pack->ErrorCode = -6; // unable to read the given file
			// TODO: set a timer so we know when shit times out
			delete [] lpszBuffer;
			return *out_pack;
		}

		// Step 4: package it together
		out_pack->ContentLength = dwNoBR;
		out_pack->Data = lpszBuffer;
		out_pack->DataType = type; // assuming 1 is char text
		out_pack->ErrorCode = 0; // no error

		// Step 5: clean up after myself and ship it out
		InternetCloseHandle( hInternet );
		InternetCloseHandle( hConnect );
		InternetCloseHandle( hRequest );
		return *out_pack;
	}

	DWORD CommunicatorBase::GetErrorCode(void)
	{
		return this->mdw_errorCode;
	}
}

