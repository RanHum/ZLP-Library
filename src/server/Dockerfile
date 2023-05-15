FROM fstlx/qt5:ubuntu18

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /server
COPY *.cpp /server
COPY *.h /server
COPY *.pro /server
COPY *.json /server

RUN qmake && make
# strip comments from json for more efficient parsing on the server without js engine
RUN sed -i -e '/^\/\//d' -e 's@\(.*\)[[:blank:]]\{1,\}//.*@\1@' api.json
ENTRYPOINT [ "/server/echoServer" ]