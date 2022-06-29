/// 1.
// Search
	int ds_give_qualification(lua_State* L)

// Add above
#if defined(__DS_CHANGE_ATTR__)
	int ds_open_changeattr_window(lua_State* L)
	{
		const LPCHARACTER c_lpCh = CQuestManager::instance().GetCurrentCharacterPtr();
		if (c_lpCh == nullptr)
		{
			sys_err("NULL POINT ERROR");
			return 0;
		}

		if (c_lpCh->DragonSoul_IsQualified())
			c_lpCh->DragonSoul_RefineWindow_ChangeAttr_Open(CQuestManager::instance().GetCurrentNPCCharacterPtr());

		return 0;
	}
#endif

/// 2.
// Search
			{ "open_refine_window" , ds_open_refine_window },

// Add below
#if defined(__DS_CHANGE_ATTR__)
			{ "open_changeattr_window" , ds_open_changeattr_window },
#endif
