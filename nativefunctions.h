//	Python plugin for SAMP
//	Copyright (C) 2010-2012 Fabsch
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __native_functions_h_
#define __native_functions_h_

//-----------------------------------------
// functions for finding native PAWN functions etc.
//-----------------------------------------

amx_function_t _findNative(AMX *amx, char *name, bool nowarn=false);
void _initAMX(AMX *amx);

char *_getString(AMX *amx, cell params);
#define _del(x) if (x) { delete [] (x); (x) = NULL; }
#define _pyNoReturnVal(x) (x == NULL || x == Py_None) 
#define _retPyInt(pyobj, def) \
	if (_pyNoReturnVal(pyobj)) return def;\
	\
	cell res = PyInt_AsLong(pyobj);\
	Py_DECREF(pyobj);\
	return res;

#define _getColor(pyobj) \
	unsigned int colcode; \
	if (PyTuple_Check(pyobj)) \
	{\
		unsigned char *col = new unsigned char[4]; \
		PyArg_ParseTuple(pyobj, "bbbb", &col[3], &col[2], &col[1], &col[0]); \
		colcode = *(unsigned int*)col; \
		_del(col); \
	}\
	else\
	{\
		colcode = PyLong_AsUnsignedLong(pyobj); \
	}

//-----------------------------------------
// AMX function reference definitions
//-----------------------------------------
extern amx_function_t _addMenuItem;
extern amx_function_t _addPlayerClass;
extern amx_function_t _addPlayerClassEx;
extern amx_function_t _addStaticPickup;
extern amx_function_t _addStaticVehicle;
extern amx_function_t _addStaticVehicleEx;
extern amx_function_t _addVehicleComponent;
extern amx_function_t _allowAdminTeleport;
extern amx_function_t _allowInteriorWeapons;
extern amx_function_t _allowPlayerTeleport;
extern amx_function_t _applyAnimation;
extern amx_function_t _attach3DTextLabelToPlayer;
extern amx_function_t _attach3DTextLabelToVehicle;
extern amx_function_t _attachCameraToObject;
extern amx_function_t _attachCameraToPlayerObject;
extern amx_function_t _attachObjectToObject;
extern amx_function_t _attachObjectToPlayer;
extern amx_function_t _attachObjectToVehicle;
extern amx_function_t _attachPlayerObjectToPlayer;
extern amx_function_t _attachPlayerObjectToVehicle;
extern amx_function_t _attachTrailerToVehicle;

extern amx_function_t _ban;
extern amx_function_t _banEx;

extern amx_function_t _cancelEdit;
extern amx_function_t _cancelSelectTextDraw;
extern amx_function_t _changeVehicleColor;
extern amx_function_t _changeVehiclePaintjob;
extern amx_function_t _clearAnimations;
extern amx_function_t _connectNPC;
extern amx_function_t _create3DTextLabel;
extern amx_function_t _createExplosion;
extern amx_function_t _createMenu;
extern amx_function_t _createObject;
extern amx_function_t _createPickup;
extern amx_function_t _createPlayer3DTextLabel;
extern amx_function_t _createPlayerObject;
extern amx_function_t _createVehicle;

extern amx_function_t _delete3DTextLabel;
extern amx_function_t _deletePlayer3DTextLabel;
extern amx_function_t _destroyMenu;
extern amx_function_t _destroyObject;
extern amx_function_t _destroyPickup;
extern amx_function_t _destroyPlayerObject;
extern amx_function_t _destroyVehicle;
extern amx_function_t _detachTrailerFromVehicle;
extern amx_function_t _disableInteriorEnterExits;
extern amx_function_t _disableMenu;
extern amx_function_t _disableMenuRow;
extern amx_function_t _disableNameTagLOS;
extern amx_function_t _disablePlayerCheckpoint;
extern amx_function_t _disablePlayerRaceCheckpoint;

extern amx_function_t _editObject;
extern amx_function_t _editPlayerObject;
extern amx_function_t _editAttachedObject;
extern amx_function_t _enableStuntBonusForAll;
extern amx_function_t _enableStuntBonusForPlayer;
extern amx_function_t _forceClassSelection;

extern amx_function_t _gameModeExit;
extern amx_function_t _gameTextForAll;
extern amx_function_t _gameTextForPlayer;
extern amx_function_t _gangZoneCreate;
extern amx_function_t _gangZoneDestroy;
extern amx_function_t _gangZoneFlashForAll;
extern amx_function_t _gangZoneFlashForPlayer;
extern amx_function_t _gangZoneHideForAll;
extern amx_function_t _gangZoneHideForPlayer;
extern amx_function_t _gangZoneShowForAll;
extern amx_function_t _gangZoneShowForPlayer;
extern amx_function_t _gangZoneStopFlashForAll;
extern amx_function_t _gangZoneStopFlashForPlayer;
extern amx_function_t _getAnimationName;
extern amx_function_t _getMaxPlayers;
extern amx_function_t _getNetworkStats;
extern amx_function_t _getObjectPos;
extern amx_function_t _getObjectRot;
extern amx_function_t _getPlayerAmmo;
extern amx_function_t _getPlayerAnimationIndex;
extern amx_function_t _getPlayerArmour;
extern amx_function_t _getPlayerCameraFrontVector;
extern amx_function_t _getPlayerCameraMode;
extern amx_function_t _getPlayerCameraPos;
extern amx_function_t _getPlayerColor;
extern amx_function_t _getPlayerDistanceFromPoint;
extern amx_function_t _getPlayerDrunkLevel;
extern amx_function_t _getPlayerFacingAngle;
extern amx_function_t _getPlayerFightingStyle;
extern amx_function_t _getPlayerHealth;
extern amx_function_t _getPlayerInterior;
extern amx_function_t _getPlayerIp;
extern amx_function_t _getPlayerKeys;
extern amx_function_t _getPlayerMenu;
extern amx_function_t _getPlayerMoney;
extern amx_function_t _getPlayerName;
extern amx_function_t _getPlayerNetworkStats;
extern amx_function_t _getPlayerObjectPos;
extern amx_function_t _getPlayerObjectRot;
extern amx_function_t _getPlayerPing;
extern amx_function_t _getPlayerPos;

