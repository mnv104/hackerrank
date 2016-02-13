#include <string>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <stdint.h>
#include <cstdio>

using namespace std;

typedef uint64_t vmk_uint64;
typedef uint32_t vmk_uint32;

typedef std::pair<vmk_uint64, vmk_uint64> extentRange;

struct ExtentVal {
   std::vector<extentRange> v;
   ExtentVal() { }
   ExtentVal(vmk_uint64 start, vmk_uint64 count) {
      v.push_back(std::make_pair(start, count));
   }
   void addNewExtent(vmk_uint64 startOffset, vmk_uint32 length);
};

struct ExtentKey {
   bool isNFS;
   std::string deviceName;
   ExtentKey(bool _isNFS, const std::string &_deviceName) :
      isNFS(_isNFS), deviceName(_deviceName) { }
#if 0
   bool operator<(const ExtentKey &ek1) const {
      if (deviceName.length() < ek1.deviceName.length()) {
         return true;
      } else if (deviceName.length() > ek1.deviceName.length()) {
         return false;
      } else {
         return memcmp(deviceName.c_str(), ek1.deviceName.c_str(),
                       deviceName.length()) < 0;
      }
   }
#endif
};

struct ExtentKeyCompare {
   bool operator()(const ExtentKey &ek1, const ExtentKey &ek2) const {
      if (ek1.deviceName.length() < ek2.deviceName.length()) {
         return true;
      } else if (ek1.deviceName.length() > ek2.deviceName.length()) {
         return false;
      } else {
         return memcmp(ek1.deviceName.c_str(), ek2.deviceName.c_str(),
                       ek1.deviceName.length()) < 0;
      }
   }
};


std::map<ExtentKey, ExtentVal, ExtentKeyCompare> deviceMap;

/*
 * -------------------------------------------------------------
 * UtilExtentOverlap --
 *
 *          Determines if there are any overlaps between
 *          a pair of offset,count tuples.
 *
 * Parameters:
 *          "start1": Start offset of the first pair.
 *          "count1": Count/length of the first pair.
 *          "start2": Start offset of the second pair.
 *          "count2": Count/length of the second pair.
 *
 * Results:
 *          true if they overlap
 *          false if they don't.
 * -------------------------------------------------------------
 */

static inline bool
UtilExtentOverlap(vmk_uint64 start1,                      // IN
                      vmk_uint64 count1,                      // IN
                      vmk_uint64 start2,                      // IN
                      vmk_uint64 count2)                      // IN
{
   vmk_uint64 end1 = start1 + count1 - 1, end2 = start2 + count2 - 1;

   if (count1 == 0 || count2 == 0) {
      return false;
   }
   if ((start2 >= start1 && start2 <= end1) ||
       (start1 >= start2 && start1 <= end2)) {
       return true;
   }
   return false;
}


/*
 * -------------------------------------------------------------
 * UtilExtentDetermineOverlap --
 *
 *          Determines if there are any overlaps between
 *          a pair of offset,count tuples and if they do overlap
 *          it returns the overlapping range (overlap offset
 *          and count) as well as the minimum offset and maximum
 *          end of the pair.
 *
 * Parameters:
 *          "start1": Start offset of the first pair.
 *          "count1": Count/length of the first pair.
 *          "start2": Start offset of the second pair.
 *          "count2": Count/length of the second pair.
 *          "overlapStart": Overlapping start offset of the pair.
 *          "overlapCount": Overlapping count of the pair.
 *          "minStart": Minimum of the pair of start offsets.
 *          "maxEnd": Maximum end offset of the pair.
 *
 * Results:
 *          true if they overlap
 *          false if they don't.
 * -------------------------------------------------------------
 */

static inline bool
UtilExtentDetermineOverlap(vmk_uint64 start1,              // IN
                               vmk_uint64 count1,              // IN
                               vmk_uint64 start2,              // IN
                               vmk_uint64 count2,              // IN
                               vmk_uint64 *overlapStart,       // OUT
                               vmk_uint64 *overlapCount,       // OUT
                               vmk_uint64 *minStart,           // OUT
                               vmk_uint64 *maxEnd)             // OUT
{
   vmk_uint64 end1 = start1 + count1 - 1, end2 = start2 + count2 - 1;

   if (!UtilExtentOverlap(start1, count1, start2, count2)) {
      return false;
   }
   if (overlapStart) {
      *overlapStart = std::max(start1, start2);
   }
   if (overlapCount) {
      *overlapCount = std::min(end1, end2) - std::max(start1, start2) + 1;
   }
   if (minStart) {
      *minStart = std::min(start1, start2);
   }
   if (maxEnd) {
      *maxEnd = std::max(end1, end2);
   }
   return true;
}


