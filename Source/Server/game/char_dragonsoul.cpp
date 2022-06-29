/// 1.
// Search
bool CHARACTER::DragonSoul_RefineWindow_Close()

// Add above
#if defined(__DS_CHANGE_ATTR__)
bool CHARACTER::DragonSoul_RefineWindow_ChangeAttr_Open(LPENTITY pEntity)
{
	if (m_pointsInstant.m_pDragonSoulRefineWindowOpener == nullptr)
		m_pointsInstant.m_pDragonSoulRefineWindowOpener = pEntity;

	TPacketGCDragonSoulRefine PDS;
	PDS.header = HEADER_GC_DRAGON_SOUL_REFINE;
	PDS.bSubType = DS_SUB_HEADER_OPEN_CHANGE_ATTR;

	LPDESC lpDesc = GetDesc();
	if (lpDesc == nullptr)
	{
		sys_err("User(%s)'s DESC is NULL POINT.", GetName());
		return false;
	}

	lpDesc->Packet(&PDS, sizeof(PDS));
	return true;
}
#endif