extern amx_function_t _getPlayerScore;
extern amx_function_t _getPlayerSkin;
extern amx_function_t _getPlayerSpecialAction;
extern amx_function_t _getPlayerState;
extern amx_function_t _getPlayerSurfingObjectID;
extern amx_function_t _getPlayerSurfingVehicleID;
extern amx_function_t _getPlayerTargetPlayer;
extern amx_function_t _getPlayerTeam;
extern amx_function_t _getPlayerTime;
extern amx_function_t _getPlayerVehicleID;
extern amx_function_t _getPlayerVehicleSeat;
extern amx_function_t _getPlayerVelocity;
extern amx_function_t _getPlayerVersion;
extern amx_function_t _getPlayerVirtualWorld;
extern amx_function_t _getPlayerWantedLevel;
extern amx_function_t _getPlayerWeapon;
extern amx_function_t _getPlayerWeaponData;
extern amx_function_t _getPlayerWeaponState;
extern amx_function_t _getTickCount;
extern amx_function_t _getVehicleComponentInSlot;
extern amx_function_t _getVehicleComponentType;
extern amx_function_t _getVehicleDamageStatus;
extern amx_function_t _getVehicleDistanceFromPoint;
extern amx_function_t _getVehicleHealth;
extern amx_function_t _getVehicleModel;
extern amx_function_t _getVehicleModelInfo;
extern amx_function_t _getVehiclePos;
extern amx_function_t _getVehicleRotationQuat;
extern amx_function_t _getVehicleTrailer;
extern amx_function_t _getVehicleVelocity;
extern amx_function_t _getVehicleVirtualWorld;
extern amx_function_t _getVehicleZAngle;
extern amx_function_t _getWeaponName;
extern amx_function_t _givePlayerMoney;
extern amx_function_t _givePlayerWeapon;

extern amx_function_t _hideMenuForPlayer;

extern amx_function_t _interpolateCameraPos;
extern amx_function_t _interpolateCameraLookAt;
extern amx_function_t _isObjectMoving;
extern amx_function_t _isPlayerAdmin;
extern amx_function_t _isPlayerAttachedObjectSlotUsed;
extern amx_function_t _isPlayerConnected;
extern amx_function_t _isPlayerHoldingObject;
extern amx_function_t _isPlayerInAnyVehicle;
extern amx_function_t _isPlayerInCheckpoint;
extern amx_function_t _isPlayerInRaceCheckpoint;
extern amx_function_t _isPlayerInRangeOfPoint;
extern amx_function_t _isPlayerInVehicle;
extern amx_function_t _isPlayerNPC;
extern amx_function_t _isPlayerObjectMoving;
extern amx_function_t _isPlayerStreamedIn;
extern amx_function_t _isTrailerAttachedToVehicle;
extern amx_function_t _isValidMenu;
extern amx_function_t _isValidObject;
extern amx_function_t _isValidPlayerObject;
extern amx_function_t _isVehicleStreamedIn;

extern amx_function_t _kick;
extern amx_function_t _killTimer;

extern amx_function_t _limitGlobalChatRadius;
extern amx_function_t _limitPlayerMarkerRadius;
extern amx_function_t _linkVehicleToInterior;

extern amx_function_t _manualVehicleEngineAndLights;
extern amx_function_t _moveObject;
extern amx_function_t _movePlayerObject;

extern amx_function_t _playAudioStreamForPlayer;
extern amx_function_t _playCrimeReportForPlayer;
extern amx_function_t _playerPlaySound;
extern amx_function_t _playerSpectatePlayer;
extern amx_function_t _playerSpectateVehicle;
extern amx_function_t _putPlayerInVehicle;

extern amx_function_t _createPlayerTextDraw;
extern amx_function_t _playerTextDrawDestroy;
extern amx_function_t _playerTextDrawLetterSize;
extern amx_function_t _playerTextDrawTextSize;
extern amx_function_t _playerTextDrawAlignment;
extern amx_function_t _playerTextDrawColor;
extern amx_function_t _playerTextDrawUseBox;
extern amx_function_t _playerTextDrawBoxColor;
extern amx_function_t _playerTextDrawSetShadow;
extern amx_function_t _playerTextDrawSetOutline;
extern amx_function_t _playerTextDrawBackgroundColor;
extern amx_function_t _playerTextDrawFont;
extern amx_function_t _playerTextDrawSetProportional;
extern amx_function_t _playerTextDrawSetSelectable;
extern amx_function_t _playerTextDrawShow;
extern amx_function_t _playerTextDrawHide;
extern amx_function_t _playerTextDrawSetString;

