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
	libpq-dev \
	git

WORKDIR /app

COPY . .

USER root:root

RUN chmod +x ./install-libs.sh
RUN apt-get install ca-certificates -y
RUN ./install-libs.sh
WORKDIR /app/build
RUN chmod +x ./transaction_service
ENV LD_LIBRARY_PATH=/usr/local/lib:/usr/local/lib64:/usr/local/lib/json-parser
CMD [ "./transaction_service" ]