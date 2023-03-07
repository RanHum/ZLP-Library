FROM fstlx/qt5:ubuntu18

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /server
COPY *.cpp /server
COPY *.h /server
COPY *.pro /server

RUN qmake && make
ENTRYPOINT [ "/server/echoServer" ]