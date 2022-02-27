// 1.0.0

#include "Arduino.h"
#include "rz_version.h"

#include <string>
#include <cstdio>
using namespace std;

// thanks to Pankaj Choudhary
struct Version
{
   private:
   // Define four member variables major, minor, revision and build.
   // Here, we are saying it as version-tag
   int major, minor, revision, build;

   public:
   // Parametarized constructor. Pass string to it and it will
   // extract version-tag from it.
   //
   // Use initializer list to assign version-tag variables
   // Assign it by zero, otherwise std::scanf() will assign
   // garbage value to the versio-tag, if number of version-tag
   // will be less than four.
   Version(const std::string& version)
      : major(0), minor(0), revision(0), build(0)
   {
      std::sscanf(version.c_str(), "%d.%d.%d.%d", &major, &minor, &revision, &build);

      // version-tag must be >=0, if it is less than zero, then make it zero.
      if (major < 0) major = 0;
      if (minor < 0) minor = 0;
      if (revision < 0) revision = 0;
      if (build < 0) build = 0;
   }

   // Overload greater than(>) operator to compare two version objects
   bool operator > (const Version& other)
   {
      // Start comparing version tag from left most.
      // There are three relation between two number. It could be >, < or ==
      // While comparing the version tag, if they are equal, then move to the
      // next version-tag. If it could be greater then return true otherwise
      // return false.

      // Compare major version-tag
      if (major > other.major)
         return true;
      else if (major < other.major)
         return false;

      // Compare minor version-tag
      // If control came here it means that above version-tag(s) are equal
      if (minor > other.minor)
         return true;
      else if (minor < other.minor)
         return false;

      // Compare revision version-tag
      // If control came here it means that above version-tag(s) are equal
      if (revision > other.revision)
         return true;
      else if(revision < other.revision)
         return false;

      // Compare build version-tag
      // If control came here it means that above version-tag(s) are equal
      if (build > other.build)
         return true;
      else if(build < other.build)
         return false;

      return false;
   }

   // Overload equal to(==) operator to compare two version
   bool operator == (const Version& other)
   {
      return major == other.major 
         && minor == other.minor 
         && revision == other.revision 
         && build == other.build;
   }
};

RZ_Version::RZ_Version() {
  // Serial.println("RZ_Version::RZ_Version");
  _updateVersion = "0";
}

int RZ_Version::checkVersions(std::string str_v1, std::string str_v2) {
  Version v1(str_v1);
  Version v2(str_v2);
  if(v1 == v2) {
    //Serial.println("-- current version is up to date");
    return 0;
  } else if(v1 > v2) {
    //Serial.println("-- current version is greater than Github version. Pls check");
    return 1;
  } else {
    //Serial.println("-- a new Firmware is available on Github https://github.com/Zheng-Bote/esp32_dht_webserver_mqtt-client");
    return 2;
  }
  return 255;
}

void RZ_Version::setUpdateVersion(std::string v2) {
  _updateVersion = v2;
}

std::string RZ_Version::getUpdateVersion() {
  return _updateVersion;
}
