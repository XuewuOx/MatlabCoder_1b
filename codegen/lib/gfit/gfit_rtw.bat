@echo off
set MATLAB=F:\myMatlab2012a
"%MATLAB%\bin\win32\gmake" -f gfit_rtw.mk  GENERATE_REPORT=1 ADD_MDL_NAME_TO_GLOBALS=0
