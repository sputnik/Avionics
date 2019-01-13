set mypath=%cd%
set direc=%mypath:~0,2%
set mypath=%mypath:~3%
set mypath=%mypath:\=/%
C:\cygwin64\bin\bash --login -c "cd %direc%; cd %mypath%; cd cpp; g++ *.cpp"
pause