extern amx_function_t _removeBuildingForPlayer;
extern amx_function_t _removePlayerAttachedObject;
extern amx_function_t _removePlayerFromVehicle;
extern amx_function_t _removePlayerMapIcon;
extern amx_function_t _removeVehicleComponent;
extern amx_function_t _repairVehicle;
extern amx_function_t _resetPlayerMoney;
extern amx_function_t _resetPlayerWeapons;

extern amx_function_t _selectObject;
extern amx_function_t _selectTextDraw;
extern amx_function_t _sendClientMessage;
extern amx_function_t _sendClientMessageToAll;
extern amx_function_t _sendDeathMessage;
extern amx_function_t _sendPlayerMessageToAll;
extern amx_function_t _sendPlayerMessageToPlayer;
extern amx_function_t _sendRconCommand;
extern amx_function_t _setCameraBehindPlayer;
extern amx_function_t _setGameModeText;
extern amx_function_t _setGravity;
extern amx_function_t _setMenuColumnHeader;
extern amx_function_t _setNameTagDrawDistance;
extern amx_function_t _setObjectMaterial;
extern amx_function_t _setObjectMaterialText;
extern amx_function_t _setObjectPos;
extern amx_function_t _setObjectRot;
extern amx_function_t _setPlayerAmmo;
extern amx_function_t _setPlayerArmedWeapon;
extern amx_function_t _setPlayerArmour;
extern amx_function_t _setPlayerAttachedObject;
extern amx_function_t _setPlayerCameraLookAt;
extern amx_function_t _setPlayerCameraPos;
extern amx_function_t _setPlayerChatBubble;
extern amx_function_t _setPlayerCheckpoint;
extern amx_function_t _setPlayerColor;
extern amx_function_t _setPlayerDrunkLevel;
extern amx_function_t _setPlayerFacingAngle;
extern amx_function_t _setPlayerFightingStyle;
extern amx_function_t _setPlayerHealth;
extern amx_function_t _setPlayerHoldingObject;
extern amx_function_t _setPlayerInterior;
extern amx_function_t _setPlayerMapIcon;
extern amx_function_t _setPlayerMarkerForPlayer;
extern amx_function_t _setPlayerName;
extern amx_function_t _setPlayerObjectMaterial;
extern amx_function_t _setPlayerObjectMaterialText;
extern amx_function_t _setPlayerObjectPos;
extern amx_function_t _setPlayerObjectRot;
extern amx_function_t _setPlayerPos;
extern amx_function_t _setPlayerPosFindZ;
extern amx_function_t _setPlayerRaceCheckpoint;
extern amx_function_t _setPlayerScore;
extern amx_function_t _setPlayerShopName;
extern amx_function_t _setPlayerSkillLevel;
extern amx_function_t _setPlayerSkin;
extern amx_function_t _setPlayerSpecialAction;
extern amx_function_t _setPlayerTeam;
extern amx_function_t _setPlayerTime;
extern amx_function_t _setPlayerVelocity;
extern amx_function_t _setPlayerVirtualWorld;
extern amx_function_t _setPlayerWantedLevel;
extern amx_function_t _setPlayerWeather;
extern amx_function_t _setPlayerWorldBounds;
extern amx_function_t _setSpawnInfo;
extern amx_function_t _setTeamCount;
extern amx_function_t _setTimerEx;
extern amx_function_t _setVehicleAngularVelocity;
extern amx_function_t _setVehicleHealth;
extern amx_function_t _setVehicleNumberPlate;
extern amx_function_t _setVehicleParamsEx;
extern amx_function_t _setVehicleParamsForPlayer;
extern amx_function_t _setVehiclePos;
extern amx_function_t _setVehicleToRespawn;
extern amx_function_t _setVehicleVelocity;
extern amx_function_t _setVehicleVirtualWorld;
extern amx_function_t _setVehicleZAngle;
extern amx_function_t _setWeather;
extern amx_function_t _setWorldTime;
extern amx_function_t _showMenuForPlayer;
extern amx_function_t _showNameTags;
extern amx_function_t _showPlayerDialog;
extern amx_function_t _showPlayerMarkers;
extern amx_function_t _showPlayerNameTagForPlayer;
extern amx_function_t _spawnPlayer;
extern amx_function_t _startRecordingPlayerData;
extern amx_function_t _stopAudioStreamForPlayer;
extern amx_function_t _stopObject;
extern amx_function_t _stopPlayerHoldingObject;
extern amx_function_t _stopPlayerObject;
extern amx_function_t _stopRecordingPlayerData;

