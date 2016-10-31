<<<<<<< HEAD
C/C++  π”√ChinaMapShiftø‚ ≤‚ ‘ª•◊™: µÿ«ÚWGS-84 ª–«GCJ-02 ∞Ÿ∂»BD-09


**÷ÿµ„ƒ⁄»›**±ÿ”¶-÷–π˙µÿÕº ≤…”√µƒ «ª–«◊¯±Í
http://cn.bing.com/ditu/
	
	**÷ÿµ„ƒ⁄»›**NMEA Tools ≤…ºØµƒ∂»∑÷∏Ò Ω“™œ»◊™≥…–° ˝∏Ò Ω
	**÷ÿµ„ƒ⁄»›**‘Ÿ◊™≥…ª–«◊¯±Í£¨≤≈ƒ‹‘⁄÷–π˙µÿÕº…œ∂‘”¶°£
À„∑®ø‚÷ªƒ‹◊‘º∫œ¬‘ÿ¡À	
https://github.com/Dronaldo17/ChinaMapShift
	Algorithm for the map offset problem in China. 
	**÷ÿµ„ƒ⁄»›**Ω‚æˆ÷–π˙µÿÕº∆´“∆Œ Ã‚µƒÀ„∑®°£
	
![±ÿ”¶-÷–π˙µÿÕº ≤…”√µƒ «ª–«◊¯±Í](https://github.com/hongwenjun/nmea_gprmc/blob/master/WGS2GCJ/WGS2GCJ.png) 

***
≤‚ ‘¥˙¬Î
```
#include <iostream>
#include <string>
#include <stdio.h>
#include "china_shift.h"
#include <iomanip>

// Transform WGS-84 to GCJ-02 (Chinese encrypted coordination system)

//    typedef struct {
//        double lng;
//        double lat;
//    } Location;
//
//    Location transformFromWGSToGCJ(Location wgLoc);
//    Location transformFromGCJToWGS(Location gcLoc);
//    Location bd_encrypt(Location gcLoc);
//    Location bd_decrypt(Location bdLoc);


using namespace std;

int main()
{

    puts("µÿ«ÚWGS-84 ◊™ ª–«GCJ-02 ◊™  ∞Ÿ∂»BD-09");

    Location gps = { 119.465265, 29.1934702};
    cout << setprecision(9) << "µÿ«ÚWGS-84: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromWGSToGCJ(gps);
    cout << "ª–«GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_encrypt(gps);
    cout << "∞Ÿ∂» BD-09: "  << gps.lat << "  " << gps.lng << endl;

    cout << endl << endl;



    puts("∞Ÿ∂»BD-09  ◊™ ª–«GCJ-02 ◊™  µÿ«ÚWGS-84");

    gps = { 119.476936, 29.196518};
    cout << "∞Ÿ∂» BD-09: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_decrypt(gps);
    cout << "ª–«GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromGCJToWGS(gps);
    cout << "µÿ«ÚWGS-84: "  << gps.lat << "  " << gps.lng << endl;

    return 0;
}


```
***
```
µÿ«ÚWGS-84 ◊™ ª–«GCJ-02 ◊™  ∞Ÿ∂»BD-09
µÿ«ÚWGS-84: 29.1934702  119.465265
ª–«GCJ-02: 29.1908196  119.470341
∞Ÿ∂» BD-09: 29.1965172  119.476936


∞Ÿ∂»BD-09  ◊™ ª–«GCJ-02 ◊™  µÿ«ÚWGS-84
∞Ÿ∂» BD-09: 29.196518  119.476936
ª–«GCJ-02: 29.1908195  119.470342
µÿ«ÚWGS-84: 29.1934702  119.465265

“‘…œ « ‰≥ˆΩ·π˚£¨ π”√∞Ÿ∂»APIµÿÕº»°µƒµ„£¨ƒ‹◊™µΩWGS-84◊¯±Í£¨‘⁄ maps.google.com…œµÿÕº∂‘”¶°£ 
GoogleµÿÕº÷–π˙∞Ê£¨∑Ω±„∞— ‰»Îº∏∏ˆª–«◊¯±Í£¨Õ®π˝»Áœ¬∑Ω Ω¡¨Ω”∆¿¥£¨%09 «◊™“Â∑˚
http://www.google.cn/maps/dir/29.1934702%09119.465265/29.1908196%09119.470341/29.1965172%09119.476936/

```
œ‡πÿ¡¥Ω”
https://github.com/hongwenjun/nmea_gprmc
https://github.com/hongwenjun/TrajectoryCombine

 
=======
#C/C++ ‰ΩøÁî®ChinaMapShiftÂ∫ì ÊµãËØï‰∫íËΩ¨: Âú∞ÁêÉWGS-84 ÁÅ´ÊòüGCJ-02 ÁôæÂ∫¶BD-09


**ÈáçÁÇπÂÜÖÂÆπ**ÂøÖÂ∫î-‰∏≠ÂõΩÂú∞Âõæ ÈááÁî®ÁöÑÊòØÁÅ´ÊòüÂùêÊ†á
	http://cn.bing.com/ditu/
	
**ÈáçÁÇπÂÜÖÂÆπ**NMEA Tools ÈááÈõÜÁöÑÂ∫¶ÂàÜÊ†ºÂºèË¶ÅÂÖàËΩ¨ÊàêÂ∞èÊï∞Ê†ºÂºè
**ÈáçÁÇπÂÜÖÂÆπ**ÂÜçËΩ¨ÊàêÁÅ´ÊòüÂùêÊ†áÔºåÊâçËÉΩÂú®‰∏≠ÂõΩÂú∞Âõæ‰∏äÂØπÂ∫î„ÄÇ
	ÁÆóÊ≥ïÂ∫ìÂè™ËÉΩËá™Â∑±‰∏ãËΩΩ‰∫Ü	
	https://github.com/Dronaldo17/ChinaMapShift

	Algorithm for the map offset problem in China. 
**ÈáçÁÇπÂÜÖÂÆπ**Ëß£ÂÜ≥‰∏≠ÂõΩÂú∞ÂõæÂÅèÁßªÈóÆÈ¢òÁöÑÁÆóÊ≥ï„ÄÇ
	
![ÂøÖÂ∫î-‰∏≠ÂõΩÂú∞Âõæ ÈááÁî®ÁöÑÊòØÁÅ´ÊòüÂùêÊ†á](https://github.com/hongwenjun/nmea_gprmc/blob/master/WGS2GCJ/WGS2GCJ.png) 

***
ÊµãËØï‰ª£Á†Å
```
#include <iostream>
#include <string>
#include <stdio.h>
#include "china_shift.h"
#include <iomanip>

// Transform WGS-84 to GCJ-02 (Chinese encrypted coordination system)

//    typedef struct {
//        double lng;
//        double lat;
//    } Location;
//
//    Location transformFromWGSToGCJ(Location wgLoc);
//    Location transformFromGCJToWGS(Location gcLoc);
//    Location bd_encrypt(Location gcLoc);
//    Location bd_decrypt(Location bdLoc);


using namespace std;

int main()
{

    puts("Âú∞ÁêÉWGS-84 ËΩ¨ ÁÅ´ÊòüGCJ-02 ËΩ¨  ÁôæÂ∫¶BD-09");

    Location gps = { 119.465265, 29.1934702};
    cout << setprecision(9) << "Âú∞ÁêÉWGS-84: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromWGSToGCJ(gps);
    cout << "ÁÅ´ÊòüGCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_encrypt(gps);
    cout << "ÁôæÂ∫¶ BD-09: "  << gps.lat << "  " << gps.lng << endl;

    cout << endl << endl;



    puts("ÁôæÂ∫¶BD-09  ËΩ¨ ÁÅ´ÊòüGCJ-02 ËΩ¨  Âú∞ÁêÉWGS-84");

    gps = { 119.476936, 29.196518};
    cout << "ÁôæÂ∫¶ BD-09: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_decrypt(gps);
    cout << "ÁÅ´ÊòüGCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromGCJToWGS(gps);
    cout << "Âú∞ÁêÉWGS-84: "  << gps.lat << "  " << gps.lng << endl;

    return 0;
}


```
***
```
Âú∞ÁêÉWGS-84 ËΩ¨ ÁÅ´ÊòüGCJ-02 ËΩ¨  ÁôæÂ∫¶BD-09
Âú∞ÁêÉWGS-84: 29.1934702  119.465265
ÁÅ´ÊòüGCJ-02: 29.1908196  119.470341
ÁôæÂ∫¶ BD-09: 29.1965172  119.476936


ÁôæÂ∫¶BD-09  ËΩ¨ ÁÅ´ÊòüGCJ-02 ËΩ¨  Âú∞ÁêÉWGS-84
ÁôæÂ∫¶ BD-09: 29.196518  119.476936
ÁÅ´ÊòüGCJ-02: 29.1908195  119.470342
Âú∞ÁêÉWGS-84: 29.1934702  119.465265

‰ª•‰∏äÊòØËæìÂá∫ÁªìÊûúÔºå‰ΩøÁî®ÁôæÂ∫¶APIÂú∞ÂõæÂèñÁöÑÁÇπÔºåËÉΩËΩ¨Âà∞WGS-84ÂùêÊ†áÔºåÂú® maps.google.com‰∏äÂú∞ÂõæÂØπÂ∫î„ÄÇ 
GoogleÂú∞Âõæ‰∏≠ÂõΩÁâàÔºåÊñπ‰æøÊääËæìÂÖ•Âá†‰∏™ÁÅ´ÊòüÂùêÊ†áÔºåÈÄöËøáÂ¶Ç‰∏ãÊñπÂºèËøûÊé•Ëµ∑Êù•Ôºå%09ÊòØËΩ¨‰πâÁ¨¶
http://www.google.cn/maps/dir/29.1934702%09119.465265/29.1908196%09119.470341/29.1965172%09119.476936/

```
	Áõ∏ÂÖ≥ÈìæÊé•
	https://github.com/hongwenjun/nmea_gprmc
	
	https://github.com/hongwenjun/TrajectoryCombine

 
>>>>>>> a283afdc88a6d5e5feb97cbdd1c97c4304217d55
