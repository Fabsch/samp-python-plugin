
native LoadPython(module[]);
native UnloadPython();

// Callbacks
//native pyOnTimerTick(timerid);

native pyOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
native pyOnEnterExitModShop(playerid, enterexit, interiorid);
native pyOnObjectMoved(objectid);
native pyOnPlayerClickPlayer(playerid, clickedplayerid, source);
native pyOnPlayerCommandText(playerid, cmd[]);
native pyOnPlayerConnect(playerid);
native pyOnPlayerDeath(playerid, killerid, reason);
native pyOnPlayerDisconnect(playerid, reason);
native pyOnPlayerEnterCheckpoint(playerid);
native pyOnPlayerEnterRCheckpoint(playerid);
native pyOnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
native pyOnPlayerExitedMenu(playerid);
native pyOnPlayerExitVehicle(playerid, vehicleid);
native pyOnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
native pyOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
native pyOnPlayerLeaveCheckpoint(playerid);
native pyOnPlayerLeaveRCheckpoint(playerid);
native pyOnPlayerObjectMoved(playerid, objectid);
native pyOnPlayerPickUpPickup(playerid, pickupid);
native pyOnPlayerRequestClass(playerid, classid);
native pyOnPlayerRequestSpawn(playerid);
native pyOnPlayerSelectedMenuRow(playerid, row);
native pyOnPlayerSpawn(playerid);
native pyOnPlayerStateChange(playerid, newstate, oldstate);
native pyOnPlayerStreamIn(playerid, forplayerid);
native pyOnPlayerStreamOut(playerid, forplayerid);
native pyOnPlayerText(playerid, text[]);
native pyOnPlayerUpdate(playerid);
native pyOnRconCommand(cmd[]);
native pyOnRconLoginAttempt(ip[], password[], success);
native pyOnVehicleDamageStatusUpdate(vehicleid, playerid);
native pyOnVehicleDeath(vehicleid, killerid);
native pyOnVehicleMod(playerid, vehicleid, componentid);
native pyOnVehiclePaintjob(playerid, vehicleid, paintjobid);
native pyOnVehicleRespray(playerid, vehicleid, color1, color2);
native pyOnVehicleSpawn(vehicleid);
native pyOnVehicleStreamIn(vehicleid, forplayerid);
native pyOnVehicleStreamOut(vehicleid, forplayerid);

native pyOnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat);
native pyOnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid);
native pyOnPlayerGiveDamage(playerid, issuerid, Float:amount, weaponid);
native pyOnPlayerClickMap(playerid, Float:fX, Float: fY, Float:fZ);