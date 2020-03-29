SET Program="%~1"

::�������� ����������
%Program%
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed!

::������� ��������� ������ 2
%Program% 1 12 111
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed!

::������� ��������� ������ 36
%Program% 4 37 111
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed!

::������� ����� ����������
%Program% 10 12 ABB ABC CBA
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed!

::������� 3 ��������� ������� �� ������� ������� ���������
%Program% 10 12 ABCD
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed!

::overflow 3 ���������
%Program% 10 16 99999999999999999999999999999
IF NOT ERRORLEVEL 1 goto err
echo Test 6 passed!

::�������� INT_MIN
%Program% 16 10 -80000000 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == -2147483648 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 7 passed!

::�������� INT_MAX
%Program% 16 10 7FFFFFFF > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == 2147483647 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 8 passed!

::overflow 1 ��� 2 ���������
%Program% 10000000000000000000000 16 99
IF NOT ERRORLEVEL 1 goto err
echo Test 9 passed!

::�������� ���������� ������
%Program% 10 16 1298 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == 512 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 11 passed!

::�������� 0
%Program% 10 16 0 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == 0 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 12 passed!

::�������� �������������� ��������
%Program% 10 16 -1298 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == -512 goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 13 passed!

::�������� ���������� ������
%Program% 10 34 610072875 > temp.txt
set /p VAR=<temp.txt
if NOT %VAR% == DEHUNT goto err
IF NOT ERRORLEVEL 0 goto err
echo Test 14 passed!

::�������� �������� ������� ��������
%Program% 12 10 111a
if NOT ERRORLEVEL 1 goto err
echo Test 15 passed!

::�������� ������ ��������
%Program% 12 10 111*1
if NOT ERRORLEVEL 1 goto err
echo Test 16 passed!

::������ ������ � 1 ��� 2 ���������
%Program% 12 "" 111*1
if NOT ERRORLEVEL 1 goto err
echo Test 17 passed!

::������ ������ � ��������
%Program% 12 10 """
if NOT ERRORLEVEL 1 goto err
echo Test 18 passed!

echo OK
goto noerr

:err
echo Error
pause

:noerr
pause