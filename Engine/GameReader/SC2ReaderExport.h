#pragma once


namespace GameReaderStarcraft2
{
	class StarcraftGameState
	{
	public:
		bool GameStart;
		int GameTimer;
	};

	class StarcraftPlayerState
	{
	public:
		__int8 status; //0x0000
		__int32 cameraX; //0x0008  
		__int32 cameraY; //0x000C  
		__int32 cameraDistance; //0x0010  
		__int32 cameraAngleOfAttack; //0x0014  
		__int32 cameraRotation; //0x0018  
		__int8 team; //0x001C  
		__int8 playerType; //0x001D  
		__int8 playingStatus; //0x001E
		__int8 difficulty; //0x0027
		__int32 attackMultiplier; //0x00F8  
		__int32 damageMultiplier; //0x00FC
		__int32 apmCurrent; //0x0270
		__int32 unitsKilled; //0x02A0  
		__int32 unitsLost; //0x02A8  
		__int32 unitsBetrayed; //0x02B0
		__int32 harvesters_current; //0x03B8
		__int32 harvesters_built; //0x03C8
		__int32 building_queue_length; //0x03E8  
		__int32 buildings_constructing; //0x03F0  
		__int32 buildings_current; //0x03F8  
		__int32 total_constructing_queue_length; //0x0400  
		__int32 total_constructing; //0x0408  
		__int32 army_size; //0x0410  
		
		__int32 supplyCap; //0x0468  
		
		__int32 supplyCurrent; //0x0470  
		
		__int32 mineralsCurrent; //0x0498  
		
		__int32 vespeneCurrent; //0x04A0  
		
		__int32 terrazineCurrent; //0x04A8  
		
		__int32 customCurrent; //0x04B0  
		
		__int32 mineralsTotal; //0x04B8  
		
		__int32 vespeneTotal; //0x04C0  
		
		__int32 terrazineTotal; //0x04C8  
		
		__int32 customTotal; //0x04D0  
		
		__int32 mineralsRate; //0x0518  
		
		__int32 vespeneRate; //0x0520  
		
		__int32 terrazineRate; //0x0528  
		
		__int32 customRate; //0x0530  
		
		__int32 slowMineralsCurrent; //0x0538  
		
		__int32 slowVespeneCurrent; //0x0540  
		
		__int32 slowTerrazineCurrent; //0x0548  
		
		__int32 slowCustomCurrent; //0x0550  
		
		__int32 units_lost_minerals_worth; //0x0580  
		
		__int32 buildings_lost_minerals_worth; //0x0588  
		
		__int32 buildings_lost_vespene_worth; //0x0590  
		
		__int32 units_lost_vespene_worth; //0x05A0  
		
	};

	class StarcraftUnitState
	{
	public:
		WORD times_used; //0x0000  
		WORD id; //0x0002  
		WORD previous_id; //0x0004  
		WORD next_id; //0x0006  
		__int32 model; //0x0008  
		
	
		__int8 playerOwner; //0x0027  
	
		__int8 isAlive; //0x0029  
	
		__int8 isPaused; //0x002E  
	
		__int16 kills; //0x0032  
		__int8 playerOwner2; //0x0034  
		__int8 playerOwner3; //0x0035  
	
		__int32 positionX; //0x0040  
		__int32 positionY; //0x0044  
		__int32 positionZ; //0x0048  
	
		__int32 rotationX; //0x0054  
		__int32 rotationY; //0x0058  
		__int32 rotation; //0x005C  
	
		__int32 destinationX; //0x0074  
		__int32 destinationY; //0x0078  
		__int32 destinationZ; //0x007C  
	
		__int32 lastOrder; //0x0084  
		__int32 destinationX2; //0x0088  
		__int32 destinationY2; //0x008C  
		__int32 startPositionX; //0x0090  
		__int32 startPositionY; //0x0094  
		__int32 destinationX3; //0x0098  
		__int32 destinationY3; //0x009C  
		__int32 startPosition2X; //0x00A0  
		__int32 startPosition2Y; //0x00A4  
	
		__int32 moveSpeed; //0x00B8  
	
		__int32 commandQueue; //0x00C4  
	
	
	
		__int32 healthDamage; //0x0104  
		__int32 shieldDamage; //0x0108  
		__int32 energyDamage; //0x010C  
		__int32 healthMax; //0x0110  
		__int32 shieldMax; //0x0114  
		__int32 energyMax; //0x0118  
		__int32 healthMultiplier; //0x011C  
		__int32 shieldMultiplier; //0x0120  
		__int32 energyMultiplier; //0x0124  
	
		__int32 lifespan; //0x0151  
		__int32 lastAttacked; //0x0155  
	
		__int32 bountyMinerals; //0x0168  
		__int32 bountyVespene; //0x016C  
		__int32 bountyTerrazine; //0x0170  
		__int32 bountyCustom; //0x0174  
		__int32 bountyXP; //0x0178  
		__int8 cellX_Approx; //0x017C  
		__int8 cellY_Approx; //0x017D  
	};

	class StarcraftAPI
	{
	public:
		static StarcraftAPI& Initialize( );
		BOOL GetGameState(__out StarcraftGameState * gamestate);
		BOOL GetPlayerState(__out StarcraftPlayerState * playerstate);
		int GetUnitState(__out StarcraftUnitState * unitstate); 
		~StarcraftAPI(void);

	protected:
		DWORD playerOffset;
		DWORD unitOffset;
		HANDLE processHandle;
		int unitCount;
		Player * myplayer;
		Unit * myunit;
		DWORD unitStart;

	protected:
		StarcraftAPI(void);
		// Finds the process Id of Starcraft 2 on a given windows machine
		static BOOL FindMyProcess(__in WCHAR processName[MAX_PATH] , __out DWORD & processId);
		// Sets the offset values for a given instance of the reader
		void EstablishOffsets(void);
		// finds the amount of unitary offset from the unitOffset of the first unit belonging to player 1
		int FindFirstPlayerUnit(int initial_guess, int count = 0);
		// fills the player variable
		void UpdatePlayer(void);
		// Fills the unit tables;
		void UpdateUnit(void);
	
	};

}