from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'

#  * Running on http://127.0.0.1:5000/ (Press CTRL+C to quit)