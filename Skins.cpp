#include "Skins.h"
RecvVarProxyFn fnSequenceProxyFn = NULL;

std::unordered_map<int, SkinStruct>  g_SkinCFG;
std::unordered_map<int, const char*> g_ViewModelCFG;
std::unordered_map<const char*, const char*> g_KillIconCfg;

void SetSkinCFG() {
	// StatTrak™ AWP | Dragon Lore
	g_SkinCFG[WEAPON_AWP].nFallbackPaintKit = 344;
	g_SkinCFG[WEAPON_AWP].flFallbackWear = 0.00000001f;
	g_SkinCFG[WEAPON_AWP].nFallbackStatTrak = 1337;

	// Valve AK-47 | Redline
	g_SkinCFG[WEAPON_AK47].nFallbackPaintKit = 282;
	g_SkinCFG[WEAPON_AK47].nEntityQuality = 6;

	// Souvenir M4A4 | Howl
	g_SkinCFG[WEAPON_M4A1].nFallbackPaintKit = 309;
	g_SkinCFG[WEAPON_M4A1].nEntityQuality = 12;

	// Prototype Desert Eagle | Conspiracy
	g_SkinCFG[WEAPON_DEAGLE].nFallbackPaintKit = 351;
	g_SkinCFG[WEAPON_DEAGLE].nEntityQuality = 7;

	// Glock-18 | Fade
	g_SkinCFG[WEAPON_GLOCK].nFallbackPaintKit = 38;

	// USP-S | Stainless
	g_SkinCFG[WEAPON_USPS].nFallbackPaintKit = 277;

	// Karambit | Fade (CT)
	g_SkinCFG[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_KARAMBIT;
	g_SkinCFG[WEAPON_KNIFE].nFallbackPaintKit = 38;
	g_SkinCFG[WEAPON_KNIFE].nEntityQuality = 3;

	// Bowie Knife | Crimson Web (T)
	g_SkinCFG[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_SURVIVAL_BOWIE;
	g_SkinCFG[WEAPON_KNIFE_T].nFallbackPaintKit = 12;
	g_SkinCFG[WEAPON_KNIFE_T].nEntityQuality = 3;
}

void SetViewModelCFG() {
	// Get the indexes of the models we want to replace.
	int nOriginalKnifeCT = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	int nOriginalKnifeT = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");

	// Configure model replacements.
	g_ViewModelCFG[nOriginalKnifeCT] = "models/weapons/v_knife_karam.mdl";
	g_ViewModelCFG[nOriginalKnifeT] = "models/weapons/v_knife_survival_bowie.mdl";
}

void SetKillIconCFG() {
	// Define replacement kill icons. (these only apply to you)
	g_KillIconCfg["knife_default_ct"] = "knife_karambit";
	g_KillIconCfg["knife_t"] = "knife_survival_bowie";
}

void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
	// Make the incoming data editable.
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	// Confirm that we are replacing our view model and not someone elses.
	CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

	if (pViewModel) {
		CBaseEntity* pOwner = Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)pViewModel->GetOwner());

		// Compare the owner entity of this view model to the local player entity.
		if (pOwner && pOwner->GetIndex() == Interfaces.pEngine->GetLocalPlayer()) {
			// Get the filename of the current view model.
			model_t* pModel = (model_t*)Interfaces.g_pModelInfo->GetModel(pViewModel->GetModelIndex());
			const char* szModel = Interfaces.g_pModelInfo->GetModelName(pModel);

			// Store the current sequence.
			int m_nSequence = pData->m_Value.m_Int;

			if (!strcmp(szModel, "models/weapons/v_knife_butterfly.mdl")) {
				// Fix animations for the Butterfly Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
				default:
					m_nSequence++;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_falchion_advanced.mdl")) {
				// Fix animations for the Falchion Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence--;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_push.mdl")) {
				// Fix animations for the Shadow Daggers.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
				case SEQUENCE_DEFAULT_LIGHT_MISS1:
				case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
				case SEQUENCE_DEFAULT_HEAVY_HIT1:
				case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence += 2;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_survival_bowie.mdl")) {
				// Fix animations for the Bowie Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
				default:
					m_nSequence--;
				}
			}

			// Set the fixed sequence.
			pData->m_Value.m_Int = m_nSequence;
		}
	}

	// Call original function with the modified data.
	fnSequenceProxyFn(pData, pStruct, pOut);
}

bool ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex) {
	// Check if this weapon has a valid override defined.
	if (g_SkinCFG.find(nWeaponIndex) == g_SkinCFG.end())
		return false;

	// Apply our changes to the fallback variables.
	*pWeapon->GetFallbackPaintKit() = g_SkinCFG[nWeaponIndex].nFallbackPaintKit;
	*pWeapon->GetEntityQuality() = g_SkinCFG[nWeaponIndex].nEntityQuality;
	*pWeapon->GetFallbackSeed() = g_SkinCFG[nWeaponIndex].nFallbackSeed;
	*pWeapon->GetFallbackStatTrak() = g_SkinCFG[nWeaponIndex].nFallbackStatTrak;
	*pWeapon->GetFallbackWear() = g_SkinCFG[nWeaponIndex].flFallbackWear;

	if (g_SkinCFG[nWeaponIndex].nItemDefinitionIndex)
		*pWeapon->GetItemDefinitionIndex() = g_SkinCFG[nWeaponIndex].nItemDefinitionIndex;

	// If a name is defined, write it now.
	if (g_SkinCFG[nWeaponIndex].szWeaponName) {
		sprintf_s(pWeapon->GetCustomName(), 32, "%s", g_SkinCFG[nWeaponIndex].szWeaponName);
	}

	// Edit "m_iItemIDHigh" so fallback values will be used.
	*pWeapon->GetItemIDHigh() = -1;

	return true;
}



bool ApplyCustomModel(CBaseEntity* pLocal, CBaseAttributableItem* pWeapon, int nWeaponIndex) {
	CBaseViewModel* pViewModel = (CBaseViewModel*)Interfaces.pEntList->GetClientEntityFromHandle(*(HANDLE*)((DWORD)pLocal + 0x32FC));

	if (!pViewModel)
		return false;

	// Get the weapon belonging to this view model.
	DWORD hViewModelWeapon = pViewModel->GetWeapon();
	CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)hViewModelWeapon);

	if (pViewModelWeapon != pWeapon)
		return false;

	// Check if an override exists for this view model.
	int nViewModelIndex = pViewModel->GetModelIndex();

	if (g_ViewModelCFG.find(nViewModelIndex) == g_ViewModelCFG.end())
		return false;

	// Set the replacement model.
	pViewModel->SetWeaponModel(g_ViewModelCFG[nViewModelIndex], pWeapon);

	return true;
}


bool ApplyCustomKillIcon(IGameEvent* pEvent) {
	// Get the user ID of the attacker.
	int nUserID = pEvent->GetInt("attacker");

	if (!nUserID)
		return false;

	// Only continue if we were the attacker.
	if (Interfaces.pEngine->GetPlayerForUserID(nUserID) != Interfaces.pEngine->GetLocalPlayer())
		return false;

	// Get the original weapon used to kill.
	const char* szWeapon = pEvent->GetString("weapon");

	for (auto ReplacementIcon : g_KillIconCfg) {
		// Search for a valid replacement.
		if (!strcmp(szWeapon, ReplacementIcon.first)) {
			// Replace with user defined value.
			pEvent->SetString("weapon", ReplacementIcon.second);
			break;
		}
	}

	return true;
}
