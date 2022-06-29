/// 1.
// Search
	bool DoRefineStrength(LPCHARACTER ch, TItemPos(&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);

// Add below
#if defined(__DS_CHANGE_ATTR__)
	bool DoChangeAttribute(LPCHARACTER lpCh, TItemPos(&arItemPos)[DRAGON_SOUL_REFINE_GRID_SIZE]);
#endif
