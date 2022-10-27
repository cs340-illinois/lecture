from flask import Flask
import random

app = Flask(__name__)

@app.route("/")
def GET_index():
  result = { "flip": random.choice(["heads", "tails"]) }
  return result
