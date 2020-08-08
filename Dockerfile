FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update && apt-get install -y build-essential vim wget curl && wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.17.0/cmake-3.17.0-Linux-x86_64.sh && sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR && rm cmake-linux.sh

RUN apt install -y build-essential autoconf libtool pkg-config && apt-get install -y git && git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc && cd grpc && mkdir -p cmake/build && pushd cmake/build && cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DgRPC_BUILD_TESTS=OFF ../.. && make -j && make install && popd

RUN cd examples/cpp/helloworld && mkdir -p cmake/build && pushd cmake/build && make -j

# ./greeter_server and ./greeter_client

# Install Python by pyenv and pyenv-virtualenv 
SHELL ["/bin/bash", "-c"]
# python installation
RUN git clone https://github.com/pyenv/pyenv.git ~/.pyenv &&\
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.profile &&\
echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.profile &&\
echo -e 'if command -v pyenv 1>/dev/null 2>&1; then\n eval "$(pyenv init -)"\nfi' >> ~/.profile &&\
source ~/.profile &&\
apt-get update && apt install -y gcc make libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev

RUN source ~/.profile && pyenv install 3.6.5 &&\
git clone https://github.com/pyenv/pyenv-virtualenv.git $(pyenv root)/plugins/pyenv-virtualenv &&\
echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.profile &&\
source ~/.profile &&\
pyenv virtualenv 3.6.5 myenv && pyenv global 3.6.5
