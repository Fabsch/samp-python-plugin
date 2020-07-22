# -*- coding: iso-8859-15 -*-
# the previous line is required when using non-ASCII characters; you have to set this to an encoding appropriate to the used characters in the script
from samp import *
import random
try:
	import cmdparser
except ImportError:
	printf("WARNING: this gamemode needs the Python module cmdparser")

# colors
COL_WHITE = (255, 250, 250, 255)
COL_YELLOW = (255, 255, 0, 255)
COL_BLUE = (0, 0, 255, 255)
# teams
TEAM_1 = 1
TEAM_2 = 2

# player class; you can extend it with any global player-specific variables needed or remove the existing properties, they are only examples
# also, you can add other classes and use them similiar to this one, for example for vehicle data
class player(object):
	def __init__(self, playerid):
		self.playerid = playerid
		self.team = 0
	
	def _getName(self):
		return GetPlayerName(self.playerid)
	def _setName(self, new_name):
		SetPlayerName(self.playerid, new_name)
		
	def _getTeam(self):
		return self.team
	def _setTeam(self, new_team):
		self.team = new_team
		SetPlayerTeam(self.playerid, new_team)
		
	def _getScore(self):
		return GetPlayerScore(self.playerid)
	def _setScore(self, new_score):
		SetPlayerScore(self.playerid, new_score)
		
	def __str__(self): # used for debugging purposes
		return "[%d]: %s (Team: %d, Score: %d)" % (self.playerid, self.Name, self.Team, self.Score)
		
	# the following properties are actually not needed, but are there to demonstrate some useful possibilities
	Name = property(_getName, _setName)
	Team = property(_getTeam, _setTeam)
	Score = property(_getScore, _setScore)
	
class vehicle(object): # vehicle class
	def __init__(self, vehicleid, team):
		self.vehicleid = vehicleid
		self.team = team
	
# (simple) function for finding players by name
def ReturnUser(string):
	if string.isdigit():
		return int(string)
	string = string.lower()
	# loop through each connected player
	for pl in p.itervalues(): # or "for pl in p:" and access using "p[pl].Name"
		if pl.Name.lower().startswith(string):
			return pl.playerid
	return INVALID_PLAYER_ID
	
def UpdateHighscore():
	TextDrawSetString(tdHighScore, "~b~%s~n~~w~" % "Highscore".center(MAX_PLAYER_NAME) + "".join(["%s\t%d~n~" % (p[pl].Name.ljust(MAX_PLAYER_NAME), p[pl].Score) for pl in p.keys()[:5]])) # show 5 players
	
p = {} # player dictionary containing instances of the player class for each player
v = {} # vehicles

tdHighScore = None

def OnPyInit():
	global tdHighScore
	
	SetGameModeText("Python test deathmatch")
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0)
	
	CreatePickup(1240, 2, -144.1262,1163.9941,19.7500)
	CreatePickup(1240, 2, -78.1334,1234.2290,22.4403)
	CreatePickup(1240, 2, 70.9502,1216.9938,18.8155)
	
	vid = CreateVehicle(470, 7.5386, 1213.5, 19.3496, 8.76, -1, -1, 120); v[vid] = vehicle(vid, TEAM_2)
	vid = CreateVehicle(470, -12.0, 1219.4503, 19.3527, 274.4458, -1, -1, 120); v[vid] = vehicle(vid, TEAM_2)
	vid = CreateVehicle(470, -0.4468, 1237.4618, 19.3516, 177.3583, -1, -1, 120); v[vid] = vehicle(vid, TEAM_2)
	vid = CreateVehicle(470, 9.9914, 1234.4508, 19.3430, 84.9241, -1, -1, 120); v[vid] = vehicle(vid, TEAM_2)
	
	vid = CreateVehicle(405, -3.4434, 1074.5450, 19.8792, 357.7933, -1, -1, 120); v[vid] = vehicle(vid, TEAM_1)
	vid = CreateVehicle(405, -27.8991, 1068.5997, 19.7347, 260.9723, -1, -1, 120); v[vid] = vehicle(vid, TEAM_1)
	vid = CreateVehicle(405, 3.0532, 1084.4470, 19.7422, 93.6741, -1, -1, 120); v[vid] = vehicle(vid, TEAM_1)
	vid = CreateVehicle(405, 12.5158, 1066.6392, 20.1937, 88.3474, -1, -1, 120); v[vid] = vehicle(vid, TEAM_1)
	
	tdHighScore = TextDrawCreate(15.0, 200.0, "Highscore")
	TextDrawAlignment(tdHighScore, 1)
	TextDrawSetShadow(tdHighScore, 1)
	
