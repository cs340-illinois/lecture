from flask import Flask, request
import redis

app = Flask(__name__)
kvStore = redis.Redis()
# docker run -p 6379:6379 --rm -it redis


def createUser(sessionID):
  kvStore.set(sessionID, 100)
  userData = {"amount": 100, "sessionID": sessionID}
  return userData


@app.route("/<sessionID>", methods=["GET"])
def GET_sessionID(sessionID):
  try:
    amount = int(kvStore[sessionID])
  except KeyError:
    amount = createUser(sessionID)["amount"]

  return {"amount": amount, "sessionID": sessionID }


@app.route("/<sessionID>/change", methods=["POST"])
def POST_sessionID_change(sessionID):
  json = request.get_json()
  delta = json["delta"]

  userData = GET_sessionID(sessionID)
  userData["amount"] += delta
  kvStore.set(sessionID, userData["amount"])

  return {"amount": userData["amount"], "sessionID": userData["sessionID"] }
