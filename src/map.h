#ifndef _MAP_H
#define _MAP_H

#include <map>
#include <ctime>
#include "nbt.h"
#include "user.h"

struct spawnedItem
{
  int EID;
  int item;
  char count;
  sint16 health;
  int x;
  int y;
  int z;
  time_t spawnedAt;
  uint32 spawnedBy;

  spawnedItem()
  {
    spawnedAt=time(0);
    spawnedBy=0;
  }
};

class Map
{
private:

  Map()
  {
    for(int i=0;i<256;i++) emitLight[i]=0;
    emitLight[0x0A] = 15; // Lava
    emitLight[0x0B] = 15; // Stationary Lava
    emitLight[0x27] = 1;  // Brown mushroom
    emitLight[0x32] = 14; // Torch
    emitLight[0x33] = 15; // Fire
    emitLight[0x3E] = 14; // Lit furnace
    emitLight[0x4A] = 9;  // Redstone ore (Glowing)
    emitLight[0x4C] = 7;  // Redstone Torch (On)
    emitLight[0x59] = 15; // Lightstone
    emitLight[0x5A] = 11; // Portal
    emitLight[0x5B] = 15; // Jack-O-Lantern
    

    for(int i=0;i<256;i++) stopLight[i]=-16;
    stopLight[0x00] = 0; // Empty
    stopLight[0x06] = 0; // Sapling
    stopLight[0x08] =-3; // Water
    stopLight[0x09] =-3; // Stationary water
    stopLight[0x12] =-3; // Leaves
    stopLight[0x14] = 0; // Glass
    stopLight[0x25] = 0; // Yellow flower
    stopLight[0x26] = 0; // Red rose
    stopLight[0x27] = 0; // Brown mushroom
    stopLight[0x28] = 0; // Red mushroom
    stopLight[0x32] = 0; // Torch
    stopLight[0x33] = 0; // Fire
    stopLight[0x34] = 0; // Mob spawner
    stopLight[0x37] = 0; // Redstone wire
    stopLight[0x40] = 0; // Wooden door
    stopLight[0x41] = 0; // Ladder
    stopLight[0x42] = 0; // Minecart track
    stopLight[0x47] = 0; // Iron door
    stopLight[0x4b] = 0; // Redstone Torch (Off)
    stopLight[0x4C] = 0; // Redstone Torch (On)
    stopLight[0x4e] = 0; // Snow
    stopLight[0x4f] =-3; // Ice    
    stopLight[0x55] = 0; // Fence
    stopLight[0x5A] = 0; // Portal
    stopLight[0x5B] = 0; // Jack-O-Lantern
  };
  ~Map()
  {
    // Free all memory
    for (std::map<uint32, NBT_struct>::const_iterator it = maps.begin(); it != maps.end(); ++it)
    {
      releaseMap(maps[it->first].x, maps[it->first].z);
    }

    //Free item memory
    for (std::map<uint32, spawnedItem*>::const_iterator it = items.begin(); it != items.end(); ++it)
    {
      delete items[it->first];
    }

    // Free level.dat info
    freeNBT_struct(&levelInfo);
  };

  

public:

  std::string mapDirectory;

  // Map spawn position
  coord spawnPos;

  // for level.dat file
  NBT_struct levelInfo;

  // How blocks affect light
  int stopLight[256];

  // Blocks that emit light
  int emitLight[256];

  // Store all maps here
  std::map<uint32, NBT_struct> maps;

  // Store the time map chunk has been last used
  std::map<uint32, int> mapLastused;

  // Store if map has been modified
  std::map<uint32, bool> mapChanged;

  // Store item pointers for each chunk
  std::map<uint32, std::vector<spawnedItem *> > mapItems;

  //All spawned items on map
  std::map<uint32,spawnedItem *> items;

  void posToId(int x, int z, uint32 *id);
  void idToPos(uint32 id, int *x, int *z);

  void initMap();
  void freeMap();
  void sendToUser(User *user, int x, int z);

  // Get pointer to struct
  NBT_struct *getMapData(int x, int z);

  // Load map chunk
  bool loadMap(int x,int z);

   // Save map chunk to disc
  bool saveMap(int x,int z);

  // Save whole map to disc (/save command)
  bool saveWholeMap();

  // Generate light maps for chunk
  bool generateLightMaps(int x, int z);

  // Release/save map chunk
  bool releaseMap(int x, int z);

  // Light get/set
  bool getBlockLight(int x, int y, int z, uint8 *blocklight, uint8 *skylight);
  bool setBlockLight(int x, int y, int z, uint8 blocklight, uint8 skylight, uint8 setLight);
  bool lightmapStep(int x, int y, int z, int light);
  bool blocklightmapStep(int x, int y, int z, int light);

  // Block value/meta get/set
  bool getBlock(int x, int y, int z, uint8 *type, uint8 *meta);
  bool setBlock(int x, int y, int z, char type, char meta);

  bool sendBlockChange(int x, int y, int z, char type, char meta);

  bool sendPickupSpawn(spawnedItem item);  

  static Map &get();
};

#endif
