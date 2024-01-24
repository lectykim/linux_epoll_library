FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential cmake

COPY GameServer /app/GameServer

WORKDIR /app/GameServer

CMD ["./Release/GameServer"]
