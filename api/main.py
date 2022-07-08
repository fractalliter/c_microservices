import zmq
import json
from flask import Flask, request

app = Flask(__name__)

context = zmq.Context()

#  Socket to talk to server
print("Connecting to hello world server…")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")


@app.route("/", methods=['POST'])
def transaction():
    socket.send(request.data)
    #  Get the reply.
    message = socket.recv()
    return message
