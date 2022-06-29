/// 1.
// Search @ bool IsDragonSoulRefineMaterial
		pItem->GetSubType() == MATERIAL_DS_REFINE_HOLLY

// Add below
#if defined(__DS_CHANGE_ATTR__)
		|| pItem->GetSubType() == MATERIAL_DS_CHANGE_ATTR
#endif

/// Example
	return (pItem->GetSubType() == MATERIAL_DS_REFINE_NORMAL ||
		pItem->GetSubType() == MATERIAL_DS_REFINE_BLESSED ||
		pItem->GetSubType() == MATERIAL_DS_REFINE_HOLLY
#if defined(__DS_CHANGE_ATTR__)
		|| pItem->GetSubType() == MATERIAL_DS_CHANGE_ATTR
#endif
		);

/// 2.
// Search
void DSManager::SendRefineResultPacket(LPCHARACTER ch, BYTE bSubHeader, const TItemPos& pos)

// Add above
#if defined(__DS_CHANGE_ATTR__)
bool DSManager::DoChangeAttribute(LPCHARACTER lpCh, TItemPos(&arItemPos)[DRAGON_SOUL_REFINE_GRID_SIZE])
{
	if (lpCh == nullptr)
		return false;

	if (arItemPos == nullptr)
		return false;

	if (!lpCh->DragonSoul_RefineWindow_CanRefine())
	{
		sys_err("%s do not activate DragonSoulRefineWindow. But how can he come here?", lpCh->GetName());
		lpCh->ChatPacket(CHAT_TYPE_INFO, "[SYSTEM ERROR]You cannot use dragon soul refine window.");
		return false;
	}

	std::set<LPITEM> setItems;
	for (int i = 0; i < DRAGON_SOUL_REFINE_GRID_SIZE; i++)
	{
		LPITEM lpItem = lpCh->GetItem(arItemPos[i]);
		if (lpItem)
			setItems.insert(lpItem);
	}
	if (setItems.empty())
		return false;

	LPITEM lpRefineMaterial = nullptr;
	LPITEM lpDragonSoul = nullptr;
	for (auto lpItem : setItems)
	{
		if (lpItem->IsEquipped())
			return false;

		if (lpItem->IsDragonSoul())
		{
			if (lpDragonSoul != nullptr)
			{
				SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL, TItemPos(lpItem->GetWindow(), lpItem->GetCell()));
				return false;
			}
			lpDragonSoul = lpItem;
		}
		else if (IsDragonSoulRefineMaterial(lpItem))
		{
			if (lpRefineMaterial != nullptr)
			{
				SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL, TItemPos(lpItem->GetWindow(), lpItem->GetCell()));
				return false;
			}
			lpRefineMaterial = lpItem;
		}
		else
		{
			lpCh->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("°­È­¿¡ ÇÊ¿äÇÑ Àç·á°¡ ¾Æ´Õ´Ï´Ù."));
			SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_INVALID_MATERIAL, TItemPos(lpItem->GetWindow(), lpItem->GetCell()));
			return false;
		}
	}

	BYTE bType, bGrade, bStep, bStrength;
	if (!lpDragonSoul || !lpRefineMaterial)
	{
		SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL, NPOS);
		return false;
	}

	if (lpDragonSoul != nullptr)
	{
		GetDragonSoulInfo(lpDragonSoul->GetVnum(), bType, bGrade, bStep, bStrength);
		if (bGrade < DRAGON_SOUL_GRADE_MYTH)
		{
			lpCh->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("°­È­ÇÒ ¼ö ¾ø´Â ¿ëÈ¥¼®ÀÔ´Ï´Ù."));
			SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_MAX_REFINE, TItemPos(lpDragonSoul->GetWindow(), lpDragonSoul->GetCell()));
			return false;
		}
	}

	int64_t iFee = lpRefineMaterial->GetValue(0);
	if (lpCh->GetGold() < iFee)
	{
		lpCh->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("°³·®À» ÇÏ±â À§ÇÑ µ·ÀÌ ºÎÁ·ÇÕ´Ï´Ù."));
		SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MONEY, NPOS);
		return false;
	}

	WORD wNeedMaterialCount = 1;
	switch (bStep)
	{
	case DRAGON_SOUL_STEP_LOWEST:
		wNeedMaterialCount = DRAGON_SOUL_CHANGE_ATTR_STEP_LOWEST;
		break;
	case DRAGON_SOUL_STEP_LOW:
		wNeedMaterialCount = DRAGON_SOUL_CHANGE_ATTR_STEP_LOW;
		break;
	case DRAGON_SOUL_STEP_MID:
		wNeedMaterialCount = DRAGON_SOUL_CHANGE_ATTR_STEP_MID;
		break;
	case DRAGON_SOUL_STEP_HIGH:
		wNeedMaterialCount = DRAGON_SOUL_CHANGE_ATTR_STEP_HIGH;
		break;
	case DRAGON_SOUL_STEP_HIGHEST:
		wNeedMaterialCount = DRAGON_SOUL_CHANGE_ATTR_STEP_HIGHEST;
		break;
	}

	if (lpCh->CountSpecifyItem(lpRefineMaterial->GetVnum()) < wNeedMaterialCount)
	{
		SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL, NPOS);
		return false;
	}

	lpCh->RemoveSpecifyItem(lpRefineMaterial->GetVnum(), wNeedMaterialCount);
	lpCh->PointChange(POINT_GOLD, -iFee);

	lpDragonSoul->ClearAllAttribute();
	PutAttributes(lpDragonSoul);

	SendRefineResultPacket(lpCh, DS_SUB_HEADER_REFINE_SUCCEED, TItemPos(lpDragonSoul->GetWindow(), lpDragonSoul->GetCell()));

	return true;
}
#endif