/*
 * -------------------------------------------------------------
 * UtilExtentAdjacent --
 *
 *          Determines if the specified pair of tuples are adjacent.
 *
 * Parameters:
 *          "start1": Start offset of the first pair.
 *          "count1": Count/length of the first pair.
 *          "start2": Start offset of the second pair.
 *          "count2": Count/length of the second pair.
 *
 * Results:
 *          true if they are adjacent,
 *          false if they are not.
 * -------------------------------------------------------------
 */

static inline bool
UtilExtentAdjacent(vmk_uint64 start1,                      // IN
                       vmk_uint64 count1,                      // IN
                       vmk_uint64 start2,                      // IN
                       vmk_uint64 count2)                      // IN
{
   if (count1 == 0 || count2 == 0) {
      return false;
   }
   if ((start1 + count1 == start2) ||
       (start2 + count2 == start1)) {
      return true;
   }
   return false;
}


/*
 * -------------------------------------------------------------
 * UtilExtentWiden --
 *
 *          Determines the lowest offset and maximum length of
 *          an extent given a offset, count pair of tuples.
 *
 * Parameters:
 *          "start1": Start offset of the first pair.
 *          "count1": Count/length of the first pair.
 *          "start2": Start offset of the second pair.
 *          "count2": Count/length of the second pair.
 *          "start3": New widened start offset.
 *          "count3": New widened length.
 *
 * Results:
 *          true if they are overlapping,
 *          false if they are not.
 * -------------------------------------------------------------
 */

static inline bool
UtilExtentWiden(vmk_uint64 start1,                         // IN
                    vmk_uint64 count1,                         // IN
                    vmk_uint64 start2,                         // IN
                    vmk_uint64 count2,                         // IN
                    vmk_uint64 *start3,                        // OUT
                    vmk_uint64 *count3)                        // OUT
{
   vmk_uint64 overlapStart, overlapCount, minStart, maxEnd;

   if (!UtilExtentOverlap(start1, count1, start2, count2) &&
       !UtilExtentAdjacent(start1, count1, start2, count2)) {
      return false;
   }
   if (UtilExtentDetermineOverlap(start1, count1, start2, count2,
                                      &overlapStart, &overlapCount,
                                      &minStart, &maxEnd)) {
      *start3 = minStart;
      *count3 = maxEnd - minStart + 1;
   } else {
      *start3 = std::min(start1, start2);
      *count3 = count1 + count2;
   }
   return true;
}



void
ExtentVal::addNewExtent(vmk_uint64 startOffset, vmk_uint32 length)
{
   std::vector<extentRange>::iterator it = v.begin();
   while (it != v.end()) {
      extentRange &e = *it;
      vmk_uint64 newStart, newCount;
      if (UtilExtentWiden(e.first, e.second,
                          startOffset, length,
                          &newStart, &newCount)) {
          e.first = newStart;
          e.second = newCount;
          return;
      } else if (startOffset < e.first) {
         v.insert(it, std::make_pair(startOffset, length));
         return;
      }
      it++;
   }
   v.push_back(std::make_pair(startOffset, length));
}

struct ranges {
   vmk_uint64 startOffset;
   vmk_uint64 count;
};

int main()
{
   std::string deviceID("naa.947472943095874903049");
   ranges r[] = {{100, 10}, {200, 15}, {108, 10}, {140, 30}, {208, 20}, {70, 40}, {40, 40}, {0, 20}, {21, 10}};
   ExtentKey k(false, deviceID);
   for (unsigned int i = 0; i < sizeof(r)/sizeof(r[0]); i++) {
      try {
         ExtentVal &e = deviceMap.at(k);
         printf("Adding extent %lu: %lu\n", r[i].startOffset, r[i].count);
         e.addNewExtent(r[i].startOffset, r[i].count);
      } catch (const std::out_of_range &e) {
         printf("(1) Adding extent %lu: %lu\n", r[i].startOffset, r[i].count);
         //deviceMap.insert(std::pair<ExtentKey, ExtentVal>(k, ExtentVal(r[i].startOffset, r[i].count)));
         deviceMap[k] = ExtentVal(r[i].startOffset, r[i].count);
      }
   }
   std::map<ExtentKey, ExtentVal>::iterator it = deviceMap.begin();
   while (it != deviceMap.end()) {
      ExtentKey ek = (*it).first;
      ExtentVal ev = (*it).second;
      printf("Extent map on %s device %s\n", ek.isNFS ? "NFS" : "VMFS",
               ek.isNFS ? "" : ek.deviceName.c_str());
      std::vector<extentRange>::iterator it2 = ev.v.begin();
      while (it2 != ev.v.end()) {
         extentRange &er = *it2;
         printf("%lu: %lu\n", er.first, er.second);
         it2++;
      }
      it++;
   }

   return 0;
}
