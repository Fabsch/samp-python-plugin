#include <a_samp>
#include <python>

main()
{
	
}

//------------------------------
// callback
//------------------------------

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	return pyOnDialogResponse(playerid, dialogid, response, listitem, inputtext);
}

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	return pyOnEnterExitModShop(playerid, enterexit, interiorid);
}

public OnFilterScriptExit()
{
	return 1;
}
public OnFilterScriptInit()
{
	return 1;
}

public OnGameModeInit()
{
	if (fexist("python.cfg"))
	{
		new s[128];
		new File:f = fopen("python.cfg", io_read);
		while (fread(f, s))
		{
			new len = strlen(s);
			// strip \n or \r\n at the end
			if (s[len-2] == '\r') s[len-2] = '\0';
			else if (s[len-1] == '\n') s[len-1] = '\0';
			LoadPython(s);
		}
	}
	else
	{
		LoadPython("gamemode");
	}
	return 1;
}
public OnGameModeExit()
{
	UnloadPython();
	return 1;
}

public OnObjectMoved(objectid)
{
	return pyOnObjectMoved(objectid);
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return pyOnPlayerClickPlayer(playerid, clickedplayerid, source);
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return pyOnPlayerCommandText(playerid, cmdtext);
}

public OnPlayerConnect(playerid)
{
	//SetSpawnInfo(playerid, 1, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	return pyOnPlayerConnect(playerid);
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return pyOnPlayerDeath(playerid, killerid, reason);
}

public OnPlayerDisconnect(playerid, reason)
{
	return pyOnPlayerDisconnect(playerid, reason);
}

public OnPlayerEnterCheckpoint(playerid)
{
	return pyOnPlayerEnterCheckpoint(playerid);
}
public OnPlayerEnterRaceCheckpoint(playerid)
{
	return pyOnPlayerEnterRCheckpoint(playerid);
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return pyOnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
}
public OnPlayerExitVehicle(playerid, vehicleid)
{
	return pyOnPlayerExitVehicle(playerid, vehicleid);
}
public OnPlayerExitedMenu(playerid)
{
	return pyOnPlayerExitedMenu(playerid);
}
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return pyOnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return pyOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}
public OnPlayerLeaveCheckpoint(playerid)
{
	return pyOnPlayerLeaveCheckpoint(playerid);
}
public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return pyOnPlayerLeaveRCheckpoint(playerid);
}
public OnPlayerObjectMoved(playerid, objectid)
{
	return pyOnPlayerObjectMoved(playerid, objectid);
}
public OnPlayerPickUpPickup(playerid, pickupid)
{
	return pyOnPlayerPickUpPickup(playerid, pickupid);
}
// OnPlayerPrivmsg -- deprecated/removed
public OnPlayerRequestClass(playerid, classid)
{
	return pyOnPlayerRequestClass(playerid, classid);
}
public OnPlayerRequestSpawn(playerid)
{
	return pyOnPlayerRequestSpawn(playerid);
}
public OnPlayerSelectedMenuRow(playerid, row)
{
	return pyOnPlayerSelectedMenuRow(playerid, row);
}
public OnPlayerSpawn(playerid)
{
	return pyOnPlayerSpawn(playerid);
}
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return pyOnPlayerStateChange(playerid, newstate, oldstate);
}
public OnPlayerStreamIn(playerid, forplayerid)
{
	return pyOnPlayerStreamIn(playerid, forplayerid);
}
public OnPlayerStreamOut(playerid, forplayerid)
{
	return pyOnPlayerStreamOut(playerid, forplayerid);
}
// OnPlayerTeamPrivmsg -- removed
public OnPlayerText(playerid, text[])
{
	return pyOnPlayerText(playerid, text);
}
public OnPlayerUpdate(playerid)
{
	return pyOnPlayerUpdate(playerid);
}
public OnRconCommand(cmd[])
{
	return pyOnRconCommand(cmd);
}
public OnRconLoginAttempt(ip[], password[], success)
{
	return pyOnRconLoginAttempt(ip, password, success);
}
public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	return pyOnVehicleDamageStatusUpdate(vehicleid, playerid);
}
public OnVehicleDeath(vehicleid, killerid)
{
	return pyOnVehicleDeath(vehicleid, killerid);
}
public OnVehicleMod(playerid, vehicleid, componentid)
{
	return pyOnVehicleMod(playerid, vehicleid, componentid);
}
public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return pyOnVehiclePaintjob(playerid, vehicleid, paintjobid);
}
public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return pyOnVehicleRespray(playerid, vehicleid, color1, color2);
}
public OnVehicleSpawn(vehicleid)
{
	return pyOnVehicleSpawn(vehicleid);
}
public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return pyOnVehicleStreamIn(vehicleid, forplayerid);
}
public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return pyOnVehicleStreamOut(vehicleid, forplayerid);
}
public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
{
	return pyOnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat);
}
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	return pyOnPlayerTakeDamage(playerid, issuerid, amount, weaponid);
}
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
	return pyOnPlayerGiveDamage(playerid, damagedid, amount, weaponid);
}
public OnPlayerClickMap(playerid, Float:fX, Float: fY, Float:fZ)
{
	return pyOnPlayerClickMap(playerid, fX, fY, fZ);
}