extern amx_function_t _textDrawAlignment;
extern amx_function_t _textDrawBackgroundColor;
extern amx_function_t _textDrawBoxColor;
extern amx_function_t _textDrawColor;
extern amx_function_t _textDrawCreate;
extern amx_function_t _textDrawDestroy;
extern amx_function_t _textDrawFont;
extern amx_function_t _textDrawHideForAll;
extern amx_function_t _textDrawHideForPlayer;
extern amx_function_t _textDrawLetterSize;
extern amx_function_t _textDrawSetOutline;
extern amx_function_t _textDrawSetProportional;
extern amx_function_t _textDrawSetSelectable;
extern amx_function_t _textDrawSetShadow;
extern amx_function_t _textDrawSetString;
extern amx_function_t _textDrawShowForAll;
extern amx_function_t _textDrawShowForPlayer;
extern amx_function_t _textDrawTextSize;
extern amx_function_t _textDrawUseBox;
extern amx_function_t _togglePlayerClock;
extern amx_function_t _togglePlayerControllable;
extern amx_function_t _togglePlayerSpectating;

extern amx_function_t _update3DTextLabelText;
extern amx_function_t _updatePlayer3DTextLabelText;
extern amx_function_t _updateVehicleDamageStatus;
extern amx_function_t _usePlayerPedAnims;


//-----------------------------------------
// function definitions
//-----------------------------------------

PyObject *sPrintf(PyObject *self, PyObject *args);

PyObject *sAddMenuItem(PyObject *self, PyObject *args);
PyObject *sAddPlayerClass(PyObject *self, PyObject *args);
PyObject *sAddPlayerClassEx(PyObject *self, PyObject *args);
PyObject *sAddStaticPickup(PyObject *self, PyObject *args);
PyObject *sAddStaticVehicle(PyObject *self, PyObject *args);
PyObject *sAddStaticVehicleEx(PyObject *self, PyObject *args);
PyObject *sAddVehicleComponent(PyObject *self, PyObject *args);
PyObject *sAllowAdminTeleport(PyObject *self, PyObject *args);
PyObject *sAllowInteriorWeapons(PyObject *self, PyObject *args);
PyObject *sAllowPlayerTeleport(PyObject *self, PyObject *args);
PyObject *sApplyAnimation(PyObject *self, PyObject *args);
PyObject *sAttach3DTextLabelToPlayer(PyObject *self, PyObject *args);
PyObject *sAttach3DTextLabelToVehicle(PyObject *self, PyObject *args);
PyObject *sAttachCameraToObject(PyObject *self, PyObject *args);
PyObject *sAttachCameraToPlayerObject(PyObject *self, PyObject *args);
PyObject *sAttachObjectToObject(PyObject *self, PyObject *args);
PyObject *sAttachObjectToPlayer(PyObject *self, PyObject *args);
PyObject *sAttachObjectToVehicle(PyObject *self, PyObject *args);
PyObject *sAttachPlayerObjectToPlayer(PyObject *self, PyObject *args);
PyObject *sAttachPlayerObjectToVehicle(PyObject *self, PyObject *args);
PyObject *sAttachTrailerToVehicle(PyObject *self, PyObject *args);

PyObject *sBan(PyObject *self, PyObject *args);
PyObject *sBanEx(PyObject *self, PyObject *args);

PyObject *sCancelEdit(PyObject *self, PyObject *args);
PyObject *sCancelSelectTextDraw(PyObject *self, PyObject *args);
PyObject *sChangeVehicleColor(PyObject *self, PyObject *args);
PyObject *sChangeVehiclePaintjob(PyObject *self, PyObject *args);
PyObject *sClearAnimations(PyObject *self, PyObject *args);
PyObject *sConnectNPC(PyObject *self, PyObject *args);
PyObject *sCreate3DTextLabel(PyObject *self, PyObject *args);
PyObject *sCreateExplosion(PyObject *self, PyObject *args);
PyObject *sCreateMenu(PyObject *self, PyObject *args);
PyObject *sCreateObject(PyObject *self, PyObject *args);
PyObject *sCreatePickup(PyObject *self, PyObject *args);
PyObject *sCreatePlayer3DTextLabel(PyObject *self, PyObject *args);
PyObject *sCreatePlayerObject(PyObject *self, PyObject *args);
PyObject *sCreateVehicle(PyObject *self, PyObject *args);

PyObject *sDelete3DTextLabel(PyObject *self, PyObject *args);
PyObject *sDeletePlayer3DTextLabel(PyObject *self, PyObject *args);
PyObject *sDestroyMenu(PyObject *self, PyObject *args);
PyObject *sDestroyObject(PyObject *self, PyObject *args);
PyObject *sDestroyPickup(PyObject *self, PyObject *args);
PyObject *sDestroyPlayerObject(PyObject *self, PyObject *args);
PyObject *sDestroyVehicle(PyObject *self, PyObject *args);
PyObject *sDetachTrailerFromVehicle(PyObject *self, PyObject *args);
PyObject *sDisableInteriorEnterExits(PyObject *self, PyObject *args);
PyObject *sDisableMenu(PyObject *self, PyObject *args);
PyObject *sDisableMenuRow(PyObject *self, PyObject *args);
PyObject *sDisableNameTagLOS(PyObject *self, PyObject *args);
PyObject *sDisablePlayerCheckpoint(PyObject *self, PyObject *args);
PyObject *sDisablePlayerRaceCheckpoint(PyObject *self, PyObject *args);

