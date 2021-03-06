﻿#include <string>
#include <map>

#include "constants.h"

std::map<std::string, std::string> defaultConf;
std::map<uint8, Drop> BLOCKDROPS;

void initConstants()
{
  // Init configuration
  defaultConf.insert(std::pair<std::string, std::string>("port", "25565"));
  defaultConf.insert(std::pair<std::string, std::string>("servername", "Minecraft server"));
  defaultConf.insert(std::pair<std::string, std::string>("mapdir", "testmap"));
  defaultConf.insert(std::pair<std::string, std::string>("userlimit", "20"));
  defaultConf.insert(std::pair<std::string, std::string>("map_release_time", "10"));
  defaultConf.insert(std::pair<std::string, std::string>("server_full_message", "Server is currently full"));
  defaultConf.insert(std::pair<std::string, std::string>("default_kick_message", "You have been kicked"));
  defaultConf.insert(std::pair<std::string, std::string>("wrong_protocol_message", "Wrong client protocol"));

  // Block drops (10000 = 100%)
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_STONE, Drop(BLOCK_COBBLESTONE, 10000, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_GRASS, Drop(BLOCK_DIRT, 10000, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_GRAVEL, Drop(ITEM_FLINT, 850, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_COAL_ORE, Drop(ITEM_COAL, 10000, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_LEAVES, Drop(BLOCK_SAPLING, 1200, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_DIAMOND_ORE, Drop(ITEM_DIAMOND, 10000, 1)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_REDSTONE_ORE, Drop(ITEM_REDSTONE, 10000, 4)));
  
  // Blocks that drop nothing
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_TNT, Drop(BLOCK_TNT, 10000, 0)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_GLASS, Drop(BLOCK_GLASS, 10000, 0)));
  BLOCKDROPS.insert(std::pair<uint8, Drop>(BLOCK_MOB_SPAWNER, Drop(BLOCK_MOB_SPAWNER, 10000, 0)));

}