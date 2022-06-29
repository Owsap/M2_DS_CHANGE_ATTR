/// 1.
// Search
	PyModule_AddIntConstant(poModule, "CAMERA_STOP", CPythonApplication::CAMERA_STOP);

// Add below
#if defined(ENABLE_DS_CHANGE_ATTR)
	PyModule_AddIntConstant(poModule, "ENABLE_DS_CHANGE_ATTR", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_DS_CHANGE_ATTR", 0);
#endif
