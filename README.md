# StringReaper

> A lightweight C++ tool for extracting and analyzing raw strings from binary files.  
> Designed for reverse engineers, malware analysts, and curious hackers.

---

##  Overview

`StringReaper` dives into binary files and pulls out printable ASCII strings
It scans for:

 **Base64 payloads**
 **Hex-encoded strings**
 **Hidden URLs & secrets**

Use it to:
 Uncover malware commands
 Decode embedded payloads
 Find suspicious patterns

---

## Build Instructions

> Requires a C++ compiler

```bash
git clone https://github.com/spatxz/StringReaper.git
cd StringReaper/src
g++ stringreaper.cpp -o stringreaper
