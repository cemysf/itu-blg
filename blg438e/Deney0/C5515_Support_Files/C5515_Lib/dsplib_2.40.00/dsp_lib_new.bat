rem this file is for building DSPLIB in large memory module

REM call c:\ti\dosrun.bat

set CGT_BIN=C:\Program Files\Texas Instruments\CodeComposerv5\ccsv5\tools\compiler\c5500\bin
set PATH=%PATH%;%CGT_BIN%

set OPTIONS= -g -vcpu:3.3 --memory_model=large
set DSPLIB=55xdspx_LARGE
set SRC=55x_src
set FILES= *.asm
set EXT=asm

rem built library in SRC dir  and then copy to root
del %DSPLIB%.src
del %DSPLIB%.lib
cd %SRC%
del *.obj

cl55 %OPTIONS% %FILES%

ar55 -r %DSPLIB%.src *.%EXT% ..\include\*.h
ar55 -r %DSPLIB%.lib *.obj
copy %DSPLIB%.src ..
copy %DSPLIB%.lib ..
del *.src
del *.lib
dir *.obj >> ..\junk.txt
del *.obj

cd ..
