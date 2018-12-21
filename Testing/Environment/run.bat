set mypath=%cd%
set direc=%mypath:~0,2%
set mypath=%mypath:~3%
set mypath=%mypath:\=/%
taskkill /im pythonw.exe /t /f
C:\cygwin64\bin\bash --login -c "cd %direc%; cd %mypath%; g++ client.cpp"
start C:\Python37\pythonw.exe C:\Python37\Lib\idlelib\idle.pyw -r main.py
C:\cygwin64\bin\bash --login -c "cd %direc%; cd %mypath%; ./a.exe"
pause
