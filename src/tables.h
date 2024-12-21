#pragma once

#include "types.h"

char* ver_strings [NUM_VERSIONS] = {
	"21:44:29 Sep 23 2000",
	"18:03:05 Mar 19 2003", // All the copies of Xmas 0.96 I could find have this. Weird.
	"14:46:55 Nov  8 2000",
	"13:19:30 Mar  1 2001",
	"18:46:34 Jun 20 2001",
	"10:18:27 Dec 25 2001",
	"13:59:06 Jan  6 2002",
	"20:59:16 Mar  8 2002",
	"19:31:11 Mar 18 2002",
	"16:45:04 Mar 10 2003",
	"!", // fd 1.01
	"%", // fd 1.02
	"13:58:48 Jun 19 2003", // fd 1.03
	"20:10:23 Jun 21 2003", // fd 1.04
	"10:38:20 Jan  2 2004",
	"21:50:26 Sep 11 2005",
	"13:30:06 Jan  7 2006",
	"Aug 22 2006",
	"Feb 17 2008",
	"srb2fun Beta Mar  2 2008",
	"v1.1 Private Beta Aug 22 2008",
	"v1.1 Private Beta Sep 24 2008"
};

char* ver_names [NUM_VERSIONS] = {
	"Halloween 1.32",
	"Xmas 0.96", // All the copies of Xmas 0.96 I could find have this. Weird.
	"Demo 1",
	"Demo 2",
	"Demo 3",
	"Demo 4",
	"Demo 4.1",
	"Demo 4.32",
	"Demo 4.35",
	"Tournament 2003",
	"Final Demo 1.01", // fd 1.01
	"Final Demo 1.02", // fd 1.02
	"Final Demo 1.03", // fd 1.03
	"Final Demo 1.04", // fd 1.04
	"Final Demo 1.08",
	"Final Demo 1.09",
	"Final Demo 1.09.2",
	"Final Demo 1.09.4",
	"Final Demo 1.09.4a",
	"IRC Match Beta",
	"Aug 22 2008 1.1 Prototype",
	"Sep 24 2008 1.1 Prototype"
};
	
uint32 ver_addresses [NUM_VERSIONS] [2] = {
	{0x06DB5F, 0x06DB72},
	{0x071917, 0x07192A},
	{0x073D33, 0x073D46},
	{0x07CBE7, 0x07CBFA},
	{0x07ACCF, 0x07ACE2},
	{0x07AEEF, 0x07AF02},
	{0x07AEEF, 0x07AF02},
	{0x090264, 0x090277}, // jump from legacy 1.30 to 1.32
	{0x08F268, 0x08F27B},
	{0x095CC8, 0x095CDB},
	{0x091991, 0x091991}, // fd 1.01
	{0x091991, 0x091991}, // fd 1.02
	{0x09FE38, 0x09FE4B},
	{0x09FE40, 0x09FE53},
	{0x0AA3F0, 0x0AA403},
	{0x0A4614, 0x0A4627},
	{0x0A6798, 0x0A67AB}, // fd 1.09.2
	{0x0C25D8, 0x0C25E2}, 
	{0x0C6558, 0x0C6562}, 
	{0x0E6040, 0x0E6057}, 
	{0x14AD27, 0x14AD43}, // debuggggg aug 2008
	{0x0E830A, 0x0E6327}, // sep 2008
};