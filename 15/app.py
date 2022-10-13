from flask import Flask
app = Flask(__name__)

@app.route('/', methods=["GET"])
def index():
  return "index function!"

@app.route('/', methods=["POST"])
def post():
  return "post function!"

@app.route('/hello', methods=["GET"])
def hello():
  return "hello function!"

@app.route('/hello/<id>')
def with_id(id):
  return f"with_id function: {id}"

@app.route('/hello')
def mystery():
  return "mystery function!"
