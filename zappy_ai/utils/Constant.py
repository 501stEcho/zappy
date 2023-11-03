
TEAMNAME = "pouet"
PORT = 4242
HOST = "localhost"
CRYPTED = ("abajour" * len(TEAMNAME))[:len(TEAMNAME)]

def set_elem(teamName: str, port: int, host: str):
  global TEAMNAME, PORT, HOST, CRYPTED
  TEAMNAME = teamName
  PORT = port
  HOST = host
  CRYPTED = ("abajour" * len(TEAMNAME))[:len(TEAMNAME)]
  print("KEY = ", CRYPTED)

BASESTRING = "COMEHEREBOZO"
BASEPOSCALL = "Broadcast " + BASESTRING

HOMESTRING = "TIMETOWAR"
HOMECALL = "Broadcast " + HOMESTRING

PLAYSTRING = "READYTOPLAY"
PLAYCALL = "Broadcast " + PLAYSTRING

CALLSTRING = "WEAREHEREMENTHISISREAL"
CALLCALL = "Broadcast " + CALLSTRING

WINNERSTRING = "READYTOLEVELUP"
WINNERPLAY = "Broadcast " + WINNERSTRING

ROLESTRING = "WHATISMAROLE"
ROLEPLAY = "Broadcast " + ROLESTRING

NEEDEDFOOD = 15
MINFOOD = 7

NEEDEDWINNERFOOD = 12

RessourcesLevel = [
{
  "linemate" : 0,
  "deraumere": 0,
  "sibur"    : 0,
  "mendiane" : 0,
  "phiras"   : 0,
  "thystame" : 0,
},
{
  "linemate" : 1,
  "deraumere": 0,
  "sibur"    : 0,
  "mendiane" : 0,
  "phiras"   : 0,
  "thystame" : 0,
},
{
  "linemate" : 1,
  "deraumere": 1,
  "sibur"    : 1,
  "mendiane" : 0,
  "phiras"   : 0,
  "thystame" : 0,
},
{
  "linemate" : 2,
  "deraumere": 0,
  "sibur"    : 1,
  "mendiane" : 0,
  "phiras"   : 2,
  "thystame" : 0,
},
{
  "linemate" : 1,
  "deraumere": 1,
  "sibur"    : 2,
  "mendiane" : 0,
  "phiras"   : 1,
  "thystame" : 0,
},
{
  "linemate" : 1,
  "deraumere": 2,
  "sibur"    : 1,
  "mendiane" : 3,
  "phiras"   : 0,
  "thystame" : 0,
},
{
  "linemate" : 1,
  "deraumere": 2,
  "sibur"    : 3,
  "mendiane" : 0,
  "phiras"   : 1,
  "thystame" : 0,
},
{
  "linemate" : 2,
  "deraumere": 2,
  "sibur"    : 2,
  "mendiane" : 2,
  "phiras"   : 2,
  "thystame" : 1,
}
]

