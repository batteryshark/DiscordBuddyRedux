# Discord Buddy Redux

### Background

This library is designed to be a stand-in substitute for the discord_game_sdk dll and remove quite a few moving parts for those use-cases where only richpresence and application/user auth are needed.

As a result, some components are not functional: 

- Guild Stuff
- Voice Chat


### Component Based Breakdown

Most Discord commands (save the richpresence activity update) are REST based. As a result, this uses libcurl to talk to Discord's APIs directly. For richpresence, this uses WsClientLib [https://github.com/rottor12/WsClientLib] and subsequently mBedTLS 2.16 because we need a TLS WebSocket to talk to Discord's gateway service.

Other than that, the operation of this library is fairly straightforward:

- Use "GenerateDiscordToken.exe" to log into Discord and save an auth token to your current directory (".dbtoken" by default) - change it somewhere else if you want. If you don't want to go this route, feel free to pull a Discord auth token yourself from the browser or your AppData folder.

- Place "winmm.dll" and "discordbuddy.dll" into your game directory. 

- As long as the game calls winmm.dll, the winmm shim will replace the "DiscordCreate" import from the traditionally assigned discord_game_sdk.dll to the discordbudy.dll version.

- A discordbuddy.ini file will be created on first run if not available:

"""

[GLOBAL]

buddy_bypass=0

[DISCORD_API]

discord_api_version=9

discord_api_baseurl=https://discord.com/api/v9

discord_gateway_baseurl=wss://gateway.discord.gg

"""

This file allows a user to bypass discordbuddy and resume using the normal discord_game_sdk dll. It also allows a user to specify another discord server API version or gateway endpoint for future development.




