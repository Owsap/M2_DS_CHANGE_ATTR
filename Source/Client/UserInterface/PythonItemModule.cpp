/// 1.
// Search
	PyModule_AddIntConstant(poModule, "MATERIAL_DS_REFINE_HOLLY", CItemData::MATERIAL_DS_REFINE_HOLLY);

// Add below
#if defined(ENABLE_DS_CHANGE_ATTR)
	PyModule_AddIntConstant(poModule, "MATERIAL_DS_CHANGE_ATTR", CItemData::MATERIAL_DS_CHANGE_ATTR);
#endif
