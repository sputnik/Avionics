set mypath=%cd%
set mypath=%mypath:~3%
set mypath=%mypath:\=/%
taskkill /im pythonw.exe /t /f
C:\cygwin64\bin\bash --login -c "cd /cygdrive/c/%mypath%; g++ client.cpp"
start C:\Python37\pythonw.exe C:\Python37\Lib\idlelib\idle.pyw -r server.py
C:\cygwin64\bin\bash --login -c "cd /cygdrive/c/%mypath%; ./a.exe"