PyObject *sEditObject(PyObject *self, PyObject *args);
PyObject *sEditPlayerObject(PyObject *self, PyObject *args);
PyObject *sEditAttachedObject(PyObject *self, PyObject *args);
PyObject *sEnableStuntBonusForAll(PyObject *self, PyObject *args);
PyObject *sEnableStuntBonusForPlayer(PyObject *self, PyObject *args);
PyObject *sForceClassSelection(PyObject *self, PyObject *args);

PyObject *sGameModeExit(PyObject *self, PyObject *args);
PyObject *sGameTextForAll(PyObject *self, PyObject *args);
PyObject *sGameTextForPlayer(PyObject *self, PyObject *args);
PyObject *sGangZoneCreate(PyObject *self, PyObject *args);
PyObject *sGangZoneDestroy(PyObject *self, PyObject *args);
PyObject *sGangZoneFlashForAll(PyObject *self, PyObject *args);
PyObject *sGangZoneFlashForPlayer(PyObject *self, PyObject *args);
PyObject *sGangZoneHideForAll(PyObject *self, PyObject *args);
PyObject *sGangZoneHideForPlayer(PyObject *self, PyObject *args);
PyObject *sGangZoneShowForAll(PyObject *self, PyObject *args);
PyObject *sGangZoneShowForPlayer(PyObject *self, PyObject *args);
PyObject *sGangZoneStopFlashForAll(PyObject *self, PyObject *args);
PyObject *sGangZoneStopFlashForPlayer(PyObject *self, PyObject *args);
PyObject *sGetAnimationName(PyObject *self, PyObject *args);
PyObject *sGetMaxPlayers(PyObject *self, PyObject *args);
PyObject *sGetNetworkStats(PyObject *self, PyObject *args);
PyObject *sGetObjectPos(PyObject *self, PyObject *args);
PyObject *sGetObjectRot(PyObject *self, PyObject *args);
PyObject *sGetPlayerAmmo(PyObject *self, PyObject *args);
PyObject *sGetPlayerAnimationIndex(PyObject *self, PyObject *args);
PyObject *sGetPlayerArmour(PyObject *self, PyObject *args);
PyObject *sGetPlayerCameraFrontVector(PyObject *self, PyObject *args);
PyObject *sGetPlayerCameraMode(PyObject *self, PyObject *args);
PyObject *sGetPlayerCameraPos(PyObject *self, PyObject *args);
PyObject *sGetPlayerColor(PyObject *self, PyObject *args);
PyObject *sGetPlayerDistanceFromPoint(PyObject *self, PyObject *args);
PyObject *sGetPlayerDrunkLevel(PyObject *self, PyObject *args);
PyObject *sGetPlayerFacingAngle(PyObject *self, PyObject *args);
PyObject *sGetPlayerFightingStyle(PyObject *self, PyObject *args);
PyObject *sGetPlayerHealth(PyObject *self, PyObject *args);
PyObject *sGetPlayerInterior(PyObject *self, PyObject *args);
PyObject *sGetPlayerIp(PyObject *self, PyObject *args);
PyObject *sGetPlayerKeys(PyObject *self, PyObject *args);
PyObject *sGetPlayerMenu(PyObject *self, PyObject *args);
PyObject *sGetPlayerMoney(PyObject *self, PyObject *args);
PyObject *sGetPlayerName(PyObject *self, PyObject *args);
PyObject *sGetPlayerNetworkStats(PyObject *self, PyObject *args);
PyObject *sGetPlayerObjectPos(PyObject *self, PyObject *args);
PyObject *sGetPlayerObjectRot(PyObject *self, PyObject *args);
PyObject *sGetPlayerPing(PyObject *self, PyObject *args);
PyObject *sGetPlayerPos(PyObject *self, PyObject *args);
PyObject *sGetPlayerScore(PyObject *self, PyObject *args);
PyObject *sGetPlayerSkin(PyObject *self, PyObject *args);
PyObject *sGetPlayerSpecialAction(PyObject *self, PyObject *args);
PyObject *sGetPlayerState(PyObject *self, PyObject *args);
PyObject *sGetPlayerSurfingObjectID(PyObject *self, PyObject *args);
PyObject *sGetPlayerSurfingVehicleID(PyObject *self, PyObject *args);
PyObject *sGetPlayerTargetPlayer(PyObject *self, PyObject *args);
PyObject *sGetPlayerTeam(PyObject *self, PyObject *args);
PyObject *sGetPlayerTime(PyObject *self, PyObject *args);
PyObject *sGetPlayerVehicleID(PyObject *self, PyObject *args);
PyObject *sGetPlayerVehicleSeat(PyObject *self, PyObject *args);
PyObject *sGetPlayerVelocity(PyObject *self, PyObject *args);
PyObject *sGetPlayerVersion(PyObject *self, PyObject *args);
PyObject *sGetPlayerVirtualWorld(PyObject *self, PyObject *args);
PyObject *sGetPlayerWantedLevel(PyObject *self, PyObject *args);
PyObject *sGetPlayerWeapon(PyObject *self, PyObject *args);
PyObject *sGetPlayerWeaponData(PyObject *self, PyObject *args);
PyObject *sGetPlayerWeaponState(PyObject *self, PyObject *args);
PyObject *sGetTickCount(PyObject *self, PyObject *args);
PyObject *sGetVehicleComponentInSlot(PyObject *self, PyObject *args);
PyObject *sGetVehicleComponentType(PyObject *self, PyObject *args);
PyObject *sGetVehicleDamageStatus(PyObject *self, PyObject *args);
PyObject *sGetVehicleDistanceFromPoint(PyObject *self, PyObject *args);
PyObject *sGetVehicleHealth(PyObject *self, PyObject *args);
PyObject *sGetVehicleModel(PyObject *self, PyObject *args);
PyObject *sGetVehicleModelInfo(PyObject *self, PyObject *args);
PyObject *sGetVehiclePos(PyObject *self, PyObject *args);
PyObject *sGetVehicleRotationQuat(PyObject *self, PyObject *args);
PyObject *sGetVehicleTrailer(PyObject *self, PyObject *args);
PyObject *sGetVehicleVelocity(PyObject *self, PyObject *args);
PyObject *sGetVehicleVirtualWorld(PyObject *self, PyObject *args);
PyObject *sGetVehicleZAngle(PyObject *self, PyObject *args);
PyObject *sGetWeaponName(PyObject *self, PyObject *args);
PyObject *sGivePlayerMoney(PyObject *self, PyObject *args);
PyObject *sGivePlayerWeapon(PyObject *self, PyObject *args);

