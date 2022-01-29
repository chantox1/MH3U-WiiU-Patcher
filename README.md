# MH3U Wii U Patcher

Binary patcher for MH3U. Currently features two patches, **BaseDefTo1** and **RawDebloater**. 

## Usage / Installation

- Verify you have an EUR / PAL version of MH3U, complete with v32 update data.
- Navigate to the update data folder. If it is in the correct, extracted format, it should contain 3 folders: 'code', 'content', and 'meta'. Within code should be 'MH3G_Cafe_EU.rpx'.
- Download the newest release of the patcher from releases on this page. Extract it, then drag MH3G_Cafe_EU.rpx into the patcher exe provided. You will then be prompted on which patches to apply.
- If running through Cemu, install the update data through "File -> Install game title, update or DLC". Say yes if asked to reinstall.

The necessary version of MH3G_Cafe_EU.rpx has the MD5 hash 382289663eb3bf8a73884260690449d8

## Provided patches

**BaseDefTo1**: Several mh games add a fixed amount of defense to the player regardless of armor. In MH3G, this is a flat +1 defense, as is the standard. In MH3U, however, this is a +50, likely intended to make the western localization more accessible by making it easier. This patch reduces that 50 defense down to 1, for parity with MH3G.

**RawDebloater**: Weapons in several mh games (MH3U included) feature 'bloat values', which are multipliers to a player's attack, dependent on weapon type, intended to showcase how slower weapons such as GS or Hammer deal more damage per hit. As these values are visual-only, obscuring the real attack values without impacting gameplay, they tend to be disliked in the mh community. This patch forces all bloat values to 1x, so true attack is shown on all weapons.

## Adding new patches

Patches in patches.txt are separated by newlines, and sport the following fields:
- Name: The name by which the user is prompted to install the patch.
- Data: Hex data to write.
- Offsets: Offsets to which this data will be written, comma-separated.
- N_loops: Number of times the data will be written. Applies to all offsets specified.

As an example, the provided patch 'RawDebloater' will seek to offset 0x0017C9FC in the extracted rpx (referred to as 'code.bin' in this project). There, it will write 00000064 14 times; that is: 
> 0000006400000064000000640000006400000064000000640000006400000064000000640000006400000064000000640000006400000064

**Formatting**:  
Everything is written to patches.txt in plaintext, however, there are some considerations as to how each field is read:
- Name: What you write is what you get.
- Data: Every two characters represent a byte, big endian. For example, '1234' will write 0x12 0x34 to code.bin. Only hexadecimal characters are allowed here, with no specifiers (such as '0x', 'h').
- Offsets: Each offset is an integer value, read automatically according to content. '1234' will be taken as decimal, while 0x1234 will be taken as hexadecimal. Each offset is comma-separated, with no spaces in between. Offsets are relative to the extracted code.bin, not so the full game, which starts its code section at a given offset.
- N_Loops: Decimal integer value. Usually '1' for 'write once to each offset'. This field is only meant as a convenience for writing repetitive data.


## Building

Requires OpenSSL v1.1.1 (current version probably works, but is untested). Make sure to link it properly.
You will need the [wiiurpxtool](https://github.com/0CBH0/wiiurpxtool) executable at the same level as the patcher's when running.

## Special Thanks
CBH, for providing [wiiurpxtool](https://github.com/0CBH0/wiiurpxtool) under the GPLv3.

IncognitoMan, for pointing out how bloat values are stored in the game.
