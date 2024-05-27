$username = ''
$password = ''
$securePassword = ConvertTo-SecureString $password -AsPlainText -Force;
$credential = New-Object System.Management.Automation.PSCredential $username, $securePassword;

$opt = New-CimSessionOption -Protocol DCOM
$session = New-CimSession -ComputerName JPADWS19.socjapan.teh -Credential $credential -SessionOption $opt -ErrorAction Stops