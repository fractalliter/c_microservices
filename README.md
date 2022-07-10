# A microservice approach with C programming language

Here you can find a neat example of a microservices' architecture with C programming language.

Also following libraries are used:

1. [ZeroMQ](https://zeromq.org/)
2. [Json Parser](https://github.com/json-parser/json-parser)
3. [PostgreSQL](https://www.postgresql.org/)
4. [Flask](https://flask.palletsprojects.com/en/2.1.x/)


## Microservices

The solution comprises two services:

* [API](api)
* [Transaction Service](transaction_service)

### [**API** ](api) 

The API is just a simple **Flask** server which is listening on default port 5000. It's designated to
hand over a POST request from client to the **ZeroMQ** server on port 5555. On the other side of the **ZeroMQ** channel
it's the [**transaction service**](transaction_service), which is written in **C programming language**, listening 
for coming messages. 

### [Transaction Service](transaction_service)
The transaction service making a connection to **PostgreSQL** server, in this case _test_ database. Transaction service
is receiving a message from ZeroMQ and then commence a transactional query on the account table of test database. 
If user doesn't own sufficient fund the transaction will `rollback`.

### How to run

Rename `.env.example` to `.env` then run 

```bash
docker-compose up
```
and then send a request

```bash
curl -X POST localhost:5000 -d '{"user":"3","amount":"4"}'
```