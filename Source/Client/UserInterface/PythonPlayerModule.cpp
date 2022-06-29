/// 1.
// Search @ PyObject* playerSendDragonSoulRefine
	case DS_SUB_HEADER_DO_REFINE:

// Add below
#if defined(ENABLE_DS_CHANGE_ATTR)
	case DS_SUB_HEADER_DO_CHANGE_ATTR:
#endif

/// 2.
// Search
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_DO_REFINE", DS_SUB_HEADER_DO_REFINE);

// Add below
#if defined(ENABLE_DS_CHANGE_ATTR)
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_DO_CHANGE_ATTR", DS_SUB_HEADER_DO_CHANGE_ATTR);
#endif
