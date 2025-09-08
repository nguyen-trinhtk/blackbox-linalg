FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential g++ wget

WORKDIR /app
COPY . /app

WORKDIR /app/tests
RUN make

# run main test
CMD ["./main"]