PyObject *sHideMenuForPlayer(PyObject *self, PyObject *args);

PyObject *sInterpolateCameraPos(PyObject *self, PyObject *args);
PyObject *sInterpolateCameraLookAt(PyObject *self, PyObject *args);
PyObject *sIsObjectMoving(PyObject *self, PyObject *args);
PyObject *sIsPlayerAdmin(PyObject *self, PyObject *args);
PyObject *sIsPlayerAttachedObjectSlotUsed(PyObject *self, PyObject *args);
PyObject *sIsPlayerConnected(PyObject *self, PyObject *args);
PyObject *sIsPlayerHoldingObject(PyObject *self, PyObject *args);
PyObject *sIsPlayerInAnyVehicle(PyObject *self, PyObject *args);
PyObject *sIsPlayerInCheckpoint(PyObject *self, PyObject *args);
PyObject *sIsPlayerInRaceCheckpoint(PyObject *self, PyObject *args);
PyObject *sIsPlayerInRangeOfPoint(PyObject *self, PyObject *args);
PyObject *sIsPlayerInVehicle(PyObject *self, PyObject *args);
PyObject *sIsPlayerNPC(PyObject *self, PyObject *args);
PyObject *sIsPlayerObjectMoving(PyObject *self, PyObject *args);
PyObject *sIsPlayerStreamedIn(PyObject *self, PyObject *args);
PyObject *sIsTrailerAttachedToVehicle(PyObject *self, PyObject *args);
PyObject *sIsValidMenu(PyObject *self, PyObject *args);
PyObject *sIsValidObject(PyObject *self, PyObject *args);
PyObject *sIsValidPlayerObject(PyObject *self, PyObject *args);
PyObject *sIsVehicleStreamedIn(PyObject *self, PyObject *args);

PyObject *sKick(PyObject *self, PyObject *args);
PyObject *sKillTimer(PyObject *self, PyObject *args);

PyObject *sLimitGlobalChatRadius(PyObject *self, PyObject *args);
PyObject *sLimitPlayerMarkerRadius(PyObject *self, PyObject *args);
PyObject *sLinkVehicleToInterior(PyObject *self, PyObject *args);

PyObject *sManualVehicleEngineAndLights(PyObject *self, PyObject *args);
PyObject *sMoveObject(PyObject *self, PyObject *args);
PyObject *sMovePlayerObject(PyObject *self, PyObject *args);

PyObject *sPlayAudioStreamForPlayer(PyObject *self, PyObject *args);
PyObject *sPlayCrimeReportForPlayer(PyObject *self, PyObject *args);
PyObject *sPlayerPlaySound(PyObject *self, PyObject *args);
PyObject *sPlayerSpectatePlayer(PyObject *self, PyObject *args);
PyObject *sPlayerSpectateVehicle(PyObject *self, PyObject *args);
PyObject *sPutPlayerInVehicle(PyObject *self, PyObject *args);

