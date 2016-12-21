#include "stdafx.h"
#include "SkinC.h"
//100% paste

SkinC::SkinC()
{
}


SkinC::~SkinC()
{
}
/*
bool SkinC::Load(const std::string& gamePath, const std::string& gameShortName)
{

	_items_game = new File::Valve::CConfig();
	if (!_items_game->Load(gamePath + "/scripts/items/items_game.txt", false))
		return false;

	_csgo_english = new File::Valve::CConfig();
	if (!_csgo_english->Load(gamePath + "/resource/" + gameShortName + "_english.txt", true))
		return false;

	const File::Valve::mapLevel& Items = _items_game->GetLevel()->GetSubLevels().at("items")->GetSubLevels();
	const File::Valve::mapLevel& Prefabs = _items_game->GetLevel()->GetSubLevels().at("prefabs")->GetSubLevels();

	std::vector<WeaponInfo_t> vWeapons;
	for (auto& Item : Items)
	{
		const std::string& Name = Item.second->GetVariables().at("name");
		if (Name.find("weapon_") == std::string::npos)
			continue;

		const std::string& Prefab = Item.second->GetVariables().at("prefab");
		if (Prefab == "melee_unusual")
		{
			std::string szWeaponName;
			if (!bTranslate(Item.second->GetVariables().at("item_name"), szWeaponName))
				continue;

			std::string szWorldModel = Item.second->GetVariables().at("model_world");
			std::string szDroppedModel = szWorldModel;

			size_t FindResult = szDroppedModel.find(".mdl");
			if (FindResult != std::string::npos)
				szDroppedModel.replace(FindResult, 4, "_dropped.mdl");

			WeaponInfo_t WeaponInfo;
			WeaponInfo.bIsKnife = true;
			WeaponInfo.iWeaponID = (unsigned int)atoi(Item.first.c_str());
			WeaponInfo.szShortWeaponName = Name;
			WeaponInfo.szWeaponName = szWeaponName;
			WeaponInfo.szViewModel = Item.second->GetVariables().at("model_player");
			WeaponInfo.szWorldModel = szWorldModel;
			WeaponInfo.szDroppedModel = szDroppedModel;

			vWeapons.push_back(WeaponInfo);
		}
		else
		{
			if (Prefab != Name + "_prefab")
				continue;

			if (Item.second->GetVariables().at("item_sub_position").find("grenade") != std::string::npos)
				continue;

			std::string szWeaponName;
			if (!bTranslate(Prefabs.at(Prefab)->GetVariables().at("item_name"), szWeaponName))
				continue;

			std::string szWorldModel = Prefabs.at(Prefab)->GetVariables().at("model_world");
			std::string szDroppedModel = szWorldModel;

			size_t FindResult = szDroppedModel.find(".mdl");
			if (FindResult != std::string::npos)
				szDroppedModel.replace(FindResult, 4, "_dropped.mdl");

			WeaponInfo_t WeaponInfo;
			WeaponInfo.bIsKnife = false;
			WeaponInfo.iWeaponID = (unsigned int)atoi(Item.first.c_str());
			WeaponInfo.szShortWeaponName = Name;
			WeaponInfo.szWeaponName = szWeaponName;
			WeaponInfo.szViewModel = Prefabs.at(Prefab)->GetVariables().at("model_player");
			WeaponInfo.szWorldModel = szWorldModel;
			WeaponInfo.szDroppedModel = szDroppedModel;

			vWeapons.push_back(WeaponInfo);
		}
	}

	const File::Valve::mapLevel WeaponIcons = _items_game->GetLevel()->GetSubLevels().at("alternate_icons2")->GetSubLevels().at("weapon_icons")->GetSubLevels();
	const File::Valve::mapLevel ItemSets = _items_game->GetLevel()->GetSubLevels().at("item_sets")->GetSubLevels();

	for (auto& PaintKit : _items_game->GetLevel()->GetSubLevels().at("paint_kits")->GetSubLevels())
	{
		const std::string& PaintKitID = PaintKit.first;
		if (PaintKitID == "9001")
			continue;

		std::string DescriptionTag = PaintKit.second->GetVariables().at("description_tag");
		std::string PaintTranslatedKitName;
		if (!bTranslate(DescriptionTag, PaintTranslatedKitName))
		{
			DescriptionTag[6] = 'k'; // volvo pls get ur shit together 
			if (!bTranslate(DescriptionTag, PaintTranslatedKitName))
				continue;
		}

		if (PaintTranslatedKitName == "-")
			continue;

		const std::string& PaintKitName = PaintKit.second->GetVariables().at("name");

		for (auto& ItemSet : ItemSets)
		{
			for (auto& Item : ItemSet.second->GetSubLevels().at("items")->GetVariables())
			{
				std::string Weapon = Item.first;
				if (Weapon.find(PaintKitName + "]") == std::string::npos)
					continue;

				size_t FindResult = Weapon.find("]");
				if (FindResult == std::string::npos)
					continue;

				Weapon = Weapon.substr(FindResult + 1);

				int iSize = vWeapons.size();
				for (int i = 0; i < iSize; ++i)
				{
					if (vWeapons[i].szShortWeaponName == Weapon)
					{
						SkinInfo_t SkinInfo;
						SkinInfo.iSkinID = (unsigned int)atoi(PaintKitID.c_str());
						SkinInfo.szShortSkinName = PaintKitName;
						SkinInfo.szSkinName = PaintTranslatedKitName;

						_skininfo[vWeapons[i]].push_back(SkinInfo);

						std::sort(_skininfo[vWeapons[i]].begin(), _skininfo[vWeapons[i]].end(), CompareSkinInfo);

						break;
					}
				}
			}
		}

		for (auto& WeaponIcon : WeaponIcons)
		{
			const std::string& IconPath = WeaponIcon.second->GetVariables().at("icon_path");
			if (IconPath[IconPath.size() - 7] != '_')
				continue;

			size_t FindResult = IconPath.find(PaintKitName + "_medium");
			if (FindResult == std::string::npos)
				continue;

			std::string Weapon = IconPath.substr(23, FindResult - 24);

			int iSize = vWeapons.size();
			for (int i = 0; i < iSize; ++i)
			{
				if ((vWeapons[i].bIsKnife || PaintKitName == "cu_m4a1_howling" ) && vWeapons[i].szShortWeaponName == Weapon)
				{
					SkinInfo_t SkinInfo;
					SkinInfo.iSkinID = (unsigned int)atoi(PaintKitID.c_str());
					SkinInfo.szShortSkinName = PaintKitName;
					SkinInfo.szSkinName = PaintTranslatedKitName;

					_skininfo[vWeapons[i]].push_back(SkinInfo);

					std::sort(_skininfo[vWeapons[i]].begin(), _skininfo[vWeapons[i]].end(), CompareSkinInfo);

					break;
				}
			}
		}
	}

	return true;
}*/
