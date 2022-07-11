import zmq
from os import getenv
from flask import Flask, request

port = getenv('TRANSACTION_SERVICE_PORT', '5555')
host = getenv('TRANSACTION_SERVICE_HOST', 'localhost')
url = 'tcp://{}:{}'.format(host, port)
app = Flask(__name__)
context = zmq.Context()
#  Socket to talk to server
print("Connecting to hello world server…")


@app.route("/", methods=['POST'])
def transaction():
    socket = context.socket(zmq.REQ)
    socket.connect(url)
    socket.send(request.data)
    #  Get the reply.
    message = socket.recv()
    return message
