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

#include "pythonplugin.h"
#include <frameobject.h> // used for building the traceback
#include "nativefunctions.h"
#include "pysamp.h"
#include "constants.h"

// ----------------------------------
// python module for the samp functions
// ----------------------------------

PyMethodDef _pySampMethods[] =
{
	{ "printf", sPrintf, METH_VARARGS, "Prints to the log" },

	{ "AddMenuItem", sAddMenuItem, METH_VARARGS, "" },
	{ "AddPlayerClass", sAddPlayerClass, METH_VARARGS, "Adds a class to the class selection" },
	{ "AddPlayerClassEx", sAddPlayerClassEx, METH_VARARGS, "" },
	{ "AddStaticPickup", sAddStaticPickup, METH_VARARGS, "Adds a static pickup" },
	{ "AddStaticVehicle", sAddStaticVehicle, METH_VARARGS, "" },
	{ "AddStaticVehicleEx", sAddStaticVehicleEx, METH_VARARGS, "" },
	{ "AddVehicleComponent", sAddVehicleComponent, METH_VARARGS, "Adds a vehicle component" },
	{ "AllowAdminTeleport", sAllowAdminTeleport, METH_VARARGS, "" },
	{ "AllowInteriorWeapons", sAllowInteriorWeapons, METH_VARARGS, "Allows to use weapons in interiors" },
	{ "AllowPlayerTeleport", sAllowPlayerTeleport, METH_VARARGS, "" },
	{ "ApplyAnimation", sApplyAnimation, METH_VARARGS, "Applies an animation to a player" },
	{ "Attach3DTextLabelToPlayer", sAttach3DTextLabelToPlayer, METH_VARARGS, "" },
	{ "Attach3DTextLabelToVehicle", sAttach3DTextLabelToVehicle, METH_VARARGS, "" },
	{ "AttachCameraToObject", sAttachCameraToObject, METH_VARARGS, "" },
	{ "AttachCameraToPlayerObject", sAttachCameraToPlayerObject, METH_VARARGS, "" },
	{ "AttachObjectToObject", sAttachObjectToObject, METH_VARARGS, "" },
	{ "AttachObjectToPlayer", sAttachObjectToPlayer, METH_VARARGS, "" },
	{ "AttachObjectToVehicle", sAttachObjectToVehicle, METH_VARARGS, "" },
	{ "AttachPlayerObjectToPlayer", sAttachPlayerObjectToPlayer, METH_VARARGS, "" },
	{ "AttachPlayerObjectToVehicle", sAttachPlayerObjectToVehicle, METH_VARARGS, "" },
	{ "AttachTrailerToVehicle", sAttachTrailerToVehicle, METH_VARARGS, "" },

	{ "Ban", sBan, METH_VARARGS, "Bans a player" },
	{ "BanEx", sBanEx, METH_VARARGS, "Bans a player with a reason" },

	{ "CancelEdit", sCancelEdit, METH_VARARGS, "" },
	{ "CancelSelectTextDraw", sCancelSelectTextDraw, METH_VARARGS, "" },
	{ "ChangeVehicleColor", sChangeVehicleColor, METH_VARARGS, "Changes a vehicle's colors" },
	{ "ChangeVehiclePaintjob", sChangeVehiclePaintjob, METH_VARARGS, "Changes a vehicle's paintjob" },
	{ "ClearAnimations", sClearAnimations, METH_VARARGS, "Clears all animations for a player" },
	{ "ConnectNPC", sConnectNPC, METH_VARARGS, "Connects a NPC to the server" },
	{ "Create3DTextLabel", sCreate3DTextLabel, METH_VARARGS, "" },
	{ "CreateExplosion", sCreateExplosion, METH_VARARGS, "Creates an explosion" },
	{ "CreateMenu", sCreateMenu, METH_VARARGS, "" },
	{ "CreateObject", sCreateObject, METH_VARARGS, "Creates an object" },
	{ "CreatePickup", sCreatePickup, METH_VARARGS, "Creates a pickup" },
	{ "CreatePlayer3DTextLabel", sCreatePlayer3DTextLabel, METH_VARARGS, "" },
	{ "CreatePlayerObject", sCreatePlayerObject, METH_VARARGS, "Creates a player object" },
	{ "CreateVehicle", sCreateVehicle, METH_VARARGS, "Creates a vehicle" },

	{ "Delete3DTextLabel", sDelete3DTextLabel, METH_VARARGS, "Deletes a 3D text label" },
	{ "DeletePlayer3DTextLabel", sDeletePlayer3DTextLabel, METH_VARARGS, "Deletes a player 3D text label" },
	{ "DestroyMenu", sDestroyMenu, METH_VARARGS, "Destroys a menu" },
	{ "DestroyObject", sDestroyObject, METH_VARARGS, "Destroys an object" },
	{ "DestroyPickup", sDestroyPickup, METH_VARARGS, "Destroys a pickup" },
	{ "DestroyPlayerObject", sDestroyPlayerObject, METH_VARARGS, "Destroys a player object" },
	{ "DestroyVehicle", sDestroyVehicle, METH_VARARGS, "Destroys a vehicle" },
	{ "DetachTrailerFromVehicle", sDetachTrailerFromVehicle, METH_VARARGS, "Detaches a trailer from a vehicle" },
	{ "DisableInteriorEnterExits", sDisableInteriorEnterExits, METH_VARARGS, "Disables interior entrances" },
	{ "DisableMenu", sDisableMenu, METH_VARARGS, "Disables a menu" },
	{ "DisableMenuRow", sDisableMenuRow, METH_VARARGS, "Disables a menu row" },
	{ "DisableNameTagLOS", sDisableNameTagLOS, METH_VARARGS, "Disables name tag line of sight" },
	{ "DisablePlayerCheckpoint", sDisablePlayerCheckpoint, METH_VARARGS, "Disables a player's checkpoint" },
	{ "DisablePlayerRaceCheckpoint", sDisablePlayerRaceCheckpoint, METH_VARARGS, "Disables a player's race checkpoint" },

	{ "EditObject", sEditObject, METH_VARARGS, "" },
	{ "EditPlayerObject", sEditPlayerObject, METH_VARARGS, "" },
	{ "EditAttachedObject", sEditAttachedObject, METH_VARARGS, "" },
	{ "EnableStuntBonusForAll", sEnableStuntBonusForAll, METH_VARARGS, "Enables/disables stunt bonus for everyone" },
	{ "EnableStuntBonusForPlayer", sEnableStuntBonusForPlayer, METH_VARARGS, "Enables/disables stunt bonus for a player" },
	{ "ForeClassSelection", sForceClassSelection, METH_VARARGS, "Forces a player to the class selection after the next death" },

	{ "GameModeExit", sGameModeExit, METH_VARARGS, "Exits the current gamemode" },
	{ "GameTextForAll", sGameTextForAll, METH_VARARGS, "Sends a game text for everyone" },
	{ "GameTextForPlayer", sGameTextForPlayer, METH_VARARGS, "Sends a game text for a player" },
	{ "GangZoneCreate", sGangZoneCreate, METH_VARARGS, "Creates a gang zone" },
	{ "GangZoneDestroy", sGangZoneDestroy, METH_VARARGS, "Destroys a gang zone" },
	{ "GangZoneFlashForAll", sGangZoneFlashForAll, METH_VARARGS, "Flashes a gang zone for everyone" },
	{ "GangZoneFlashForPlayer", sGangZoneFlashForPlayer, METH_VARARGS, "Flashes a gang zone for a player" },
	{ "GangZoneHideForAll", sGangZoneHideForAll, METH_VARARGS, "Hides a gang zone for everyone" },
	{ "GangZoneHideForPlayer", sGangZoneHideForPlayer, METH_VARARGS, "Hides a gang zone for a player" },
	{ "GangZoneShowForAll", sGangZoneShowForAll, METH_VARARGS, "Shows a gang zone for everyone" },
	{ "GangZoneShowForPlayer", sGangZoneShowForPlayer, METH_VARARGS, "Shows a gang zone for a player" },
	{ "GangZoneStopFlashForAll", sGangZoneStopFlashForAll, METH_VARARGS, "Stops flashing a gang zone for everyone" },
	{ "GangZoneStopFlashForPlayer", sGangZoneStopFlashForPlayer, METH_VARARGS, "Stops flashing a gang zone for a player" },
	{ "GetAnimationName", sGetAnimationName, METH_VARARGS, "Returns the name of an animation" },
	{ "GetMaxPlayers", sGetMaxPlayers, METH_VARARGS, "Gets the max player value." },
	{ "GetNetworkStats", sGetNetworkStats, METH_VARARGS, "" },
	{ "GetObjectPos", sGetObjectPos, METH_VARARGS, "Gets an object's position" },
	{ "GetObjectRot", sGetObjectRot, METH_VARARGS, "Gets an object's rotation" },
	{ "GetPlayerAmmo", sGetPlayerAmmo, METH_VARARGS, "Gets a player's current amount of ammo" },
	{ "GetPlayerAnimationIndex", sGetPlayerAnimationIndex, METH_VARARGS, "Gets a player's animation index of an animation currently running" },
	{ "GetPlayerArmour", sGetPlayerArmour, METH_VARARGS, "Gets a player's armour" },
	{ "GetPlayerCameraFrontVector", sGetPlayerCameraFrontVector, METH_VARARGS, "Gets a relative position to the camera position of the player's aiming" },
	{ "GetPlayerCameraMode", sGetPlayerCameraMode, METH_VARARGS, "" },
	{ "GetPlayerCameraPos", sGetPlayerCameraPos, METH_VARARGS, "Gets the current camera position of a player" },
	{ "GetPlayerColor", sGetPlayerColor, METH_VARARGS, "Gets a player's color" },
	{ "GetPlayerDistanceFromPoint", sGetPlayerDistanceFromPoint, METH_VARARGS, "" },
	{ "GetPlayerDrunkLevel", sGetPlayerDrunkLevel, METH_VARARGS, "Gets a player's current drunk level" },
	{ "GetPlayerFacingAngle", sGetPlayerFacingAngle, METH_VARARGS, "Gets a player's current facing angle" },
	{ "GetPlayerFightingStyle", sGetPlayerFightingStyle, METH_VARARGS, "Gets a player's current fighting style" },
	{ "GetPlayerHealth", sGetPlayerHealth, METH_VARARGS, "Gets a player's current health" },
	{ "GetPlayerInterior", sGetPlayerInterior, METH_VARARGS, "Gets a player's current interior" },
	{ "GetPlayerIp", sGetPlayerIp, METH_VARARGS, "Gets a player's ip" },
	{ "GetPlayerKeys", sGetPlayerKeys, METH_VARARGS, "Gets keys currently pressed by a player" },
	{ "GetPlayerMenu", sGetPlayerMenu, METH_VARARGS, "Gets a player's current menu" },
	{ "GetPlayerMoney", sGetPlayerMoney, METH_VARARGS, "Gets a player's current amount of money" },
	{ "GetPlayerName", sGetPlayerName, METH_VARARGS, "Gets a player's name" },
	{ "GetPlayerNetworkStats", sGetPlayerNetworkStats, METH_VARARGS, "" },
	{ "GetPlayerObjectPos", sGetPlayerObjectPos, METH_VARARGS, "Gets a player object's position" },
	{ "GetPlayerObjectRot", sGetPlayerObjectRot, METH_VARARGS, "Gets a player object's rotation" },
	{ "GetPlayerPing", sGetPlayerPing, METH_VARARGS, "Gets a player's current ping" },
	{ "GetPlayerPos", sGetPlayerPos, METH_VARARGS, "Gets a player's position" },
	{ "GetPlayerScore", sGetPlayerScore, METH_VARARGS, "" },
	{ "GetPlayerSkin", sGetPlayerSkin, METH_VARARGS, "" },
	{ "GetPlayerSpecialAction", sGetPlayerSpecialAction, METH_VARARGS, "" },
	{ "GetPlayerState", sGetPlayerState, METH_VARARGS, "" },
	{ "GetPlayerSurfingObjectID", sGetPlayerSurfingObjectID, METH_VARARGS, "" },
	{ "GetPlayerSurfingVehicleID", sGetPlayerSurfingVehicleID, METH_VARARGS, "" },
	{ "GetPlayerTargetPlayer", sGetPlayerTargetPlayer, METH_VARARGS, "" },
	{ "GetPlayerTeam", sGetPlayerTeam, METH_VARARGS, "" },
	{ "GetPlayerTime", sGetPlayerTime, METH_VARARGS, "" },
	{ "GetPlayerVehicleID", sGetPlayerVehicleID, METH_VARARGS, "" },
	{ "GetPlayerVehicleSeat", sGetPlayerVehicleSeat, METH_VARARGS, "" },
	{ "GetPlayerVelocity", sGetPlayerVelocity, METH_VARARGS, "" },
	{ "GetPlayerVersion", sGetPlayerVersion, METH_VARARGS, "" },
	{ "GetPlayerVirtualWorld", sGetPlayerVirtualWorld, METH_VARARGS, "" },
	{ "GetPlayerWantedLevel", sGetPlayerWantedLevel, METH_VARARGS, "" },
	{ "GetPlayerWeapon", sGetPlayerWeapon, METH_VARARGS, "" },
	{ "GetPlayerWeaponData", sGetPlayerWeaponData, METH_VARARGS, "" },
	{ "GetPlayerWeaponState", sGetPlayerWeaponState, METH_VARARGS, "" },
	{ "GetTickCount", sGetTickCount, METH_VARARGS, "" },
	{ "GetVehicleComponentInSlot", sGetVehicleComponentInSlot, METH_VARARGS, "" },
	{ "GetVehicleComponentType", sGetVehicleComponentType, METH_VARARGS, "" },
	{ "GetVehicleDamageStatus", sGetVehicleDamageStatus, METH_VARARGS, "" },
	{ "GetVehicleDistanceFromPoint", sGetVehicleDistanceFromPoint, METH_VARARGS, "" },
	{ "GetVehicleHealth", sGetVehicleHealth, METH_VARARGS, "" },
	{ "GetVehicleModel", sGetVehicleModel, METH_VARARGS, "" },
	{ "GetVehicleModelInfo", sGetVehicleModelInfo, METH_VARARGS, "" },
	{ "GetVehiclePos", sGetVehiclePos, METH_VARARGS, "" },
	{ "GetVehicleRotationQuat", sGetVehicleRotationQuat, METH_VARARGS, "" },
	{ "GetVehicleTrailer", sGetVehicleTrailer, METH_VARARGS, "" },
	{ "GetVehicleVelocity", sGetVehicleVelocity, METH_VARARGS, "" },
	{ "GetVehicleVirtualWorld", sGetVehicleVirtualWorld, METH_VARARGS, "" },
	{ "GetVehicleZAngle", sGetVehicleZAngle, METH_VARARGS, "" },
	{ "GetWeaponName", sGetWeaponName, METH_VARARGS, "" },
	{ "GivePlayerMoney", sGivePlayerMoney, METH_VARARGS, "" },
	{ "GivePlayerWeapon", sGivePlayerWeapon, METH_VARARGS, "" },

	{ "HideMenuForPlayer", sHideMenuForPlayer, METH_VARARGS, "" },

	{ "InterpolateCameraPos", sInterpolateCameraPos, METH_VARARGS, "" },
	{ "InterpolateCameraLookAt", sInterpolateCameraLookAt, METH_VARARGS, "" },
	{ "IsObjectMoving", sIsObjectMoving, METH_VARARGS, "" },
	{ "IsPlayerAdmin", sIsPlayerAdmin, METH_VARARGS, "" },
	{ "IsPlayerAttachedObjectSlotUsed", sIsPlayerAttachedObjectSlotUsed, METH_VARARGS, "" },
	{ "IsPlayerConnected", sIsPlayerConnected, METH_VARARGS, "" },
	{ "IsPlayerHoldingObject", sIsPlayerHoldingObject, METH_VARARGS, "" },
	{ "IsPlayerInAnyVehicle", sIsPlayerInAnyVehicle, METH_VARARGS, "" },
	{ "IsPlayerInCheckpoint", sIsPlayerInCheckpoint, METH_VARARGS, "" },
	{ "IsPlayerInRaceCheckpoint", sIsPlayerInRaceCheckpoint, METH_VARARGS, "" },
	{ "IsPlayerInRangeOfPoint", sIsPlayerInRangeOfPoint, METH_VARARGS, "" },
	{ "IsPlayerInVehicle", sIsPlayerInVehicle, METH_VARARGS, "" },
	{ "IsPlayerNPC", sIsPlayerNPC, METH_VARARGS, "" },
	{ "IsPlayerObjectMoving", sIsPlayerObjectMoving, METH_VARARGS, "" },
	{ "IsPlayerStreamedIn", sIsPlayerStreamedIn, METH_VARARGS, "" },
	{ "IsTrailerAttachedToVehicle", sIsTrailerAttachedToVehicle, METH_VARARGS, "" },
	{ "IsValidMenu", sIsValidMenu, METH_VARARGS, "" },
	{ "IsValidObject", sIsValidObject, METH_VARARGS, "" },
	{ "IsValidPlayerObject", sIsValidPlayerObject, METH_VARARGS, "" },
	{ "IsVehicleStreamedIn", sIsVehicleStreamedIn, METH_VARARGS, "" },

	{ "Kick", sKick, METH_VARARGS, "Kick a specified player from the server" },
	{ "KillTimer", sKillTimer, METH_VARARGS, "Kills a timer" },

	{ "LimitGlobalChatRadius", sLimitGlobalChatRadius, METH_VARARGS, "" },
	{ "LimitPlayerMarkerRadius", sLimitPlayerMarkerRadius, METH_VARARGS, "" },
	{ "LinkVehicleToInterior", sLinkVehicleToInterior, METH_VARARGS, "" },

	{ "ManualVehicleEngineAndLights", sManualVehicleEngineAndLights, METH_VARARGS, "" },
	{ "MoveObject", sMoveObject, METH_VARARGS, "" },
	{ "MovePlayerObject", sMovePlayerObject, METH_VARARGS, "" },

	{ "PlayAudioStreamForPlayer", sPlayAudioStreamForPlayer, METH_VARARGS, "" },
	{ "PlayCrimeReportForPlayer", sPlayCrimeReportForPlayer, METH_VARARGS, "" },
	{ "PlayerPlaySound", sPlayerPlaySound, METH_VARARGS, "" },
	{ "PlayerSpectatePlayer", sPlayerSpectatePlayer, METH_VARARGS, "" },
	{ "PlayerSpectateVehicle", sPlayerSpectateVehicle, METH_VARARGS, "" },
	{ "PutPlayerInVehicle", sPutPlayerInVehicle, METH_VARARGS, "" },

	{ "CreatePlayerTextDraw", sCreatePlayerTextDraw, METH_VARARGS, "" },
	{ "PlayerTextDrawDestroy", sPlayerTextDrawDestroy, METH_VARARGS, "" },
	{ "PlayerTextDrawLetterSize", sPlayerTextDrawLetterSize, METH_VARARGS, "" },
	{ "PlayerTextDrawTextSize", sPlayerTextDrawTextSize, METH_VARARGS, "" },
	{ "PlayerTextDrawAlignment", sPlayerTextDrawAlignment, METH_VARARGS, "" },
	{ "PlayerTextDrawColor", sPlayerTextDrawColor, METH_VARARGS, "" },
	{ "PlayerTextDrawUseBox", sPlayerTextDrawUseBox, METH_VARARGS, "" },
	{ "PlayerTextDrawBoxColor", sPlayerTextDrawBoxColor, METH_VARARGS, "" },
	{ "PlayerTextDrawSetShadow", sPlayerTextDrawSetShadow, METH_VARARGS, "" },
	{ "PlayerTextDrawSetOutline", sPlayerTextDrawSetOutline, METH_VARARGS, "" },
	{ "PlayerTextDrawBackgroundColor", sPlayerTextDrawBackgroundColor, METH_VARARGS, "" },
	{ "PlayerTextDrawFont", sPlayerTextDrawFont, METH_VARARGS, "" },
	{ "PlayerTextDrawSetProportional", sPlayerTextDrawSetProportional, METH_VARARGS, "" },
	{ "PlayerTextDrawSetSelectable", sPlayerTextDrawSetSelectable, METH_VARARGS, "" },
	{ "PlayerTextDrawShow", sPlayerTextDrawShow, METH_VARARGS, "" },
	{ "PlayerTextDrawHide", sPlayerTextDrawHide, METH_VARARGS, "" },
	{ "PlayerTextDrawSetString", sPlayerTextDrawSetString, METH_VARARGS, "" },

	{ "RemoveBuildingForPlayer", sRemoveBuildingForPlayer, METH_VARARGS, "" },
	{ "RemovePlayerAttachedObject", sRemovePlayerAttachedObject, METH_VARARGS, "" },
	{ "RemovePlayerFromVehicle", sRemovePlayerFromVehicle, METH_VARARGS, "" },
	{ "RemovePlayerMapIcon", sRemovePlayerMapIcon, METH_VARARGS, "" },
	{ "RemoveVehicleComponent", sRemoveVehicleComponent, METH_VARARGS, "" },
	{ "RepairVehicle", sRepairVehicle, METH_VARARGS, "" },
	{ "ResetPlayerMoney", sResetPlayerMoney, METH_VARARGS, "" },
	{ "ResetPlayerWeapons", sResetPlayerWeapons, METH_VARARGS, "" },

	{ "SelectObject", sSelectObject, METH_VARARGS, "" },
	{ "SelectTextDraw", sSelectTextDraw, METH_VARARGS, "" },
	{ "SendClientMessage", sSendClientMessage, METH_VARARGS, "Sends a message to a player" },
	{ "SendClientMessageToAll", sSendClientMessageToAll, METH_VARARGS, "" },
	{ "SendDeathMessage", sSendDeathMessage, METH_VARARGS, "" },
	{ "SendPlayerMessageToAll", sSendPlayerMessageToAll, METH_VARARGS, "" },
	{ "SendPlayerMessageToPlayer", sSendPlayerMessageToPlayer, METH_VARARGS, "" },
	{ "SendRconCommand", sSendRconCommand, METH_VARARGS, "" },
	{ "SetCameraBehindPlayer", sSetCameraBehindPlayer, METH_VARARGS, "" },
	{ "SetGameModeText", sSetGameModeText, METH_VARARGS, "Sets the gamemode text" },
	{ "SetGravity", sSetGravity, METH_VARARGS, "Sets the gravity on the server" },
	{ "SetMenuColumnHeader", sSetMenuColumnHeader, METH_VARARGS, "" },
	{ "SetNameTagDrawDistance", sSetNameTagDrawDistance, METH_VARARGS, "" },
	{ "SetObjectMaterial", sSetObjectMaterial, METH_VARARGS, "" },
	{ "SetObjectMaterialText", sSetObjectMaterialText, METH_VARARGS, "" },
	{ "SetObjectPos", sSetObjectPos, METH_VARARGS, "" },
	{ "SetObjectRot", sSetObjectRot, METH_VARARGS, "" },
	{ "SetPlayerAmmo", sSetPlayerAmmo, METH_VARARGS, "" },
	{ "SetPlayerArmedWeapon", sSetPlayerArmedWeapon, METH_VARARGS, "" },
	{ "SetPlayerArmour", sSetPlayerArmour, METH_VARARGS, "" },
	{ "SetPlayerAttachedObject", sSetPlayerAttachedObject, METH_VARARGS, "" },
	{ "SetPlayerCameraLookAt", sSetPlayerCameraLookAt, METH_VARARGS, "" },
	{ "SetPlayerCameraPos", sSetPlayerCameraPos, METH_VARARGS, "" },
	{ "SetPlayerChatBubble", sSetPlayerChatBubble, METH_VARARGS, "" },
	{ "SetPlayerCheckpoint", sSetPlayerCheckpoint, METH_VARARGS, "" },
	{ "SetPlayerColor", sSetPlayerColor, METH_VARARGS, "" },
	{ "SetPlayerDrunkLevel", sSetPlayerDrunkLevel, METH_VARARGS, "" },
	{ "SetPlayerFacingAngle", sSetPlayerFacingAngle, METH_VARARGS, "" },
	{ "SetPlayerFightingStyle", sSetPlayerFightingStyle, METH_VARARGS, "" },
	{ "SetPlayerHealth", sSetPlayerHealth, METH_VARARGS, "" },
	{ "SetPlayerHoldingObject", sSetPlayerHoldingObject, METH_VARARGS, "" },
	{ "SetPlayerInterior", sSetPlayerInterior, METH_VARARGS, "" },
	{ "SetPlayerMapIcon", sSetPlayerMapIcon, METH_VARARGS, "" },
	{ "SetPlayerMarkerForPlayer", sSetPlayerMarkerForPlayer, METH_VARARGS, "" },
	{ "SetPlayerName", sSetPlayerName, METH_VARARGS, "" },
	{ "SetPlayerObjectMaterial", sSetPlayerObjectMaterial, METH_VARARGS, "" },
	{ "SetPlayerObjectMaterialText", sSetPlayerObjectMaterialText, METH_VARARGS, "" },
	{ "SetPlayerObjectPos", sSetPlayerObjectPos, METH_VARARGS, "" },
	{ "SetPlayerObjectRot", sSetPlayerObjectRot, METH_VARARGS, "" },
	{ "SetPlayerPos", sSetPlayerPos, METH_VARARGS, "" },
	{ "SetPlayerPosFindZ", sSetPlayerPosFindZ, METH_VARARGS, "" },
	{ "SetPlayerRaceCheckpoint", sSetPlayerRaceCheckpoint, METH_VARARGS, "" },
	{ "SetPlayerScore", sSetPlayerScore, METH_VARARGS, "" },
	{ "SetPlayerShopName", sSetPlayerShopName, METH_VARARGS, "" },
	{ "SetPlayerSkillLevel", sSetPlayerSkillLevel, METH_VARARGS, "" },
	{ "SetPlayerSkin", sSetPlayerSkin, METH_VARARGS, "" },
	{ "SetPlayerSpecialAction", sSetPlayerSpecialAction, METH_VARARGS, "" },
	{ "SetPlayerTeam", sSetPlayerTeam, METH_VARARGS, "" },
	{ "SetPlayerTime", sSetPlayerTime, METH_VARARGS, "" },
	{ "SetPlayerVelocity", sSetPlayerVelocity, METH_VARARGS, "" },
	{ "SetPlayerVirtualWorld", sSetPlayerVirtualWorld, METH_VARARGS, "" },
	{ "SetPlayerWantedLevel", sSetPlayerWantedLevel, METH_VARARGS, "" },
	{ "SetPlayerWeather", sSetPlayerWeather, METH_VARARGS, "" },
	{ "SetPlayerWorldBounds", sSetPlayerWorldBounds, METH_VARARGS, "" },
	{ "SetSpawnInfo", sSetSpawnInfo, METH_VARARGS, "" },
	{ "SetTeamCount", sSetTeamCount, METH_VARARGS, "" },
	{ "SetTimer", sSetTimer, METH_VARARGS, "Sets a timer" },
	{ "SetVehicleAngularVelocity", sSetVehicleAngularVelocity, METH_VARARGS, "" },
	{ "SetVehicleHealth", sSetVehicleHealth, METH_VARARGS, "" },
	{ "SetVehicleNumberPlate", sSetVehicleNumberPlate, METH_VARARGS, "" },
	{ "SetVehicleParamsEx", sSetVehicleParamsEx, METH_VARARGS, "" },
	{ "SetVehicleParamsForPlayer", sSetVehicleParamsForPlayer, METH_VARARGS, "" },
	{ "SetVehiclePos", sSetVehiclePos, METH_VARARGS, "" },
	{ "SetVehicleToRespawn", sSetVehicleToRespawn, METH_VARARGS, "" },
	{ "SetVehicleVelocity", sSetVehicleVelocity, METH_VARARGS, "" },
	{ "SetVehicleVirtualWorld", sSetVehicleVirtualWorld, METH_VARARGS, "" },
	{ "SetVehicleZAngle", sSetVehicleZAngle, METH_VARARGS, "" },
	{ "SetWeather", sSetWeather, METH_VARARGS, "" },
	{ "SetWorldTime", sSetWorldTime, METH_VARARGS, "" },
	{ "ShowMenuForPlayer", sShowMenuForPlayer, METH_VARARGS, "" },
	{ "ShowNameTags", sShowNameTags, METH_VARARGS, "" },
	{ "ShowPlayerDialog", sShowPlayerDialog, METH_VARARGS, "" },
	{ "ShowPlayerMarkers", sShowPlayerMarkers, METH_VARARGS, "" },
	{ "ShowPlayerNameTagForPlayer", sShowPlayerNameTagForPlayer, METH_VARARGS, "" },
	{ "SpawnPlayer", sSpawnPlayer, METH_VARARGS, "" },
	{ "StartRecordingPlayerData", sStartRecordingPlayerData, METH_VARARGS, "" },
	{ "StopAudioStreamForPlayer", sStopAudioStreamForPlayer, METH_VARARGS, "" },
	{ "StopObject", sStopObject, METH_VARARGS, "" },
	{ "StopPlayerHoldingObject", sStopPlayerHoldingObject, METH_VARARGS, "" },
	{ "StopPlayerObject", sStopPlayerObject, METH_VARARGS, "" },
	{ "StopRecordingPlayerData", sStopRecordingPlayerData, METH_VARARGS, "" },

	{ "TextDrawAlignment", sTextDrawAlignment, METH_VARARGS, "" },
	{ "TextDrawBackgroundColor", sTextDrawBackgroundColor, METH_VARARGS, "" },
	{ "TextDrawBoxColor", sTextDrawBoxColor, METH_VARARGS, "" },
	{ "TextDrawColor", sTextDrawColor, METH_VARARGS, "" },
	{ "TextDrawCreate", sTextDrawCreate, METH_VARARGS, "" },
	{ "TextDrawDestroy", sTextDrawDestroy, METH_VARARGS, "" },
	{ "TextDrawFont", sTextDrawFont, METH_VARARGS, "" },
	{ "TextDrawHideForAll", sTextDrawHideForAll, METH_VARARGS, "" },
	{ "TextDrawHideForPlayer", sTextDrawHideForPlayer, METH_VARARGS, "" },
	{ "TextDrawLetterSize", sTextDrawLetterSize, METH_VARARGS, "" },
	{ "TextDrawSetOutline", sTextDrawSetOutline, METH_VARARGS, "" },
	{ "TextDrawSetProportional", sTextDrawSetProportional, METH_VARARGS, "" },
	{ "TextDrawSetSelectable", sTextDrawSetSelectable, METH_VARARGS, "" },
	{ "TextDrawSetShadow", sTextDrawSetShadow, METH_VARARGS, "" },
	{ "TextDrawSetString", sTextDrawSetString, METH_VARARGS, "" },
	{ "TextDrawShowForAll", sTextDrawShowForAll, METH_VARARGS, "" },
	{ "TextDrawShowForPlayer", sTextDrawShowForPlayer, METH_VARARGS, "" },
	{ "TextDrawTextSize", sTextDrawTextSize, METH_VARARGS, "" },
	{ "TextDrawUseBox", sTextDrawUseBox, METH_VARARGS, "" },
	{ "TogglePlayerClock", sTogglePlayerClock, METH_VARARGS, "" },
	{ "TogglePlayerControllable", sTogglePlayerControllable, METH_VARARGS, "" },
	{ "TogglePlayerSpectating", sTogglePlayerSpectating, METH_VARARGS, "" },

	{ "Update3DTextLabelText", sUpdate3DTextLabelText, METH_VARARGS, "" },
	{ "UpdatePlayer3DTextLabelText", sUpdatePlayer3DTextLabelText, METH_VARARGS, "" },
	{ "UpdateVehicleDamageStatus", sUpdateVehicleDamageStatus, METH_VARARGS, "" },
	{ "UsePlayerPedAnims", sUsePlayerPedAnims, METH_VARARGS, "" },

	// other functions
	// multithreading
	{ "InvokeFunction", sInvokeFunction, METH_VARARGS, "" },

	{ NULL, NULL, 0, NULL }
};

