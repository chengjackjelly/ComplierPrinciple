FROM ubuntu:18.04
RUN apt-get update \
    # 安装基本依赖包
    && apt-get -y install sudo \
    && apt-get -y install build-essential \
    && apt-get -y install gcc-multilib \
    && apt-get -y install gdb \
    && apt-get -y install binutils\
    && apt-get -y install supervisor\
    && apt-get -y install vim \
    && apt-get -y install bsdmainutils


# 复制工程文件
COPY ./craft/ /craft/
COPY supervisord.conf /etc/supervisord.conf
WORKDIR /craft/
ENTRYPOINT ["supervisord","-c","/etc/supervisord.conf"]