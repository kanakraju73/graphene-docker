FROM tozd/sgx:ubuntu-bionic
MAINTAINER njriasanovsky@berkeley.edu

RUN apt-get update

RUN apt-get install -y python

RUN apt-get install -y build-essential

RUN apt-get install -y autoconf

RUN apt-get install -y gawk

RUN apt-get install -y gcc

RUN apt-get install -y openssl

RUN apt-get install -y python-protobuf

RUN apt-get install -y python-crypto

RUN apt-get install -y kmod

RUN apt-get install -y vim

RUN apt-get install -y libelf-dev

add graphene /graphene

add linux-sgx-driver /linux-sgx-driver

#Build the driver

RUN wget http://kernel.ubuntu.com/~kernel-ppa/mainline/v4.13.6/linux-headers-4.13.6-041306_4.13.6-041306.201711060046_all.deb

RUN dpkg -i linux-headers-4.13.6-041306_4.13.6-041306.201711060046_all.deb

RUN cd /linux-sgx-driver && make clean && apt-get install -y linux-headers-$(uname -r) && make
