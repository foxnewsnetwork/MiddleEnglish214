#pragma once

namespace Communicator
{
	class CommunicatorBase
	{
	public:
		BOOL Initialize( CString url );
		BOOL Authenticate( CString username, CString password );
		BOOL SendToServer( CString header, CString content );
		BOOL GetFromServer( CString header, LPVOID buffer, DWORD size2read, DWORD bytesRead );
		~CommunicatorBase(void);

	protected:
		HINTERNET hSession;
		HINTERNET hOPenUrl;
		LPCWSTR url;
		LPCWSTR username;
		LPCWSTR password;
		int user_id;
		int authentication_id;
		int error_flag;

	protected:
		CommunicatorBase(void);
		// TODO: write functions to do RSA encryption
	};
}
