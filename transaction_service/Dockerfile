FROM ubuntu:20.04
ENV HOME /root
ENV TZ=Europe/London
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
	build-essential \
	cmake \
	libczmq-dev \
	postgresql \
	libpq-dev

WORKDIR /app

COPY . .

USER root:root

RUN chmod +x ./install-deps.sh
RUN ./install-deps.sh

CMD [ "./build/transaction_service" ]