#!/bin/bash

./protoc --cpp_out=./ ./Protocol.proto
./protoc --cpp_out=./ ./Enum.proto
