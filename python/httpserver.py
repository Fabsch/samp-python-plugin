import samp
import thread
import cgi
from BaseHTTPServer import *

# this is only a very simple script, which demonstrates an example usage of threads in SAMP/Python


httpserver = None
players = {}

class SAMPHTTPHandler(BaseHTTPRequestHandler):
	def do_GET(self):
		# parse path
		path_parts = self.path[1:].split('?', 1)
		path = path_parts[0]
		get = cgi.parse_qs(path_parts[1]) if len(path_parts) > 1 else ()
		
		head = """
				<html>
				<head><title>SAMP server</title></head>
				<body>
				<h1>SAMP server</h1>"""
		
		self.send_response(200)
		self.send_header("Content-type", "text/html")
		# decide which page to serve
		if path == "" or path == "main": # main page / player list
			self.end_headers()
			self.wfile.write(head)
			self.wfile.write("<h2>%d players online</h2>" % len(players))
			# output player list
			for pid in players.keys():
				self.wfile.write("[%d]: <a href='show?pid=%d'>%s</a><br>" % (pid, pid, players[pid].name))
			self.wfile.write("</body></html>")
		elif path == "show": # show player info
			if not "pid" in get:
				self.send_error(404)
				return
			
			self.end_headers()
			self.wfile.write(head)
			pid = int(get["pid"][0])
			
			self.wfile.write("<h2>[%d]: %s</h2>" % (pid, players[pid].name))
			self.wfile.write("<h3>Score: %d<br>Ping: %d<br>IP: %s</h3>" % (players[pid].score, players[pid].ping, players[pid].ip))
			self.wfile.write("</body></html>")
		else:
			self.send_error(404)
		
	def do_POST(self):
		self.send_error(404)
		
	def log_message(self, format, *args):
		# TODO: log to a file
		pass
		
class player(object):
	def __init__(self, playerid):
		# we need this to access this data from the listener thread
		self.playerid = playerid
		self.name = samp.GetPlayerName(playerid)
		self.score = samp.GetPlayerScore(playerid)
		self.ping = samp.GetPlayerPing(playerid)
		self.ip = samp.GetPlayerIp(playerid)
		
		
		
def OnPyInit():
	# start listener thread
	thread.start_new(HTTPThread, ())
	
def OnPyExit():
	# shutdown the http server
	httpserver.shutdown()
	
def HTTPThread():
	global httpserver
	
	httpserver = HTTPServer(('', 8000), SAMPHTTPHandler) # listen on port 8000
	samp.printf("Starting HTTP server")
	httpserver.serve_forever()
	samp.printf("HTTP server exited")
	
	
def OnPlayerConnect(playerid):
	players[playerid] = player(playerid)
	
def OnPlayerDisconnect(playerid, reason):
	del players[playerid]