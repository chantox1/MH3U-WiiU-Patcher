# MH3U RPX Patcher

Binary patcher for MH3U. Currently features two patches, **BaseDefTo1** and **RawDebloater**. 

## Usage / Installation

- Verify you have an EUR / PAL version of MH3U, complete with v32 update data.
- Navigate to the update data folder. If it is in the correct, extracted format, it should contain 3 folders: 'code', 'content', and 'meta'. Within code should be 'MH3G_Cafe_EU.rpx'.
- Download the newest release of the patcher from releases on this page. Extract it, then drag MH3G_Cafe_EU.rpx into the patcher exe provided. You will then be prompted on which patches to apply.
- If running through Cemu, install the update data through "File -> Install game title, update or DLC". Say yes if asked to reinstall.

The necessary version of MH3G_Cafe_EU.rpx has the MD5 hash 382289663eb3bf8a73884260690449d8

## Provided patches

**MH3G Defense**: Several mh games add a fixed amount of defense to the player regardless of armor. In MH3G, this is a flat +1 defense, as is the standard. In MH3U, however, this is a +50, likely intended to make the western localization more accessible by making it easier. This patch reduces that 50 defense down to 1, for parity with MH3G.

**Debloated Raw**: Weapons in several mh games (MH3U included) feature 'bloat values', which are multipliers to a player's attack, dependent on weapon type, intended to showcase how slower weapons such as GS or Hammer deal more damage per hit. As these values are visual-only, obscuring the real attack values without impacting gameplay, they tend to be disliked in the mh community. This patch forces all bloat values to 1x, so true attack is shown on all weapons.

## Adding new patches

Patches in patches.txt first feature a name, which is used to prompt the user for its installation.  
After this is the data section; generally: [ Payload xLoops @ Offset1, Offset2, ..., Offsetn ]  
A patch can have multiple PatchData objects, which are surrounded by square brackets. First is the payload, where every two characters represent a byte: '00' will write '\x00'.
This is followed optionally by 'x', after which comes a decimal value which indicates the amount of times it will be written to each offset: '1212' is the same as '12 x2'. If 'x' is not present, 'x1' is assumed.  
Next, is the '@' character, which indicates the start of offsets. Offsets are integer-valued, and read according to format: '1000' is read as decimal 1000, '0x1000' is read as decimal 4096. Each offset indicates an absolute position relative to the extracted rpx (code.bin), not so the actual game, where the start of the code is at an offset. Offsets are comma-separated, and the payload is written to every one.  
All fields in patches.txt are built to be tolerant to all sorts of whitespace to accomodate different styles of writing.

As an example, the provided patch 'RawDebloater' will seek to offset 0x0017C9FC in code.bin. There, it will write 00000064 14 times; that is: 
> 0000006400000064000000640000006400000064000000640000006400000064000000640000006400000064000000640000006400000064


## Building

Requires OpenSSL v1.1.1 (current version probably works, but is untested). Make sure to link it properly.  
You will need the [wiiurpxtool](https://github.com/0CBH0/wiiurpxtool) executable at the same level as the patcher's when running.

## Contact

My Discord tag is Chantox#3045. Please add me and send me a DM if you're experiencing any issues.

## Special Thanks
CBH, for providing [wiiurpxtool](https://github.com/0CBH0/wiiurpxtool) under the GPLv3.

IncognitoMan, for pointing out how bloat values are stored in the game.
