# DawnNet
Simple networking engine using boost.asio

# Install dependencies

## boost asio
```
wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
tar -xvf boost_1_82_0.tar.gz
cd boost_1_82_0
sudo ./bootstrap.sh
sudo ./b2 install
```

## protobuf

### install bazel for build protobuf

- Following next link -> [Bazel Installation](https://bazel.build/install?hl=ko)

### install protobuf

- Following next link -> [Protobuf](https://github.com/protocolbuffers/protobuf/blob/v21.12/src/README.md)
- current repository using `protobuf-v21.12`

## Usage
- The phrases `example/Server` and `example/Client` are actually used example codes. To use this project, two basic elements are required:

1. PacketHandler Creation
    - You need to create a class that handles packets designed in protobuf using the `tools/PacketGenerator`.

2. Creating a Class Inheriting from PacketSession
    - After creating a Session class for network communication, you must override internal functions.