PyObject *sCreatePlayerTextDraw(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawDestroy(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawLetterSize(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawTextSize(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawAlignment(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawColor(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawUseBox(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawBoxColor(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawSetShadow(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawSetOutline(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawBackgroundColor(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawFont(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawSetProportional(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawSetSelectable(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawShow(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawHide(PyObject *self, PyObject *args);
PyObject *sPlayerTextDrawSetString(PyObject *self, PyObject *args);

PyObject *sRemoveBuildingForPlayer(PyObject *self, PyObject *args);
PyObject *sRemovePlayerAttachedObject(PyObject *self, PyObject *args);
PyObject *sRemovePlayerFromVehicle(PyObject *self, PyObject *args);
PyObject *sRemovePlayerMapIcon(PyObject *self, PyObject *args);
PyObject *sRemoveVehicleComponent(PyObject *self, PyObject *args);
PyObject *sRepairVehicle(PyObject *self, PyObject *args);
PyObject *sResetPlayerMoney(PyObject *self, PyObject *args);
PyObject *sResetPlayerWeapons(PyObject *self, PyObject *args);

PyObject *sSelectObject(PyObject *self, PyObject *args);
PyObject *sSelectTextDraw(PyObject *self, PyObject *args);
PyObject *sSendClientMessage(PyObject *self, PyObject *args);
PyObject *sSendClientMessageToAll(PyObject *self, PyObject *args);
PyObject *sSendDeathMessage(PyObject *self, PyObject *args);
PyObject *sSendPlayerMessageToAll(PyObject *self, PyObject *args);
PyObject *sSendPlayerMessageToPlayer(PyObject *self, PyObject *args);
PyObject *sSendRconCommand(PyObject *self, PyObject *args);
PyObject *sSetCameraBehindPlayer(PyObject *self, PyObject *args);
PyObject *sSetGameModeText(PyObject *self, PyObject *args);
PyObject *sSetGravity(PyObject *self, PyObject *args);
PyObject *sSetMenuColumnHeader(PyObject *self, PyObject *args);
PyObject *sSetNameTagDrawDistance(PyObject *self, PyObject *args);
PyObject *sSetObjectMaterial(PyObject *self, PyObject *args);
PyObject *sSetObjectMaterialText(PyObject *self, PyObject *args);
PyObject *sSetObjectPos(PyObject *self, PyObject *args);
PyObject *sSetObjectRot(PyObject *self, PyObject *args);
PyObject *sSetPlayerAmmo(PyObject *self, PyObject *args);
PyObject *sSetPlayerArmedWeapon(PyObject *self, PyObject *args);
PyObject *sSetPlayerArmour(PyObject *self, PyObject *args);
PyObject *sSetPlayerAttachedObject(PyObject *self, PyObject *args);
PyObject *sSetPlayerCameraLookAt(PyObject *self, PyObject *args);
PyObject *sSetPlayerCameraPos(PyObject *self, PyObject *args);
PyObject *sSetPlayerChatBubble(PyObject *self, PyObject *args);
PyObject *sSetPlayerCheckpoint(PyObject *self, PyObject *args);
PyObject *sSetPlayerColor(PyObject *self, PyObject *args);
PyObject *sSetPlayerDrunkLevel(PyObject *self, PyObject *args);
PyObject *sSetPlayerFacingAngle(PyObject *self, PyObject *args);
PyObject *sSetPlayerFightingStyle(PyObject *self, PyObject *args);
PyObject *sSetPlayerHealth(PyObject *self, PyObject *args);
PyObject *sSetPlayerHoldingObject(PyObject *self, PyObject *args);
PyObject *sSetPlayerInterior(PyObject *self, PyObject *args);
PyObject *sSetPlayerMapIcon(PyObject *self, PyObject *args);
PyObject *sSetPlayerMarkerForPlayer(PyObject *self, PyObject *args);
PyObject *sSetPlayerName(PyObject *self, PyObject *args);
PyObject *sSetPlayerObjectMaterial(PyObject *self, PyObject *args);
PyObject *sSetPlayerObjectMaterialText(PyObject *self, PyObject *args);
PyObject *sSetPlayerObjectPos(PyObject *self, PyObject *args);
PyObject *sSetPlayerObjectRot(PyObject *self, PyObject *args);
PyObject *sSetPlayerPos(PyObject *self, PyObject *args);
PyObject *sSetPlayerPosFindZ(PyObject *self, PyObject *args);
PyObject *sSetPlayerRaceCheckpoint(PyObject *self, PyObject *args);
PyObject *sSetPlayerScore(PyObject *self, PyObject *args);
PyObject *sSetPlayerShopName(PyObject *self, PyObject *args);
PyObject *sSetPlayerSkillLevel(PyObject *self, PyObject *args);
PyObject *sSetPlayerSkin(PyObject *self, PyObject *args);
PyObject *sSetPlayerSpecialAction(PyObject *self, PyObject *args);
PyObject *sSetPlayerTeam(PyObject *self, PyObject *args);
PyObject *sSetPlayerTime(PyObject *self, PyObject *args);
PyObject *sSetPlayerVelocity(PyObject *self, PyObject *args);
PyObject *sSetPlayerVirtualWorld(PyObject *self, PyObject *args);
PyObject *sSetPlayerWantedLevel(PyObject *self, PyObject *args);
PyObject *sSetPlayerWeather(PyObject *self, PyObject *args);
PyObject *sSetPlayerWorldBounds(PyObject *self, PyObject *args);
PyObject *sSetSpawnInfo(PyObject *self, PyObject *args);
PyObject *sSetTeamCount(PyObject *self, PyObject *args);
PyObject *sSetTimer(PyObject *self, PyObject *args);
PyObject *sSetVehicleAngularVelocity(PyObject *self, PyObject *args);
PyObject *sSetVehicleHealth(PyObject *self, PyObject *args);
PyObject *sSetVehicleNumberPlate(PyObject *self, PyObject *args);
PyObject *sSetVehicleParamsEx(PyObject *self, PyObject *args);
PyObject *sSetVehicleParamsForPlayer(PyObject *self, PyObject *args);
PyObject *sSetVehiclePos(PyObject *self, PyObject *args);
PyObject *sSetVehicleToRespawn(PyObject *self, PyObject *args);
PyObject *sSetVehicleVelocity(PyObject *self, PyObject *args);
PyObject *sSetVehicleVirtualWorld(PyObject *self, PyObject *args);
PyObject *sSetVehicleZAngle(PyObject *self, PyObject *args);
PyObject *sSetWeather(PyObject *self, PyObject *args);
PyObject *sSetWorldTime(PyObject *self, PyObject *args);
PyObject *sShowMenuForPlayer(PyObject *self, PyObject *args);
PyObject *sShowNameTags(PyObject *self, PyObject *args);
PyObject *sShowPlayerDialog(PyObject *self, PyObject *args);
PyObject *sShowPlayerMarkers(PyObject *self, PyObject *args);
PyObject *sShowPlayerNameTagForPlayer(PyObject *self, PyObject *args);
PyObject *sSpawnPlayer(PyObject *self, PyObject *args);
PyObject *sStartRecordingPlayerData(PyObject *self, PyObject *args);
PyObject *sStopAudioStreamForPlayer(PyObject *self, PyObject *args);
PyObject *sStopObject(PyObject *self, PyObject *args);
PyObject *sStopPlayerHoldingObject(PyObject *self, PyObject *args);
PyObject *sStopPlayerObject(PyObject *self, PyObject *args);
PyObject *sStopRecordingPlayerData(PyObject *self, PyObject *args);

PyObject *sTextDrawAlignment(PyObject *self, PyObject *args);
PyObject *sTextDrawBackgroundColor(PyObject *self, PyObject *args);
PyObject *sTextDrawBoxColor(PyObject *self, PyObject *args);
PyObject *sTextDrawColor(PyObject *self, PyObject *args);
PyObject *sTextDrawCreate(PyObject *self, PyObject *args);
PyObject *sTextDrawDestroy(PyObject *self, PyObject *args);
PyObject *sTextDrawFont(PyObject *self, PyObject *args);
PyObject *sTextDrawHideForAll(PyObject *self, PyObject *args);
PyObject *sTextDrawHideForPlayer(PyObject *self, PyObject *args);
PyObject *sTextDrawLetterSize(PyObject *self, PyObject *args);
PyObject *sTextDrawSetOutline(PyObject *self, PyObject *args);
PyObject *sTextDrawSetProportional(PyObject *self, PyObject *args);
PyObject *sTextDrawSetSelectable(PyObject *self, PyObject *args);
PyObject *sTextDrawSetShadow(PyObject *self, PyObject *args);
PyObject *sTextDrawSetString(PyObject *self, PyObject *args);
PyObject *sTextDrawShowForAll(PyObject *self, PyObject *args);
PyObject *sTextDrawShowForPlayer(PyObject *self, PyObject *args);
PyObject *sTextDrawTextSize(PyObject *self, PyObject *args);
PyObject *sTextDrawUseBox(PyObject *self, PyObject *args);
PyObject *sTogglePlayerClock(PyObject *self, PyObject *args);
PyObject *sTogglePlayerControllable(PyObject *self, PyObject *args);
PyObject *sTogglePlayerSpectating(PyObject *self, PyObject *args);

PyObject *sUpdate3DTextLabelText(PyObject *self, PyObject *args);
PyObject *sUpdatePlayer3DTextLabelText(PyObject *self, PyObject *args);
PyObject *sUpdateVehicleDamageStatus(PyObject *self, PyObject *args);
PyObject *sUsePlayerPedAnims(PyObject *self, PyObject *args);

PyObject *sInvokeFunction(PyObject *self, PyObject *args);

//-----------------------------------------
// callbacks
//-----------------------------------------

//cell AMX_NATIVE_CALL n_OnTimerTick(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnDialogResponse(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnEnterExitModShop(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnObjectMoved(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerClickPlayer(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerClickTextDraw(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerClickPlayerTextDraw(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerCommandText(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerConnect(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerDeath(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerDisconnect(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerEditObject(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerEditAttachedObject(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerEnterCheckpoint(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerEnterRaceCheckpoint(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerEnterVehicle(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerExitVehicle(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerExitedMenu(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerInteriorChange(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerKeyStateChange(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerLeaveCheckpoint(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerLeaveRaceCheckpoint(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerObjectMoved(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerPickUpPickup(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerRequestClass(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerRequestSpawn(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerSelectedMenuRow(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerSelectObject(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerSpawn(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerStateChange(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerStreamIn(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerStreamOut(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerText(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerUpdate(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnRconCommand(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnRconLoginAttempt(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleDamageStatusUpdate(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleDeath(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleMod(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehiclePaintjob(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleRespray(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleSpawn(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleStreamIn(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnVehicleStreamOut(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_OnUnoccupiedVehicleUpdate(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerTakeDamage(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerGiveDamage(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_OnPlayerClickMap(AMX *amx, cell *params);


#endif
