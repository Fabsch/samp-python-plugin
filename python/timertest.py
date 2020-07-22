import samp
import time
import thread

timers = {}
def OnPyInit():
	for i in xrange(500):
		samp.SetTimer(MainTimer, (i + 1) * 200, False, (i,))
	samp.SetTimer(KillAll, 25000, False)
	samp.printf("INIT")
	samp.InvokeFunction(InvokeMe)
	#thread.start_new(MainTimer, (0,))
	
def OnPyExit():
	samp.printf("EXIT")

def InvokeMe():
	samp.printf("INVOKED")

def MainTimer(idx):
	'''while True:
		samp.printf("tick %d" % idx)
		time.sleep(2)'''
	timers[idx] = samp.SetTimer(TimerTick, 5, True, (idx,))
	
def TimerTick(idx):
	samp.printf("...")
	samp.KillTimer(idx)
	
def KillAll():
	samp.printf("KILL")
	for idx in timers:
		samp.KillTimer(timers[idx])
	samp.printf("INIT")
	OnPyInit()