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

    puts("地球WGS-84 转 火星GCJ-02 转  百度BD-09");

    Location gps = { 119.465265, 29.1934702};
    cout << setprecision(9) << "地球WGS-84: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromWGSToGCJ(gps);
    cout << "火星GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_encrypt(gps);
    cout << "百度 BD-09: "  << gps.lat << "  " << gps.lng << endl;

    cout << endl << endl;



    puts("百度BD-09  转 火星GCJ-02 转  地球WGS-84");

    gps = { 119.476936, 29.196518};
    cout << "百度 BD-09: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_decrypt(gps);
    cout << "火星GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromGCJToWGS(gps);
    cout << "地球WGS-84: "  << gps.lat << "  " << gps.lng << endl;




    return 0;
}
