#include <iostream>
#include <string.h>
#include <iostream>

using namespace std;


typedef struct {
    double lng;
    double lat;
} Location;

int main()
{

    char  input[] = "29.212143   119.471453  5.0    2016-10-23 16:11:27";
//  <trkpt lat="29.213713" lon="119.472105"><ele></ele><speed>1</speed><time>2016-12-02T08:18:18</time></trkpt>

    double  lat, lon, speed;
    char date[32], time[32];

    sscanf(input, "%lf %lf %lf %s %s",  &lat, &lon, &speed, date, time);

    /*
        坐标转换 ， 速度 转换 ，时间 本地转 UTC

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


    Location gps = { 119.465265, 29.1934702};
    gps = transformFromGCJToWGS(gps);
    */



    Location gps;
    gps.lat = lat;
    gps.lng = lon;
//   gps = transformFromGCJToWGS(gps);

    speed = speed / 3.6;

    cout << gps.lat << "\t" <<  gps.lng  << "\t" << speed << "\t" << date << "T" << time << "Z" << endl;

    return 0;
}



