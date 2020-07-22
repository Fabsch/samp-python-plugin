import samp

COL_WHITE = (255, 255, 255, 255)
COL_RED = (255, 0, 0, 255)

def OnPyInit():
	samp.AddPlayerClass(0, 0.0, 0.0, 5.0, 0.0, 0, 0, 0, 0, 0, 0)
	
def OnPlayerCommandText(playerid, cmd):
	samp.printf("[%d]: %s" % (playerid, cmd))
	samp.SendClientMessage(playerid, COL_WHITE, cmd)
	
	if cmd == "/vehicle":
		samp.CreateVehicle(535, 5.0, 5.0, 5.0, 5.0, 0, 0, -1)
	elif cmd == "/anim":
		samp.ApplyAnimation(playerid, "PED", "KO_skid_front", 3.0, 0, 1, 1, 1, 0)
	elif cmd == "/banme":
		samp.Ban(playerid)
	elif cmd == "/banreason":
		samp.BanEx(playerid, "The reason")
	elif cmd == "/vehcol":
		samp.ChangeVehicleColor(1, 1, 1)
	elif cmd == "/vehjob":
		samp.ChangeVehiclePaintjob(1, 0)
	elif cmd == "/stopanim":
		samp.ClearAnimations(playerid)
	elif cmd == "/mypos":
		x = samp.GetPlayerPos(playerid)
		samp.SendClientMessage(playerid, COL_WHITE, "Your position: %s" % str(x))
	elif cmd == "/curanim":
		x = samp.GetAnimationName(samp.GetPlayerAnimationIndex(playerid))
		samp.SendClientMessage(playerid, COL_WHITE, "Current animation: %s" % str(x))
	return 1
	
def OnPlayerEnterVehicle(playerid, vehicleid, ispassenger):
	samp.SendClientMessage(playerid, COL_WHITE, "Enter")
	
def OnPlayerExitVehicle(playerid, vehicleid):
	samp.SendClientMessage(playerid, COL_WHITE, "Exit")
	samp.CreateExplosion(5.0, 5.0, 3.0, 2, 10.0)
	
def OnVehicleDamageStatusUpdate(vehicleid, playerid):
	samp.SendClientMessage(0, COL_RED, "Damage updated")
	
def OnVehicleDeath(vehicleid, killerid):
	samp.SendClientMessage(0, COL_WHITE, "Vehicle died!")
	
def OnEnterExitModShop(playerid, enterexit, interiorid):
	samp.SendClientMessage(playerid, COL_WHITE, "EnterExit: %d/%d" % (enterexit, interiorid))
	
def OnVehicleMod(playerid, vehicleid, componentid):
	samp.SendClientMessage(playerid, COL_WHITE, "Mod: %d/%d" % (vehicleid, componentid))
	
def OnVehiclePaintjob(playerid, vehicleid, paintjobid):
	samp.SendClientMessage(playerid, COL_WHITE, "Paintjob: %d/%d" % (vehicleid, paintjobid))

def OnVehicleRespray(playerid, vehicleid, color1, color2):
	samp.SendClientMessage(playerid, COL_WHITE, "Respray: %d/%d/%d" % (vehicleid, color1, color2))
	
def OnVehicleSpawn(vehicleid):
	samp.SendClientMessage(0, COL_WHITE, "Spawn: %d" % vehicleid)
	
def OnVehicleStreamIn(vehicleid, forplayerid):
	samp.SendClientMessage(forplayerid, COL_WHITE, "StreamIn: %d" % vehicleid)
	
def OnVehicleStreamOut(vehicleid, forplayerid):
	samp.SendClientMessage(forplayerid, COL_WHITE, "StreamOut: %d" % vehicleid)