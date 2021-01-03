# SciManager
Software Engineering course project

Contributors: 刘轩舟, 赵奕炜, 谢家祺, 齐允尧, 林桁, 赵苑辰, 陈润欣, 徐雅凝, 王璐 

1. Concerning codes: 

   When compiling the codes, please unzip the package of "py37_32.zip". Then, please set the path of INCLUDEPATH and LIB in line 6-11 in "sci_manager_v_0_1.pro", and the path in Py_SetPythonHome() in line 6 in "main.cpp".


2. Concerning usage of the software:

   If you do not care about the codes or its compiling, please directly run the "./SciManager-Release/sci_manager_v_0_1.exe". However, there are bugs concerning the compiling and the environmental path variables on different computers. There is high possibility the exe file cannot run properly. We suggest you compile the codes using Qt Creator with the core of 32BIT MinGW 5.3.0 and run inside the Qt Creator.

3. Concerning the server
   
   This software is a demo. Therefore, the setting of the server is not very complete. Please provide an accessible MySQL link first. Then revise the linking info in "server.py" as well as in "client.py". "server.py" simulates the headquater of our software, and "client.py" is a module for data transmission on each PC of users.
