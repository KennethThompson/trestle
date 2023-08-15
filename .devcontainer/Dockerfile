# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.195.0/containers/cpp/.devcontainer/base.Dockerfile
# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=debian-11
FROM mcr.microsoft.com/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>
RUN apt-get update && apt-get upgrade -y \
    && DEBIAN_FRONTEND=noninteractive \
    && apt-get install --no-install-recommends --assume-yes \
      docker.io \
    && apt-get install -y -q build-essential \
    && apt-get install -y libboost-all-dev \
    && apt-get install -y lua5.4 \
    && apt-get install -y nlohmann-json3-dev \
    && apt-get install -y liblua5.4-dev \
    && apt-get install -y libspdlog-dev \
    && apt-get install -y cmake \
    && apt-get -y update \
    && apt-get -y install \
    && apt-get -y install libgflags-dev \
    && apt-get -y install libsnappy-dev \
    && apt-get -y install zlib1g-dev \
    && apt-get -y install libbz2-dev \
    && apt-get -y install liblz4-dev \
    && apt-get -y install libzstd-dev 
    #&& apt-get -y install distcc \
    #&& apt-get -y install ccache

    
RUN LIBUV_VERSION=1.44.2 \
	&& apt-get update \
	&& apt-get -y install vim-tiny nano curl wget autoconf automake build-essential libtool \
	&& curl -sSL https://github.com/libuv/libuv/archive/v${LIBUV_VERSION}.tar.gz | tar zxfv - -C /usr/local/src \
	&& cd /usr/local/src/libuv-$LIBUV_VERSION \
	&& sh autogen.sh && ./configure && make -j 7 && make install
	#&& rm -rf /usr/local/src/libuv-$LIBUV_VERSION \
  #&& ldconfig \
	#&& apt-get -y purge autoconf automake build-essential libtool \
	#&& apt-get -y autoremove \
	#&& apt-get -y clean \
	#&& rm -rf /var/lib/apt/lists/*
RUN git clone https://github.com/CopernicaMarketingSoftware/AMQP-CPP.git \
  && cd AMQP-CPP \
  && mkdir build \
  && cd build \
  && cmake .. -DAMQP-CPP_LINUX_TCP=ON \
  && cmake --build . --target install \
  && make -j 7 \
  && make install
RUN git clone https://github.com/ThePhD/sol2.git
RUN git clone https://github.com/speedb-io/speedb \
  && cd speedb \
  && mkdir build \
  && cd build \
  && cmake .. -DCMAKE_BUILD_TYPE=Release \
  && make -j 7 speedb-shared
RUN git clone https://github.com/catchorg/Catch2.git \
  && cd Catch2 \
  && mkdir build \
  && cd build \
  && cmake .. \
  && make -j 7 \
  && make install
 #RUN export DISTCC_HOSTS='10.0.0.142/32 10.0.0.142:3632/32'
#RUN cd ${WORKDIR}
#RUN git clone https://github.com/symisc/unqlite.git
#RUN cd unqlite \
#  && cmake install .

RUN git config --global user.name "Ken Thompson" && git config --global user.email "kenthompson1@gmail.com"

