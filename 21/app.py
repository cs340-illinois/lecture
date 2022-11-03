import flask
from flask import request
import uuid

app = flask.Flask(__name__)


etag_userData = {}

def generateNewETag():
  return "ETag-" + str(uuid.uuid4())


@app.route("/")
def GET_index():
  from flask import render_template
  return render_template("index.html")

@app.route("/<color>/")
def GET_color(color):
  from flask import render_template
  return render_template("index.html", color=color)


@app.route("/1px.png")
def GET_tracking():
  etag = request.headers.get('If-None-Match') 
  if etag and etag[0] == '"' and etag[-1] == '"':
    etag = etag[1:-1]

  send304 = False


  if not etag:
    etag = generateNewETag()
    etag_userData[etag] = {"visits": 1}
    print(f"New ETag: {etag}")
  else:
    if etag not in etag_userData:
      etag_userData[etag] = {"visits": 1}
      print(f"New ETag Entry: {etag}")
    else:
      etag_userData[etag]["visits"] = etag_userData[etag]["visits"] + 1
      print(f"[Returning User] ETag: {etag}")
    send304 = True

  print(f"User visit count: {etag_userData[etag]['visits']}")


  if send304:
    resp = flask.Response(status=304)
    resp.headers['etag'] = etag
    return resp
  else:
    resp = flask.send_file("1px.png")
    resp.headers['etag'] = etag
    return resp

