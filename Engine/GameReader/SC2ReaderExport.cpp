

namespace GameReaderStarcraft2
{
	StarcraftAPI::StarcraftAPI(void)
		: playerOffset(0)
		, unitOffset(0)
		, processHandle(0)
		, unitCount(0)
		, myplayer(0)
		, myunit(0)
		, unitStart(0)
	{
	}

	StarcraftAPI::~StarcraftAPI(void)
	{
		if(this->myunit)
			delete this->myunit;
		if(this->myplayer)
			delete this->myplayer;
		CloseHandle(this->processHandle);
	}

	StarcraftAPI& StarcraftAPI::Initialize(void)
	{
		StarcraftAPI * myapi = 0;

		// Step 0: Find the SC2 Process handle
		DWORD processId;
		BOOL result = StarcraftAPI::FindMyProcess( L"SC2.exe", processId );

		// If we can't find it, then the user obviously doesn't have sc2 running so we just return the error
		if(result != TRUE)
			return *myapi;
		else
			myapi = new StarcraftAPI;

		// Step 1: Get the handle to the sc2process
		myapi->processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

		// We should check again if we've failed to open the correct process
		if(myapi->processHandle == NULL)
			return *myapi;

		// Step 2: Set the offsets (eventually this ought to be done intelligently)
		myapi->EstablishOffsets();

		// Step 3: we're done
		return *myapi;
	}

	BOOL StarcraftAPI::GetGameState(__out StarcraftGameState * gamestate)
	{
		// Step 1: initialization
		if(!gamestate)
			gamestate = new StarcraftGameState;
	
		// Step 2: Get the timer and such
		// NOT IMPLEMENTED

		return TRUE;
	}

	BOOL StarcraftAPI::GetPlayerState(__out StarcraftPlayerState * playerstate)
	{
		// Step 1: initializing the variable
		if(!playerstate)
			playerstate = new StarcraftPlayerState;
	
		// Step 2: updating from the game
		this->UpdatePlayer();
		this->UpdateUnit();
	
		// Step 3: making the output variable
		playerstate->status = this->myplayer->status;
		playerstate->cameraX = this->myplayer->cameraX;
		playerstate->cameraY = this->myplayer->cameraY;
		playerstate->cameraDistance = this->myplayer->cameraDistance;
		playerstate->cameraAngleOfAttack = this->myplayer->cameraAngleOfAttack;
		playerstate->cameraRotation = this->myplayer->cameraRotation;
		playerstate->team = this->myplayer->team;
		playerstate->playerType = this->myplayer->playerType;
		playerstate->playingStatus = this->myplayer->playingStatus;
		playerstate->difficulty = this->myplayer->difficulty;
		playerstate->attackMultiplier = this->myplayer->attackMultiplier;
		playerstate->damageMultiplier = this->myplayer->damageMultiplier;
		playerstate->apmCurrent = this->myplayer->apmCurrent;
		playerstate->unitsKilled = this->myplayer->unitsKilled;
		playerstate->unitsLost = this->myplayer->unitsLost;
		playerstate->unitsBetrayed = this->myplayer->unitsBetrayed;
		playerstate->harvesters_current = this->myplayer->harvesters_current;
		playerstate->harvesters_built = this->myplayer->harvesters_built;
		playerstate->building_queue_length = this->myplayer->building_queue_length;
		playerstate->buildings_constructing = this->myplayer->buildings_constructing;
		playerstate->buildings_current = this->myplayer->buildings_current;
		playerstate->total_constructing_queue_length = this->myplayer->total_constructing_queue_length;
		playerstate->total_constructing = this->myplayer->total_constructing;
		playerstate->army_size = this->myplayer->army_size;
		playerstate->supplyCap = this->myplayer->supplyCap;
		playerstate->supplyCurrent = this->myplayer->supplyCurrent;
		playerstate->mineralsCurrent = this->myplayer->mineralsCurrent;
		playerstate->vespeneCurrent = this->myplayer->vespeneCurrent;
		playerstate->terrazineCurrent = this->myplayer->terrazineCurrent;
		playerstate->customCurrent = this->myplayer->customCurrent;
		playerstate->mineralsTotal = this->myplayer->mineralsTotal;
		playerstate->vespeneTotal = this->myplayer->vespeneTotal;
		playerstate->terrazineTotal = this->myplayer->terrazineTotal;
		playerstate->customTotal = this->myplayer->customTotal;
		playerstate->mineralsRate = this->myplayer->mineralsRate;
		playerstate->vespeneRate = this->myplayer->vespeneRate;
		playerstate->terrazineRate = this->myplayer->terrazineRate;
		playerstate->customRate = this->myplayer->customRate;
		playerstate->slowMineralsCurrent = this->myplayer->slowMineralsCurrent;
		playerstate->slowVespeneCurrent = this->myplayer->slowVespeneCurrent;
		playerstate->slowTerrazineCurrent = this->myplayer->slowTerrazineCurrent;
		playerstate->slowCustomCurrent = this->myplayer->slowCustomCurrent;
		playerstate->units_lost_minerals_worth = this->myplayer->units_lost_minerals_worth;
		playerstate->buildings_lost_minerals_worth = this->myplayer->buildings_lost_minerals_worth;
		playerstate->buildings_lost_vespene_worth = this->myplayer->buildings_lost_vespene_worth;
		playerstate->units_lost_vespene_worth = this->myplayer->units_lost_vespene_worth;	

		// Step 4: we're done
		return TRUE;
	}

