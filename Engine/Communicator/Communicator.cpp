#include "StdAfx.h"

namespace Communicator
{
	BOOL CommunicatorBase::Initialize( CString url )
	{
		DWORD result = InternetAttemptConnect(0);
		if( result != ERROR_SUCCESS)
			return -1; // If we're here, then we must not have internet access
		this->url = url;
		return TRUE;
	}

	BOOL CommunicatorBase::Authenticate( CString username, CString password )
	{
		// TODO: implement me!
	}

	BOOL CommunicatorBase::SendToServer( CString header, CString content )
	{
		// Step 01: First we check if our sessions and stuff are blank
		if(!this->hSession)
		{
			this->hSession = InternetOpen( L"IndigioDesktopApp", 0, NULL, NULL, 0);
			// TODO: CONTINUE CODING HERE, YOU FAGGOT!
		}
	}

	BOOL CommunicatorBase::GetFromServer( CString header, LPVOID buffer, DWORD size2read, DWORD bytesRead )
	{
	
	}

	CommunicatorBase::~CommunicatorBase(void)
	{
	
	}

	CommunicatorBase::CommunicatorBase(void)
	{
		this->hSession = NULL;
		this->hOPenUrl = NULL;
		this->authentication_id = 0;
		this->user_id = 0;
		this->url = NULL;
		this->username = NULL;
		this->password = NULL;
	}
}

