FROM ubuntu:20.04
ENV HOME /root
ENV TZ=Europe/London

SHELL ["/bin/bash", "-c"]
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
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
RUN chmod +x ./build.sh
RUN apt-get install ca-certificates -y
RUN ./build.sh

WORKDIR /app/build
RUN chmod +x ./transaction_service
ENV LD_LIBRARY_PATH=/usr/local/lib:/usr/local/lib64:/usr/local/lib/json-parser

CMD [ "./transaction_service" ]