struct module_state
{
        PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
        #define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
        #define GETSTATE(m) (&_state)
        static struct module_state _state;
#endif

#if PY_MAJOR_VERSION >= 3

static int _pyModuleTraverse(PyObject *m, visitproc visit, void *arg)
{
        Py_VISIT(GETSTATE(m)->error);
        return 0;
}

static int _pyModuleClear(PyObject *m)
{
        Py_CLEAR(GETSTATE(m)->error);
        return 0;
}


static struct PyModuleDef pysamp_moduledef =
{
        PyModuleDef_HEAD_INIT,
        "samp",
        NULL,
        sizeof(struct module_state),
        _pySampMethods,
        NULL,
        _pyModuleTraverse,
        _pyModuleClear,
        NULL
};
#endif



std::deque<PyObject *> m_pyModule;
bool m_pyInited = false;


char *_pyGetString(PyObject *obj)
{
	char *retval = NULL;
	PyObject *strobj = PyObject_Str(obj);
#if PY_MAJOR_VERSION >= 3
	PyObject *unival = PyUnicode_AsUTF8String(strobj);
	if (unival)
	{
		retval = strdup(PyBytes_AsString(unival));
		Py_XDECREF(unival);
	}
#else
	retval = strdup(PyString_AsString(strobj));
#endif
	Py_DECREF(strobj);
	return retval;
}
void _pyLogError()
{
	// gets exception info and prints it out to the log
	PyObject *ptype, *pval, *traceback;

	PyErr_Fetch(&ptype, &pval, &traceback);
	PyErr_NormalizeException(&ptype, &pval, &traceback);

	PyTypeObject *type = (PyTypeObject*)ptype;
	// print exception type and (if available) text
	if (pval != NULL)
	{
		char *pvalstr = _pyGetString(pval);
		logprintf("%s: %s", type->tp_name, pvalstr);
		free(pvalstr);
	}
	else logprintf("%s", type->tp_name);

	// if available, print traceback
	if (traceback != NULL)
	{
		PyTracebackObject *tb = (PyTracebackObject*)traceback;
		// import linecache module, which will be used to get the code lines in the traceback
		PyObject *linecache = PyImport_ImportModule("linecache");
		if (linecache != NULL) // if this does not work, not even Python itself will be able to print exceptions
		{
			PyObject *lc_getline = PyObject_GetAttrString(linecache, "getline");
			if (lc_getline != NULL)
			{
				while (tb != NULL)
				{
					char *fname = _pyGetString(tb->tb_frame->f_code->co_filename), *name = _pyGetString(tb->tb_frame->f_code->co_name), *cline;;
					logprintf("    %s[%d] in %s", fname, tb->tb_lineno, name);
					// use getline to get the code line
					PyObject *codeline = PyObject_CallFunction(lc_getline, "OiO", tb->tb_frame->f_code->co_filename, tb->tb_lineno, tb->tb_frame->f_globals);
					cline = _pyGetString(codeline);
					logprintf("      %s", cline);
					Py_DECREF(codeline);
					free(fname); free(name); free(cline);
					tb = tb->tb_next;
				}
				Py_DECREF(lc_getline);
			}
			Py_DECREF(linecache);
		}
	}
	if (PyErr_Occurred() != NULL)
	{
		logprintf("PYTHON: WARNING: Exception occurred while trying to print exception information");
		PyErr_Clear();
	}

	Py_DECREF(ptype); Py_XDECREF(pval); Py_XDECREF(traceback);
}

PyObject *_pyCallObject(PyObject *func, PyObject *params)
{
	PyErr_Clear();
	PyObject *ret = PyObject_CallObject(func, params);
	if (PyErr_Occurred() != NULL) _pyLogError(); //PyErr_Print();
	return ret;
}
PyObject *_pyCallFunc(PyObject *module, const char *funcname, PyObject *args)
{
	PyObject *func = NULL, *ret = NULL;

	func = PyObject_GetAttrString(module, funcname);
	if (func == NULL) return NULL;
	// call the function and return the result
	ret = _pyCallObject(func, args);
	// free the function object
	Py_DECREF(func);

	return ret;
}
cell _pyCallAll(const char *funcname, PyObject *args, int nondefval, int defval)
{
	PyObject *val = PyLong_FromLong(nondefval); // if one module returns this value, return this
	PyObject *boolval = PyBool_FromLong(nondefval);
	bool ret_val = false;
	for (std::deque<PyObject*>::iterator i = m_pyModule.begin(); i != m_pyModule.end(); i++)
	{
		PyObject *r = _pyCallFunc(*i, funcname, args);
		PyErr_Clear(); // this can be set by PyObject_GetAttrString in _pyCallFunc, but we want to ignore it
		if (r == val || r == boolval) ret_val = true;
		Py_XDECREF(r);
	}
	Py_DECREF(val); Py_DECREF(boolval);
	// DEBUG
	/*if (funcname[8] != 'U') // avoid OnPlayerUpdate
		logprintf("PYTHON: callback %s return value %d", funcname, (ret_val ? nondefval : defval));*/
	// END DEBUG
	return (ret_val ? nondefval : defval);
}

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_samp()
{
	PyObject *samp_mod = PyModule_Create(&pysamp_moduledef);
	_pyInitMacros(samp_mod);
	return samp_mod;
}
#endif

#if ENABLE_MULTITHREAD
	THREAD_RETURN _pyInit(void *prm)
#else
	void _pyInit()
#endif
{
	// prevent other thread to continue until Python is completely initialized
	m_MainLock->Lock();

	PyImport_AppendInittab("samp", PyInit_samp);
	Py_Initialize();
	PyEval_InitThreads();
	m_pyInited = true;

	// init samp modules
#if PY_MAJOR_VERSION < 3
	PyObject *samp_mod = Py_InitModule("samp", _pySampMethods);
	_pyInitMacros(samp_mod);
#endif

	// add the current directory to the module import paths
	//	char *curpath = Py_GetPath();
	//	int slen = strlen(curpath);
	//	char *newpath = (char*)malloc(slen + 5);
	//	memcpy(newpath, curpath, slen);
	//#ifdef WIN32
	//	strncpy(newpath + slen, ";.", 3);
	//#else
	//	strncpy(newpath + slen, ":.", 3);
	//#endif
	//	PySys_SetPath(newpath);
	//	free(newpath);
	
	// sys.path was overwritten (the paths added by site.py) with the previous code, so use the following:
	PyRun_SimpleString("import sys; sys.path.append('./gamemodes')");

	m_MainLock->Unlock();
#if ENABLE_MULTITHREAD
	// run a main loop; this thread still holds the GIL
	// this creates a new event in the samp module and waits for it to be set
	PyRun_SimpleString("import threading, samp\nsamp.exit_listener = threading.Event()\nsamp.exit_listener.wait()");
	_pyExit();
	return 0;
#endif
}
int _pyLoadModule(char *pyscript)
{
	PyObject *mod = PyImport_ImportModule(pyscript);
	if (!mod)
	{
		logprintf("PYTHON: Init: ERROR loading module %s:", pyscript);
		// could not load the module; print the exception to stderr
		if (PyErr_Occurred() != NULL)
		{
			// we have an exception -> print it
			_pyLogError(); // PyErr_Print();
			// DONE: use logprintf to print the exception
		}
		else
		{
			// an unkown error
			logprintf("PYTHON: Init: Unkown error loading module %s", pyscript);
		}
		return 0;
	}
	m_pyModule.push_back(mod);
	//_pyInitMacros(mod);
	// call the init function in the python script (if available)
	PyObject *o = _pyCallFunc(mod, "OnPyInit");
	Py_XDECREF(o);

	return 1;
}

void _pyExit()
{
	if (m_pyInited)
	{
		m_MainLock->Lock();
		for (std::deque<PyObject*>::iterator i = m_pyModule.begin(); i != m_pyModule.end(); i++)
		{
			Py_DECREF(*i);
		}
		m_pyModule.clear();

		// clear timer data
		for (std::deque<timer_data>::iterator i = m_TimerList.begin(); i != m_TimerList.end(); i++)
		{
			clearTimerData(i);
		}
		m_TimerList.clear();

		while (!m_InvokeQueue.empty())
		{
			invoke_data tmp = m_InvokeQueue.front();
			Py_DECREF(tmp.func);
			Py_XDECREF(tmp.params);
			m_InvokeQueue.pop();
		}
		m_MainLock->Unlock();

		Py_Finalize();

		m_pyInited = false;
	}
}

void _pyInitMacros(PyObject *module)
{
	PyModule_AddIntMacro(module, MAX_PLAYER_NAME);
	PyModule_AddIntMacro(module, MAX_PLAYERS);
	PyModule_AddIntMacro(module, MAX_VEHICLES);
	PyModule_AddIntMacro(module, INVALID_PLAYER_ID);
	PyModule_AddIntMacro(module, INVALID_VEHICLE_ID);
	PyModule_AddIntMacro(module, NO_TEAM);
	PyModule_AddIntMacro(module, MAX_OBJECTS);
	PyModule_AddIntMacro(module, INVALID_OBJECT_ID);
	PyModule_AddIntMacro(module, MAX_GANG_ZONES);
	PyModule_AddIntMacro(module, MAX_TEXT_DRAWS);
	PyModule_AddIntMacro(module, MAX_PLAYER_TEXT_DRAWS);
	PyModule_AddIntMacro(module, MAX_MENUS);
	PyModule_AddIntMacro(module, MAX_3DTEXT_GLOBAL);
	PyModule_AddIntMacro(module, MAX_3DTEXT_PLAYER);
	PyModule_AddIntMacro(module, MAX_PICKUPS);
	PyModule_AddIntMacro(module, INVALID_MENU);
	PyModule_AddIntMacro(module, INVALID_TEXT_DRAW);
	PyModule_AddIntMacro(module, INVALID_GANG_ZONE);
	PyModule_AddIntMacro(module, INVALID_3DTEXT_ID);

	PyModule_AddIntMacro(module, DIALOG_STYLE_INPUT);
	PyModule_AddIntMacro(module, DIALOG_STYLE_LIST);
	PyModule_AddIntMacro(module, DIALOG_STYLE_MSGBOX);
	PyModule_AddIntMacro(module, DIALOG_STYLE_PASSWORD);
	
	PyModule_AddIntMacro(module, PLAYER_STATE_NONE);
	PyModule_AddIntMacro(module, PLAYER_STATE_ONFOOT);
	PyModule_AddIntMacro(module, PLAYER_STATE_DRIVER);
	PyModule_AddIntMacro(module, PLAYER_STATE_PASSENGER);
	PyModule_AddIntMacro(module, PLAYER_STATE_EXIT_VEHICLE);
	PyModule_AddIntMacro(module, PLAYER_STATE_ENTER_VEHICLE_DRIVER);
	PyModule_AddIntMacro(module, PLAYER_STATE_ENTER_VEHICLE_PASSENGER);
	PyModule_AddIntMacro(module, PLAYER_STATE_WASTED);
	PyModule_AddIntMacro(module, PLAYER_STATE_SPAWNED);
	PyModule_AddIntMacro(module, PLAYER_STATE_SPECTATING);
	
	PyModule_AddIntMacro(module, PLAYER_MARKERS_MODE_OFF);
	PyModule_AddIntMacro(module, PLAYER_MARKERS_MODE_GLOBAL);
	PyModule_AddIntMacro(module, PLAYER_MARKERS_MODE_STREAMED);
	
	PyModule_AddIntMacro(module, WEAPON_BRASSKNUCKLE);
	PyModule_AddIntMacro(module, WEAPON_GOLFCLUB);
	PyModule_AddIntMacro(module, WEAPON_NITESTICK);
	PyModule_AddIntMacro(module, WEAPON_KNIFE);
	PyModule_AddIntMacro(module, WEAPON_BAT);
	PyModule_AddIntMacro(module, WEAPON_SHOVEL);
	PyModule_AddIntMacro(module, WEAPON_POOLSTICK);
	PyModule_AddIntMacro(module, WEAPON_KATANA);
	PyModule_AddIntMacro(module, WEAPON_CHAINSAW);
	PyModule_AddIntMacro(module, WEAPON_DILDO);
	PyModule_AddIntMacro(module, WEAPON_DILDO2);
	PyModule_AddIntMacro(module, WEAPON_VIBRATOR);
	PyModule_AddIntMacro(module, WEAPON_VIBRATOR2);
	PyModule_AddIntMacro(module, WEAPON_FLOWER);
	PyModule_AddIntMacro(module, WEAPON_CANE);
	PyModule_AddIntMacro(module, WEAPON_GRENADE);
	PyModule_AddIntMacro(module, WEAPON_TEARGAS);
	PyModule_AddIntMacro(module, WEAPON_MOLTOV);
	PyModule_AddIntMacro(module, WEAPON_COLT45);
	PyModule_AddIntMacro(module, WEAPON_SILENCED);
	PyModule_AddIntMacro(module, WEAPON_DEAGLE);
	PyModule_AddIntMacro(module, WEAPON_SHOTGUN);
	PyModule_AddIntMacro(module, WEAPON_SAWEDOFF);
	PyModule_AddIntMacro(module, WEAPON_SHOTGSPA);
	PyModule_AddIntMacro(module, WEAPON_UZI);
	PyModule_AddIntMacro(module, WEAPON_MP5);
	PyModule_AddIntMacro(module, WEAPON_AK47);
	PyModule_AddIntMacro(module, WEAPON_M4);
	PyModule_AddIntMacro(module, WEAPON_TEC9);
	PyModule_AddIntMacro(module, WEAPON_RIFLE);
	PyModule_AddIntMacro(module, WEAPON_SNIPER);
	PyModule_AddIntMacro(module, WEAPON_ROCKETLAUNCHER);
	PyModule_AddIntMacro(module, WEAPON_HEATSEEKER);
	PyModule_AddIntMacro(module, WEAPON_FLAMETHROWER);
	PyModule_AddIntMacro(module, WEAPON_MINIGUN);
	PyModule_AddIntMacro(module, WEAPON_SATCHEL);
	PyModule_AddIntMacro(module, WEAPON_BOMB);
	PyModule_AddIntMacro(module, WEAPON_SPRAYCAN);
	PyModule_AddIntMacro(module, WEAPON_FIREEXTINGUISHER);
	PyModule_AddIntMacro(module, WEAPON_CAMERA);
	PyModule_AddIntMacro(module, WEAPON_PARACHUTE);
	PyModule_AddIntMacro(module, WEAPON_VEHICLE);
	PyModule_AddIntMacro(module, WEAPON_DROWN);
	PyModule_AddIntMacro(module, WEAPON_COLLISION);
	
	PyModule_AddIntMacro(module, KEY_ACTION);
	PyModule_AddIntMacro(module, KEY_CROUCH);
	PyModule_AddIntMacro(module, KEY_FIRE);
	PyModule_AddIntMacro(module, KEY_SPRINT);
	PyModule_AddIntMacro(module, KEY_SECONDARY_ATTACK);
	PyModule_AddIntMacro(module, KEY_JUMP);
	PyModule_AddIntMacro(module, KEY_LOOK_RIGHT);
	PyModule_AddIntMacro(module, KEY_HANDBRAKE);
	PyModule_AddIntMacro(module, KEY_LOOK_LEFT);
	PyModule_AddIntMacro(module, KEY_SUBMISSION);
	PyModule_AddIntMacro(module, KEY_LOOK_BEHIND);
	PyModule_AddIntMacro(module, KEY_WALK);
	PyModule_AddIntMacro(module, KEY_ANALOG_UP);
	PyModule_AddIntMacro(module, KEY_ANALOG_DOWN);
	PyModule_AddIntMacro(module, KEY_ANALOG_LEFT);
	PyModule_AddIntMacro(module, KEY_ANALOG_RIGHT);
	PyModule_AddIntMacro(module, KEY_YES);
	PyModule_AddIntMacro(module, KEY_NO);
	PyModule_AddIntMacro(module, KEY_CTRL_BACK);
	
	PyModule_AddIntMacro(module, KEY_UP);
	PyModule_AddIntMacro(module, KEY_DOWN);
	PyModule_AddIntMacro(module, KEY_LEFT);
	PyModule_AddIntMacro(module, KEY_RIGHT);
	
	PyModule_AddIntMacro(module, CLICK_SOURCE_SCOREBOARD);

	PyModule_AddIntMacro(module, EDIT_RESPONSE_CANCEL);
	PyModule_AddIntMacro(module, EDIT_RESPONSE_FINAL);
	PyModule_AddIntMacro(module, EDIT_RESPONSE_UPDATE);

	PyModule_AddIntMacro(module, SELECT_OBJECT_GLOBAL_OBJECT);
	PyModule_AddIntMacro(module, SELECT_OBJECT_PLAYER_OBJECT);
	
	
	PyModule_AddIntMacro(module, SPECIAL_ACTION_NONE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DUCK);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_USEJETPACK);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_ENTER_VEHICLE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_EXIT_VEHICLE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DANCE1);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DANCE2);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DANCE3);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DANCE4);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_HANDSUP);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_USECELLPHONE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_SITTING);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_STOPUSECELLPHONE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DRINK_BEER);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_SMOKE_CIGGY);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DRINK_WINE);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_DRINK_SPRUNK);
	PyModule_AddIntMacro(module, SPECIAL_ACTION_CUFFED);

	PyModule_AddIntMacro(module, CAMERA_CUT);
	PyModule_AddIntMacro(module, CAMERA_MOVE);
	
	PyModule_AddIntMacro(module, FIGHT_STYLE_NORMAL);
	PyModule_AddIntMacro(module, FIGHT_STYLE_BOXING);
	PyModule_AddIntMacro(module, FIGHT_STYLE_KUNGFU);
	PyModule_AddIntMacro(module, FIGHT_STYLE_KNEEHEAD);
	PyModule_AddIntMacro(module, FIGHT_STYLE_GRABKICK);
	PyModule_AddIntMacro(module, FIGHT_STYLE_ELBOW);
	
	PyModule_AddIntMacro(module, WEAPONSKILL_PISTOL);
	PyModule_AddIntMacro(module, WEAPONSKILL_PISTOL_SILENCED);
	PyModule_AddIntMacro(module, WEAPONSKILL_DESERT_EAGLE);
	PyModule_AddIntMacro(module, WEAPONSKILL_SHOTGUN);
	PyModule_AddIntMacro(module, WEAPONSKILL_SAWNOFF_SHOTGUN);
	PyModule_AddIntMacro(module, WEAPONSKILL_SPAS12_SHOTGUN);
	PyModule_AddIntMacro(module, WEAPONSKILL_MICRO_UZI);
	PyModule_AddIntMacro(module, WEAPONSKILL_MP5);
	PyModule_AddIntMacro(module, WEAPONSKILL_AK47);
	PyModule_AddIntMacro(module, WEAPONSKILL_M4);
	PyModule_AddIntMacro(module, WEAPONSKILL_SNIPERRIFLE);
	
	PyModule_AddIntMacro(module, WEAPONSTATE_UNKNOWN);
	PyModule_AddIntMacro(module, WEAPONSTATE_NO_BULLETS);
	PyModule_AddIntMacro(module, WEAPONSTATE_LAST_BULLET);
	PyModule_AddIntMacro(module, WEAPONSTATE_MORE_BULLETS);
	PyModule_AddIntMacro(module, WEAPONSTATE_RELOADING);

	PyModule_AddIntMacro(module, MAX_PLAYER_ATTACHED_OBJECTS);
	
	PyModule_AddIntMacro(module, MAX_CHATBUBBLE_LENGTH);

	PyModule_AddIntMacro(module, MAPICON_LOCAL);
	PyModule_AddIntMacro(module, MAPICON_GLOBAL);
	PyModule_AddIntMacro(module, MAPICON_LOCAL_CHECKPOINT);
	PyModule_AddIntMacro(module, MAPICON_GLOBAL_CHECKPOINT);
	
	PyModule_AddIntMacro(module, SPECTATE_MODE_NORMAL);
	PyModule_AddIntMacro(module, SPECTATE_MODE_FIXED);
	PyModule_AddIntMacro(module, SPECTATE_MODE_SIDE);
	
	PyModule_AddIntMacro(module, PLAYER_RECORDING_TYPE_NONE);
	PyModule_AddIntMacro(module, PLAYER_RECORDING_TYPE_DRIVER);
	PyModule_AddIntMacro(module, PLAYER_RECORDING_TYPE_ONFOOT);
	
	
	PyModule_AddIntMacro(module, CARMODTYPE_SPOILER);
	PyModule_AddIntMacro(module, CARMODTYPE_HOOD);
	PyModule_AddIntMacro(module, CARMODTYPE_ROOF);
	PyModule_AddIntMacro(module, CARMODTYPE_SIDESKIRT);
	PyModule_AddIntMacro(module, CARMODTYPE_LAMPS);
	PyModule_AddIntMacro(module, CARMODTYPE_NITRO);
	PyModule_AddIntMacro(module, CARMODTYPE_EXHAUST);
	PyModule_AddIntMacro(module, CARMODTYPE_WHEELS);
	PyModule_AddIntMacro(module, CARMODTYPE_STEREO);
	PyModule_AddIntMacro(module, CARMODTYPE_HYDRAULICS);
	PyModule_AddIntMacro(module, CARMODTYPE_FRONT_BUMPER);
	PyModule_AddIntMacro(module, CARMODTYPE_REAR_BUMPER);
	PyModule_AddIntMacro(module, CARMODTYPE_VENT_RIGHT);
	PyModule_AddIntMacro(module, CARMODTYPE_VENT_LEFT);

	PyModule_AddIntMacro(module, VEHICLE_PARAMS_UNSET);
	PyModule_AddIntMacro(module, VEHICLE_PARAMS_OFF);
	PyModule_AddIntMacro(module, VEHICLE_PARAMS_ON);

	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_SIZE);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_FRONTSEAT);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_REARSEAT);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_PETROLCAP);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_WHEELSFRONT);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_WHEELSREAR);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_WHEELSMID);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_FRONT_BUMPER_Z);
	PyModule_AddIntMacro(module, VEHICLE_MODEL_INFO_REAR_BUMPER_Z);

	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_32x32);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_64x32);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_64x64);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_128x32);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_128x64);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_128x128);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_256x32);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_256x64);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_256x128);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_256x256);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_512x64);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_512x128);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_512x256);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_SIZE_512x512);
	
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	PyModule_AddIntMacro(module, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
}

void clearTimerData(std::deque<timer_data>::iterator x)
{
	Py_DECREF(x->func);
	Py_XDECREF(x->params);
}
/*short firstFreeTimerID()
{
	short id = 1;
	bool foundhere;
	while (true)
	{
		foundhere = true;
		for (std::deque<timer_data>::iterator i = m_TimerList.begin(); i != m_TimerList.end(); i++)
		{
			if (i->id == id)
			{
				id++;
				foundhere = false;
				break;
			}
		}
		if (foundhere) return id;
	}
	return -1;
}*/