	int StarcraftAPI::GetUnitState(__out StarcraftUnitState * unitstate)
	{
		// Step 1: initializing the variable
		unitstate = new StarcraftUnitState[this->unitCount];

		// Step 2: updating from the game
		this->UpdatePlayer();
		this->UpdateUnit();

		// Step 3: Now we've got to do it (with regex in php)
		for(int k = 0; k < this->unitCount; k++)
		{
			unitstate[k].model = this->myunit[k].model;
			unitstate[k].playerOwner = this->myunit[k].playerOwner;
			unitstate[k].isAlive = this->myunit[k].isAlive;
			unitstate[k].isPaused = this->myunit[k].isPaused;
			unitstate[k].kills = this->myunit[k].kills;
			unitstate[k].positionX = this->myunit[k].positionX;
			unitstate[k].positionY = this->myunit[k].positionY;
			unitstate[k].positionZ = this->myunit[k].positionZ;
			unitstate[k].rotationX = this->myunit[k].rotationX;
			unitstate[k].rotationY = this->myunit[k].rotationY;
			unitstate[k].rotation = this->myunit[k].rotation;
			unitstate[k].destinationX = this->myunit[k].destinationX;
			unitstate[k].destinationY = this->myunit[k].destinationY;
			unitstate[k].destinationZ = this->myunit[k].destinationZ;
			unitstate[k].lastOrder = this->myunit[k].lastOrder;
			unitstate[k].startPositionX = this->myunit[k].startPositionX;
			unitstate[k].startPositionY = this->myunit[k].startPositionY;
			unitstate[k].moveSpeed = this->myunit[k].moveSpeed;
			unitstate[k].commandQueue = this->myunit[k].commandQueue;
			unitstate[k].healthDamage = this->myunit[k].healthDamage;
			unitstate[k].shieldDamage = this->myunit[k].shieldDamage;
			unitstate[k].energyDamage = this->myunit[k].energyDamage;
			unitstate[k].healthMax = this->myunit[k].healthMax;
			unitstate[k].shieldMax = this->myunit[k].shieldMax;
			unitstate[k].energyMax = this->myunit[k].energyMax;
			unitstate[k].healthMultiplier = this->myunit[k].healthMultiplier;
			unitstate[k].shieldMultiplier = this->myunit[k].shieldMultiplier;
			unitstate[k].energyMultiplier = this->myunit[k].energyMultiplier;
			unitstate[k].lifespan = this->myunit[k].lifespan;
			unitstate[k].lastAttacked = this->myunit[k].lastAttacked;
			unitstate[k].bountyMinerals = this->myunit[k].bountyMinerals;
			unitstate[k].bountyVespene = this->myunit[k].bountyVespene;
			unitstate[k].bountyTerrazine = this->myunit[k].bountyTerrazine;
			unitstate[k].bountyCustom = this->myunit[k].bountyCustom;
			unitstate[k].bountyXP = this->myunit[k].bountyXP;
			unitstate[k].cellX_Approx = this->myunit[k].cellX_Approx;
			unitstate[k].cellY_Approx = this->myunit[k].cellY_Approx;
			unitstate[k].times_used = this->myunit[k].times_used;
			unitstate[k].id = this->myunit[k].id;
			unitstate[k].previous_id = this->myunit[k].previous_id;
			unitstate[k].next_id = this->myunit[k].next_id;
		}

		// Step 4: we're done
		return this->unitCount;
	}

