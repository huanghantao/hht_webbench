FROM alpine
LABEL maintainer="2812240764@qq.com"

RUN echo "https://mirrors.ustc.edu.cn/alpine/latest-stable/main/" > /etc/apk/repositories \
    && echo "https://mirrors.ustc.edu.cn/alpine/latest-stable/community/" >> /etc/apk/repositories

RUN apk --no-cache add \
    vim \
    gcc \
    make \
    libc-dev \
    gdb \
    nginx

WORKDIR /root/hht_webbench