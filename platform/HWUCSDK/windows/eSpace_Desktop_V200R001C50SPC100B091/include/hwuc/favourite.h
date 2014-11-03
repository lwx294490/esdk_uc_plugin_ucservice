/******************************************************************************
* Huawei Enterprise Communication API
* favourite.h
* Author :  Huawei
* Description :  My Favourites related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2012-9-04 1.00  First version
******************************************************************************/
#pragma  once

namespace uc {
  namespace model {

/**
* \brief FavouriteType
* \note The FavouriteType enum represents type of favourite
* \author  c00161520
* \version 1.0.0  initial version
*/
enum FavouriteType
{
  FAV_CONTACT,    //<! favourite contact; content is uri
  FAV_FIXEDGROUP, //<! favourite fixed group; content group id
  FAV_TEMPGROUP,  //<! favourite temp group; content is like <group id>:<uri>;<uri>...
  FAV_MEETING,    //<! favourite meeting; content is meeting id
};

/**
* \brief Favourite
* \note The Favourite struct is an item of favourite
* \author  c00161520
* \version 1.0.0  initial version
*/
struct APPCLASSLAYER_API Favourite
{
  std::string id_;      //<! favourite id
  int type_;            //<! favourite type
  std::string content;  //<! facourite content; format is determined by type_

  Favourite() : type_(-1) {}

};

/**
* \brief FavouriteMgr
* \note The FavouriteMgr class is responsible for management of my favourite.
* \author  c00161520
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API FavouriteMgr
{
public:
    virtual ~FavouriteMgr(){}
  virtual bool GetFavouriteById(Favourite & favourate, const std::string & id) = 0;
  virtual int GetFavouriteList(std::vector<Favourite> & favourites) = 0;
  virtual bool AddFavourite(Favourite & favourite) = 0;
  virtual bool RemoveFavourite(const std::string & id) = 0;
  virtual bool ModifyFavouriteContent(const Favourite & favourite) = 0;
  virtual bool FindFavouriteByTypeAndContentPrefix(
    Favourite & favourite, int favType, const std::string & pref) = 0;

};

  }
}
