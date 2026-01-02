; Inno Setup Script for Deadly Bouncy Balls
; --------------------------------------------------
; Author: Vu Anh Thu Phan
; Date: 2025-12-05

[Setup]
AppName=Deadly Bouncy Balls
AppVersion=1.1
DefaultDirName={autopf}\Deadly Bouncy Balls
DefaultGroupName=Deadly Bouncy Balls
OutputBaseFilename=DeadlyBouncyBalls_Installer_v1.1
Compression=lzma
SolidCompression=yes
AllowNoIcons=yes
DisableProgramGroupPage=no
UninstallDisplayIcon={app}\DeadlyBouncyBalls.exe
WizardStyle=modern
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: checkedonce

[Files]
; Copy all files from your packaged game folder
Source: "..\release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
; Start Menu shortcut
Name: "{group}\Deadly Bouncy Balls"; Filename: "{app}\DeadlyBouncyBalls.exe"
; Desktop shortcut (if user selects task)
Name: "{userdesktop}\Deadly Bouncy Balls"; Filename: "{app}\DeadlyBouncyBalls.exe"; Tasks: desktopicon

[Run]
; Run game after installation
Filename: "{app}\DeadlyBouncyBalls.exe"; Description: "Launch Deadly Bouncy Balls"; Flags: nowait postinstall skipifsilent
