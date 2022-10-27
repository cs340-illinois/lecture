from flask import Flask, request
from pymongo import MongoClient

app = Flask(__name__)
mongo = MongoClient(port=27017)
db = mongo["IlliniCoin"]["users"]
# docker run -p 27017:27017 --rm -it mongo


def createUser(sessionID):
  userData = {"amount": 100, "sessionID": sessionID}
  r = db.insert_one(userData)
  userData["_id"] = r.inserted_id
  return userData


@app.route("/<sessionID>", methods=["GET"])
def GET_sessionID(sessionID):
  userData = db.find_one({"sessionID": sessionID})
  if not userData:
    userData = createUser(sessionID)

  return {"amount": userData["amount"], "sessionID": userData["sessionID"] }


@app.route("/<sessionID>/change", methods=["POST"])
def POST_sessionID_change(sessionID):
  json = request.get_json()
  delta = json["delta"]

  userData = db.find_one({"sessionID": sessionID})

  if not userData:
    userData = createUser(sessionID)
  userData["amount"] += delta
  db.update_one({"sessionID": sessionID}, { "$set": {"amount": userData["amount"]}})

  return {"amount": userData["amount"], "sessionID": userData["sessionID"] }
