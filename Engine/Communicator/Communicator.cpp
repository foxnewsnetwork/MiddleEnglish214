#include "StdAfx.h"

namespace Communicator
{
	BOOL CommunicatorBase::Initialize( CString url )
	{
		this->url = url;
	}

	BOOL CommunicatorBase::Authenticate( CString username, CString password )
	{
		
	}

	BOOL CommunicatorBase::SendToServer( CString header, CString content )
	{
		
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

