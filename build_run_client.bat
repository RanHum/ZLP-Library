cd src/client
qmake
make
xcopy libs\* release /d
start release/firsttry.exe