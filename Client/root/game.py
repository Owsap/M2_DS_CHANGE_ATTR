''' 1. '''
# Search
	def BINARY_DragonSoulRefineWindow_Open(self):
		self.interface.OpenDragonSoulRefineWindow()

# Replace with
	if app.ENABLE_DS_CHANGE_ATTR:
		def BINARY_DragonSoulRefineWindow_Open(self, type):
			self.interface.OpenDragonSoulRefineWindow(type)
	else:
		def BINARY_DragonSoulRefineWindow_Open(self):
			self.interface.OpenDragonSoulRefineWindow()
