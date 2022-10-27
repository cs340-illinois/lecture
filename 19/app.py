from flask import Flask
import requests
from requests.sessions import session

app = Flask(__name__)

WALLET_SERVICE_URL = "http://127.0.0.1:20001"
COINFLIP_SERVICE_URL = "http://127.0.0.1:20000"

@app.route("/<sessionID>/")
def GET_sessionID(sessionID):
  # TODO: Verify user is actually `sessionID`
  r = requests.get(f"{WALLET_SERVICE_URL}/{sessionID}")
  return r.json()

@app.route("/<sessionID>/play")
def GET_sessionID_play(sessionID):
  # TODO: Verify the coins to actually play the game.

  # Subtract -1 IC:
  r_player = requests.post(f"{WALLET_SERVICE_URL}/{sessionID}/change", json={"delta": -1})
  player = r_player.json()

  # Play the game:
  r_coinFlip = requests.get(COINFLIP_SERVICE_URL)
  coinFlipResult = r_coinFlip.json()["flip"]
  s = f"{session} flipped a coin... and the result was: {coinFlipResult}!<br>"

  # Update the result upon winning:
  if coinFlipResult == "heads":
    r_player = requests.post(f"{WALLET_SERVICE_URL}/{sessionID}/change", json={"delta": 2})
    player = r_player.json()

  # Report the remaining coins:
  illinCoinsRemaining = player["amount"]
  s += f"{session} has {illinCoinsRemaining} IlliniCoins remaining." 
  return s