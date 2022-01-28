# MH3U-WiiU-Patcher
Binary patcher for MH3U. Currently only supports replacement by means of patches.txt.

# Usage / Installation
Firstly, verify you have an EUR / PAL version of MH3U, complete with v32 update data.

If this update data is in the correct, extracted format, it should contain 3 folders: 'code', 'content', and 'meta'. Within code should be 'MH3G_Cafe_EU.rpx'.

Download the newest release of the patcher from releases on this page, extract, and drag MH3G_Cafe_EU.rpx into the patcher exe provided. You will then be prompted on which patches to apply.

The necessary version of MH3G_Cafe_EU.rpx has the MD5 hash 382289663eb3bf8a73884260690449d8

# Provided Patches

BaseDefTo1: Several mh games add a fixed amount of defense to the player regardless of armor. In MH3G, this is a flat +1 defense, as is the standard. In MH3U, however, this is a +50, likely intended to make the western localization more accessible by making it easier. This patch reduces that 50 defense down to 1, for parity with MH3G.

RawDebloater: Weapons in several mh games (MH3U included) feature 'bloat values', which are multipliers to a player's attack, dependent on weapon type, intended to showcase how slower weapons such as GS or Hammer deal more damage per hit. As these values are visual-only, obscuring the real attack values without impacting gameplay, they tend to be disliked in the mh community. This patch forces all bloat values to 1x, so true attack is shown on all weapons.

# Special Thanks
CBH, for providing [wiiurpxtool](https://github.com/0CBH0/wiiurpxtool) under the GPLv3.
IncognitoMan, for pointing out how bloat values are stored.
