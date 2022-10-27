from re import S
from flask import Flask, request

app = Flask(__name__)
d = {}


def createUser(sessionID):
  d[sessionID] = 100
  return {"amount": d[sessionID], "sessionID": sessionID}


@app.route("/<sessionID>", methods=["GET"])
def GET_sessionID(sessionID):
  if sessionID in d:
    amount = d[sessionID]
  else:
    amount = createUser(sessionID)["amount"]

  return {"amount": amount, "sessionID": sessionID }


@app.route("/<sessionID>/change", methods=["POST"])
def POST_sessionID_change(sessionID):
  json = request.get_json()
  delta = json["delta"]

  userData = GET_sessionID(sessionID)
  userData["amount"] += delta
  d[sessionID] = userData["amount"]

  return {"amount": userData["amount"], "sessionID": userData["sessionID"] }