forward _unusedFunc();
public _unusedFunc()
{
	new Float:x, y;
	// we need to use any native function here, or we won't be able to call them from the plugin
	// this function will/should be never called
	AddMenuItem(Menu:0, 0, "");
	AddPlayerClass(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	AddPlayerClassEx(0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	AddStaticPickup(0, 0, 0.0, 0.0, 0.0, 0);
	AddStaticVehicle(0, 0.0, 0.0, 0.0, 0.0, 0, 0);
	AddStaticVehicleEx(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
	AddVehicleComponent(0, 0);
	AllowAdminTeleport(0);
	AllowInteriorWeapons(0);
	AllowPlayerTeleport(0, 0);
	Attach3DTextLabelToPlayer(Text3D:0, 0, 0.0, 0.0, 0.0);
	Attach3DTextLabelToVehicle(Text3D:0, 0, 0.0, 0.0, 0.0);
	AttachObjectToObject(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
	AttachObjectToPlayer(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	AttachObjectToVehicle(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	AttachPlayerObjectToPlayer(0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	AttachTrailerToVehicle(0, 0);
	ApplyAnimation(0, "", "", 0.0, 0, 0, 0, 0, 0, 0);
	Ban(0);
	BanEx(0, "");
	ChangeVehicleColor(0, 0, 0);
	ChangeVehiclePaintjob(0, 0);
	ClearAnimations(0, 0);
	ConnectNPC("", "");
	Create3DTextLabel("", 0, 0.0, 0.0, 0.0, 0.0, 0, 0);
	CreateExplosion(0.0, 0.0, 0.0, 0, 0.0);
	CreateMenu("", 0, 0.0, 0.0, 0.0, 0.0);
	CreateObject(0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreatePickup(0, 0, 0.0, 0.0, 0.0);
	CreatePlayer3DTextLabel(0, "", 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
	CreatePlayerObject(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreateVehicle(0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0);
	Delete3DTextLabel(Text3D:0);
	DeletePlayer3DTextLabel(0, PlayerText3D:0);
	DestroyMenu(Menu:0);
	DestroyObject(0);
	DestroyPickup(0);
	DestroyPlayerObject(0, 0);
	DestroyVehicle(0);
	DetachTrailerFromVehicle(0);
	DisableInteriorEnterExits();
	DisableMenu(Menu:0);
	DisableMenuRow(Menu:0, 0);
	DisableNameTagLOS();
	DisablePlayerCheckpoint(0);
	DisablePlayerRaceCheckpoint(0);
	EnableStuntBonusForAll(0);
	EnableStuntBonusForPlayer(0, 0);
	ForceClassSelection(0);
	GameModeExit();
	GameTextForAll("", 0, 0);
	GameTextForPlayer(0, "", 0, 0);
	GangZoneCreate(0.0, 0.0, 0.0, 0.0);
	GangZoneDestroy(0);
	GangZoneFlashForAll(0, 0);
	GangZoneFlashForPlayer(0, 0, 0);
	GangZoneHideForAll(0);
	GangZoneHideForPlayer(0, 0);
	GangZoneShowForAll(0, 0);
	GangZoneShowForPlayer(0, 0, 0);
	GangZoneStopFlashForAll(0);
	GangZoneStopFlashForPlayer(0, 0);
	GetAnimationName(0, "", 0, "", 0);
	GetMaxPlayers();
	GetNetworkStats("", 0);
	GetObjectPos(0, x, x, x);
	GetObjectRot(0, x, x, x);
	GetPlayerAmmo(0);
	GetPlayerAnimationIndex(0);
	GetPlayerArmour(0, x);
	GetPlayerCameraFrontVector(0, x, x, x);
	GetPlayerCameraMode(0);
	GetPlayerCameraPos(0, x, x, x);
	GetPlayerColor(0);
	GetPlayerDistanceFromPoint(0, 0.0, 0.0, 0.0);
	GetPlayerDrunkLevel(0);
	GetPlayerFacingAngle(0, x);
	GetPlayerFightingStyle(0);
	GetPlayerHealth(0, x);
	GetPlayerInterior(0);
	GetPlayerIp(0, "", 0);
	GetPlayerKeys(0, y, y, y);
	GetPlayerMenu(0);
	GetPlayerMoney(0);
	GetPlayerName(0, "", 0);
	GetPlayerNetworkStats(0, "", 0);
	GetPlayerObjectPos(0, 0, x, x, x);
	GetPlayerObjectRot(0, 0, x, x, x);
	GetPlayerPing(0);
	GetPlayerPos(0, x, x, x);
	GetPlayerScore(0);
	GetPlayerSkin(0);
	GetPlayerSpecialAction(0);
	GetPlayerState(0);
	GetPlayerSurfingObjectID(0);
	GetPlayerSurfingVehicleID(0);
	GetPlayerTargetPlayer(0);
	GetPlayerTeam(0);
	GetPlayerTime(0, y, y);
	GetPlayerVehicleID(0);
	GetPlayerVehicleSeat(0);
	GetPlayerVelocity(0, x, x, x);
	GetPlayerVirtualWorld(0);
	GetPlayerWantedLevel(0);
	GetPlayerWeapon(0);
	GetPlayerWeaponData(0, 0, y, y);
	GetPlayerWeaponState(0);
	GetTickCount();
	GetVehicleComponentInSlot(0, 0);
	GetVehicleComponentType(0);
	GetVehicleDamageStatus(0, y, y, y, y);
	GetVehicleDistanceFromPoint(0, 0.0, 0.0, 0.0);
	GetVehicleHealth(0, x);
	GetVehicleModel(0);
	GetVehiclePos(0, x, x, x);
	GetVehicleRotationQuat(0, x, x, x, x);
	GetVehicleTrailer(0);
	GetVehicleVelocity(0, x, x, x);
	GetVehicleVirtualWorld(0);
	GetVehicleZAngle(0, x);
	GetWeaponName(0, "", 0);
	GivePlayerMoney(0, 0);
	GivePlayerWeapon(0, 0, 0);
	HideMenuForPlayer(Menu:0, 0);
	IsObjectMoving(0);
	IsPlayerAdmin(0);
	IsPlayerAttachedObjectSlotUsed(0, 0);
	IsPlayerConnected(0);
	// IsPlayerHoldingObject(0); // removed in 0.3c
	IsPlayerInAnyVehicle(0);
	IsPlayerInCheckpoint(0);
	IsPlayerInRaceCheckpoint(0);
	IsPlayerInRangeOfPoint(0, x, x, x, x);
	IsPlayerInVehicle(0, 0);
	IsPlayerNPC(0);
	IsPlayerObjectMoving(0, 0);
	IsPlayerStreamedIn(0, 0);
	IsTrailerAttachedToVehicle(0);
	IsValidMenu(Menu:0);
	IsValidObject(0);
	IsValidPlayerObject(0, 0);
	IsVehicleStreamedIn(0, 0);
	Kick(0);
	KillTimer(0);
	LimitGlobalChatRadius(0.0);
	LimitPlayerMarkerRadius(0.0);
	LinkVehicleToInterior(0, 0);
	ManualVehicleEngineAndLights();
	MoveObject(0, 0.0, 0.0, 0.0, 0.0);
	MovePlayerObject(0, 0, 0.0, 0.0, 0.0, 0.0);
	PlayAudioStreamForPlayer(0, "");
	PlayCrimeReportForPlayer(0, 0, 0);
	PlayerPlaySound(0, 0, 0.0, 0.0, 0.0);
	PlayerSpectatePlayer(0, 0, 0);
	PlayerSpectateVehicle(0, 0, 0);
	PutPlayerInVehicle(0, 0, 0);
	RemoveBuildingForPlayer(0, 0, 0.0, 0.0, 0.0, 0.0);
	RemovePlayerAttachedObject(0, 0);
	RemovePlayerFromVehicle(0);
	RemovePlayerMapIcon(0, 0);
	RemoveVehicleComponent(0, 0);
	RepairVehicle(0);
	ResetPlayerMoney(0);
	ResetPlayerWeapons(0);
	SendClientMessage(0, 0, "");
	SendClientMessageToAll(0, "");
	SendDeathMessage(0, 0, 0);
	SendPlayerMessageToAll(0, "");
	SendPlayerMessageToPlayer(0, 0, "");
	SendRconCommand("");
	SetCameraBehindPlayer(0);
	SetGameModeText("");
	SetGravity(0.0);
	SetMenuColumnHeader(Menu:0, 0, "");
	SetNameTagDrawDistance(0.0);
	SetObjectPos(0, 0.0, 0.0, 0.0);
	SetObjectRot(0, 0.0, 0.0, 0.0);
	SetPlayerAmmo(0, 0, 0);
	SetPlayerArmedWeapon(0, 0);
	SetPlayerArmour(0, 0.0);
	SetPlayerAttachedObject(0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	SetPlayerCameraLookAt(0, 0.0, 0.0, 0.0);
	SetPlayerCameraPos(0, 0.0, 0.0, 0.0);
	SetPlayerChatBubble(0, "", 0, 0.0, 0);
	SetPlayerCheckpoint(0, 0.0, 0.0, 0.0, 0.0);
	SetPlayerColor(0, 0);
	SetPlayerDrunkLevel(0, 0);
	SetPlayerFacingAngle(0, 0.0);
	SetPlayerFightingStyle(0, 0);
	SetPlayerHealth(0, 0.0);
	// SetPlayerHoldingObject(0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // removed in 0.3c
	SetPlayerInterior(0, 0);
	SetPlayerMapIcon(0, 0, 0.0, 0.0, 0.0, 0, 0);
	SetPlayerMarkerForPlayer(0, 0, 0);
	SetPlayerName(0, "");
	SetPlayerObjectPos(0, 0, 0.0, 0.0, 0.0);
	SetPlayerObjectRot(0, 0, 0.0, 0.0, 0.0);
	SetPlayerPos(0, 0.0, 0.0, 0.0);
	SetPlayerPosFindZ(0, 0.0, 0.0, 0.0);
	SetPlayerRaceCheckpoint(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	SetPlayerScore(0, 0);
	SetPlayerShopName(0, "");
	SetPlayerSkillLevel(0, 0, 0);
	SetPlayerSkin(0, 0);
	SetPlayerSpecialAction(0, 0);
	SetPlayerTeam(0, 0);
	SetPlayerTime(0, 0, 0);
	SetPlayerVelocity(0, 0.0, 0.0, 0.0);
	SetPlayerVirtualWorld(0, 0);
	SetPlayerWantedLevel(0, 0);
	SetPlayerWeather(0, 0);
	SetPlayerWorldBounds(0, 0.0, 0.0, 0.0, 0.0);
	SetSpawnInfo(0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SetTeamCount(0);
	SetTimerEx("", 0, false, "", 0);
	SetVehicleAngularVelocity(0, 0.0, 0.0, 0.0);
	SetVehicleHealth(0, 0.0);
	SetVehicleNumberPlate(0, "");
	SetVehicleParamsEx(0, 0, 0, 0, 0, 0, 0, 0);
	SetVehicleParamsForPlayer(0, 0, 0, 0);
	SetVehiclePos(0, 0.0, 0.0, 0.0);
	SetVehicleToRespawn(0);
	SetVehicleVelocity(0, 0.0, 0.0, 0.0);
	SetVehicleVirtualWorld(0, 0);
	SetVehicleZAngle(0, 0.0);
	SetWeather(0);
	SetWorldTime(0);
	ShowMenuForPlayer(Menu:0, 0);
	ShowNameTags(0);
	ShowPlayerDialog(0, 0, 0, "", "", "", "");
	ShowPlayerMarkers(0);
	ShowPlayerNameTagForPlayer(0, 0, 0);
	SpawnPlayer(0);
	StartRecordingPlayerData(0, 0, "");
	StopAudioStreamForPlayer(0);
	StopObject(0);
	// StopPlayerHoldingObject(0); // removed in 0.3c
	StopPlayerObject(0, 0);
	StopRecordingPlayerData(0);
	TextDrawAlignment(Text:0, 0);
	TextDrawBackgroundColor(Text:0, 0);
	TextDrawBoxColor(Text:0, 0);
	TextDrawColor(Text:0, 0);
	TextDrawCreate(0.0, 0.0, "");
	TextDrawDestroy(Text:0);
	TextDrawFont(Text:0, 0);
	TextDrawHideForAll(Text:0);
	TextDrawHideForPlayer(0, Text:0);
	TextDrawLetterSize(Text:0, 0.0, 0.0);
	TextDrawSetOutline(Text:0, 0);
	TextDrawSetProportional(Text:0, 0);
	TextDrawSetShadow(Text:0, 0);
	TextDrawSetString(Text:0, "");
	TextDrawShowForAll(Text:0);
	TextDrawShowForPlayer(0, Text:0);
	TextDrawTextSize(Text:0, 0.0, 0.0);
	TextDrawUseBox(Text:0, 0);
	TogglePlayerClock(0, 0);
	TogglePlayerControllable(0, 0);
	TogglePlayerSpectating(0, 0);
	Update3DTextLabelText(Text3D:0, 0, "");
	UpdatePlayer3DTextLabelText(0, PlayerText3D:0, 0, "");
	UpdateVehicleDamageStatus(0, 0, 0, 0, 0);
	UsePlayerPedAnims();
}