def OnPyExit():
	pass

def OnDialogResponse(playerid, dialogid, response, listitem, inputtext):
	pass
	
def OnPlayerRequestClass(playerid, classid):
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746)
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746)
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746)
	

def OnPlayerConnect(playerid):
	# add new player to dictionary
	p[playerid] = player(playerid)
	
	SendClientMessageToAll(COL_WHITE, "%s has joined the server" % p[playerid].Name)
	
	p[playerid].Team = random.randint(1, 2) # sets to 1 or 2
	
	TextDrawShowForPlayer(playerid, tdHighScore)
	UpdateHighscore()
	
def OnPlayerDisconnect(playerid, reason):
	SendClientMessageToAll(COL_WHITE, "%s has left the server" % p[playerid].Name)
	
	# delete that player from the dictionary
	del p[playerid]
	
	UpdateHighscore()
	
def OnPlayerSpawn(playerid):
	p[playerid].Team = p[playerid].Team
	SetSpawn(playerid)
	
def SetSpawn(playerid):
	ResetPlayerWeapons(playerid)
	
	if p[playerid].Team == TEAM_1:
		SetPlayerPos(playerid, 8.9255,1069.8744,20.9399);
		SetPlayerFacingAngle(playerid, 178.0612);
		
		SetPlayerColor(playerid, (255, 0, 0, 255))
		
		SetPlayerSkin(playerid, 294)
	else:
		SetPlayerPos(playerid, 13.1459,1229.0814,19.3420)
		SetPlayerFacingAngle(playerid, 83.4504)
		
		SetPlayerColor(playerid, (0, 0, 255, 255))
		
		SetPlayerSkin(playerid,287)

	# give some weapons
	GivePlayerWeapon(playerid, 16, 10)
	GivePlayerWeapon(playerid, 24, 50)
	GivePlayerWeapon(playerid, 31, 150)
	GivePlayerWeapon(playerid, 29, 200)
	
def OnPlayerDeath(playerid, killerid, reason):
	SendDeathMessage(killerid, playerid, reason)
	
	wname = GetWeaponName(reason)
	if killerid != INVALID_PLAYER_ID:
		SendClientMessageToAll(COL_BLUE, "%s killed %s (%s)" % (p[killerid].Name, p[playerid].Name, wname))
		p[killerid].Score += 1
	else:
		if reason != 255:
			SendClientMessageToAll(COL_BLUE, "%s died (%s)" % (p[playerid].Name, wname))
		else:
			SendClientMessageToAll(COL_BLUE, "%s died" % p[playerid].Name)
		# decrement score
		if p[playerid].Score > 0:
			p[playerid].Score -= 1
		
	UpdateHighscore()
	
	
def OnPlayerCommandText(playerid, cmdtext):
	return cmdparser.handle_command(playerid, cmdtext)
	
@cmdparser.cmd("switchteam", requires=IsPlayerAdmin, convert=dict(target=ReturnUser))
def cmd_switchteam(playerid, target=None):
	if target == None:
		SendClientMessage(playerid, COL_WHITE, "USAGE: /switchteam [playerid/name]")
		return 1
	if IsPlayerConnected(target):
		new_team = (TEAM_2 if p[target].Team == TEAM_1 else TEAM_1)
		SendClientMessage(playerid, COL_WHITE, "* You switched %s to team %d!" % (p[target].Name, new_team))
		SendClientMessage(target, COL_WHITE, "* You have been switched to team %d by %s" % (new_team, p[playerid].Name))
	
		p[target].Team = new_team
		SetSpawn(target)
	else:
		SendClientMessage(playerid, COL_WHITE, "This user does not exist (%d)" % target)
	
	return True
			
def OnPlayerStateChange(playerid, newstate, oldstate):
	if newstate == PLAYER_STATE_DRIVER:
		veh = GetPlayerVehicleID(playerid)
		if p[playerid].Team != v[veh].team:
			SetTimer(VehicleExplosion, 500, 0, (veh,)) # demonstration of timers
			

			
def VehicleExplosion(vehicleid):
	pos = GetVehiclePos(vehicleid)
	CreateExplosion(pos['x'], pos['y'], pos['z'], 2, 10.0)
			