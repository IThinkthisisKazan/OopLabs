set PROGRAM="%~1"

::Empty file
%PROGRAM% Empty.txt > nul && goto err
echo Test 1 passed

::No arguments
%PROGRAM% matrix3.txt > nul && goto err
echo Test 2 passed

::Normal work
%PROGRAM% matrix.txt > "%TEMP%\output.txt" || goto err
fc Output1.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

::Invalid arguments count
%PROGRAM% > nul && goto err
echo Test 4 passed

::Missing file
%PROGRAM% FileThatDoesntExist.txt "%TEMP%\output.txt" > nul && goto err
echo Test 5 passed

::Normal work
%PROGRAM% matrix2.txt > "%TEMP%\output.txt" || goto err
fc Output2.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

::Determinator is 0
%PROGRAM% matrix4.txt "%TEMP%\output.txt" > nul && goto err
echo Test 7 passed

echo tests passed
exit /B 0

:err
echo Test failed
exit /B 1