	BOOL StarcraftAPI::FindMyProcess(__in WCHAR processName[MAX_PATH] , __out DWORD & processId)
	{
		HANDLE hProcessSnap;
		HANDLE hProcess;
		PROCESSENTRY32 pe32;
		DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if( hProcessSnap == INVALID_HANDLE_VALUE )
		{
			// We've encountered a terrible terrible error and we ought to abandon this endeavor
			return NULL;
		}

		// Set the size of the structure before using it.
		pe32.dwSize = sizeof( PROCESSENTRY32 );

		// Retrieve information about the first process,
		// and exit if unsuccessful
		if( !Process32First( hProcessSnap, &pe32 ) )
		{
			// Cause of error at Process32First
			CloseHandle( hProcessSnap );          // clean the snapshot object
			return( NULL );
		}

		// Setting up the variables
		TCHAR filename[MAX_PATH];

		// Now we walk the snapshot of processes
		// and look for SC2; we return it if found
		// if not, we give up
	
		do
		{
			// std::cout << "Process name: ";
			for( int k = 0; k < MAX_PATH; k++ )
			{
				// std::cout << CHAR(pe32.szExeFile[k]);
				if( CHAR(pe32.szExeFile[k]) != CHAR(processName[k]) )
					break;
				if( pe32.szExeFile[k] == NULL && processName[k] == NULL ) // second part included to look symmetric but not necessary
				{
					processId = pe32.th32ProcessID;
					return TRUE;
				}
			}
			// std::cout << std::endl;
		}
		while (Process32Next( hProcessSnap, &pe32 ) );
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	void StarcraftAPI::EstablishOffsets(void)
	{
		// As I have said, this ought to be done intelligently via stream-based machine learning
		// in the nearby future. For now, however, I will simply declare the values (lol)
		this->playerOffset = 0x026A6EC0; // come to think of it, these should probably be constants
		this->unitOffset = 0x01DE6000; // Do some research and find out this value!

		// Now we need to find the address of the first player unit
		int lolcat;
		lolcat = this->FindFirstPlayerUnit(0,200);
		this->unitStart = this->unitOffset + lolcat * sizeof(Unit);
	}

	int StarcraftAPI::FindFirstPlayerUnit(int initial_position, int end_position)
	{
		// Step 0: declare the tools I will need
		Unit myunits[2]; // Struct for the units
		SIZE_T bytesRead; // The amount of data read
		BOOL result; // The results of each reading
		DWORD start = this->unitOffset + initial_position * sizeof(Unit);
		int wtf = (end_position - initial_position) / 2;
		DWORD mid = this->unitOffset + (wtf + initial_position) * sizeof(Unit);
		DWORD end = this->unitOffset + end_position * sizeof(Unit);

		// Step 1: We check to see if we're within range
		result = ReadProcessMemory(this->processHandle, (void*)start, (void*)&myunits[0], sizeof(Unit), &bytesRead);
		if( !result )
			return -2; // memory read error
		if( myunits[0].playerOwner != 0 )
			return -1; // bad start range

		result = ReadProcessMemory(this->processHandle, (void*)end, (void*)&myunits[1], sizeof(Unit), &bytesRead);
		if( !result )
			return -2; // memory read error
		if( myunits[1].playerOwner != 1 )
			return -1; // bad end range
	
		// Step 1.5: Terminating cases
		if( end_position == initial_position + 1 )
			return end_position;
		if( (end_position - initial_position) == 2 )
		{
			result = ReadProcessMemory(this->processHandle, (void*)mid, (void*)&myunits[0], sizeof(Unit), &bytesRead);
			if( !result )
				return -2; // memory read error
			if( myunits[0].playerOwner == 0 )
				return end_position;
			else
				return end_position - 1;
		}

		// Step 2: We check the middle
		result = ReadProcessMemory(this->processHandle, (void*)mid, (void*)&myunits, sizeof(Unit)*2, &bytesRead);
		if( !result )
			return -2; // memory read error
		if( myunits[0].playerOwner != myunits[1].playerOwner ) // we've found crossover
			return mid+1;

		// Step 3: We setup the recursion
		if( myunits[0].playerOwner == 0 )
			return this->FindFirstPlayerUnit( wtf+initial_position+1, end_position );
		else if( myunits[1].playerOwner == 1 )
			return this->FindFirstPlayerUnit( initial_position, end_position-wtf-1 );
		else
			return -1; // argument out of range
	}

	// fills the player variable
	void StarcraftAPI::UpdatePlayer(void)
	{
		SIZE_T bytesRead;
		ReadProcessMemory(this->processHandle, (void*)this->playerOffset, (void*)this->myplayer, sizeof(Player), &bytesRead);
		this->unitCount = this->myplayer->army_size;
	}

	// Fills the unit tables. YOU MUST CALL UpdatePlayer BEFORE THIS METHOD OR LESE YOU'RE A FAGGOT
	void StarcraftAPI::UpdateUnit(void)
	{
		SIZE_T bytesRead;
		ReadProcessMemory(this->processHandle, (void*)this->unitOffset, (void*)this->myunit, sizeof(Unit), &bytesRead);
	
	}
}