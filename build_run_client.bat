cd src/client
qmake
make
xcopy libs\* release /d
release\firsttry.exe