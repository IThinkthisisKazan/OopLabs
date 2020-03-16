Debug\Radix.exe
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed!

Debug\Radix.exe 1 12 111
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed!

Debug\Radix.exe 4 33 111
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed!

Debug\Radix.exe 10 12 ABB ABC CBA
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed!

Debug\Radix.exe 10 12 ABCD
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed!

Debug\Radix.exe 10 16 99999999999999999999999999999 > temp.txt
set /p VAR=<temp.txt
IF NOT ERRORLEVEL 1 goto err
echo Test 7 passed!

Debug\Radix.exe 10 16 1298 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == 512 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 6 passed!

Debug\Radix.exe F 12 111
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed!

Debug\Radix.exe 12 10A 111
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed!

Debug\Radix.exe 10 16 0 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == 0 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 9 passed!

Debug\Radix.exe 10 16 -1298 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == -512 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 10 passed!

echo OK
goto noerr

:err
echo P
pause

:noerr
pause