#pragma once

namespace Communicator
{
	class AdMetaData
	{
	public:
		DWORD AdType;
		DWORD RelatedGame;
	};

	class InternetPackage
	{
	public:
		BOOL ErrorCode;
		DWORD DataType; // i.e. text, img, etc.
		LPVOID Data;
		DWORD ContentLength;
		inline ~InternetPackage(void)
		{
			delete [] this->Data;
		}
	};

	class CommunicatorBase
	{
	public: // Public interface
		~CommunicatorBase(void);
		static CommunicatorBase Initialize( CString server );
		BOOL Authenticate( CString username, CString password );
		InternetPackage GetServer( CString target, CString params, DWORD type );
		// InternetPackage PostServer( CString params);
		DWORD GetErrorCode(void);

	protected:
		CommunicatorBase(void);
		// TODO: write functions to do RSA encryption
	protected:
		LPCWSTR mpsz_serverUrl;
		LPCWSTR mpsz_username;
		LPCWSTR mpsz_password;
		DWORD mdw_errorCode;
		
	};
}
