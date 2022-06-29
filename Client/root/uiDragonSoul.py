''' 1. '''
# Search @ DragonSoulRefineWindow
	REFINE_STONE_SLOT, DRAGON_SOUL_SLOT = xrange(2)

# Add above
	if app.ENABLE_DS_CHANGE_ATTR:
		REFINE_TYPE_CHANGE_ATTR = 3
		DS_SUB_HEADER_DIC.update({ REFINE_TYPE_CHANGE_ATTR : player.DS_SUB_HEADER_DO_CHANGE_ATTR })

''' 2. '''
# Search @ DragonSoulRefineWindow.__init__
		self.refineChoiceButtonDict = None

# Add below
		if app.ENABLE_DS_CHANGE_ATTR:
			self.refineChoiceButtonTitleDict = None

''' 3. '''
# Search @ DragonSoulRefineWindow.__LoadWindow
			self.wndMoney = self.GetChild("Money_Slot")

# Add below
			if app.ENABLE_DS_CHANGE_ATTR:
				self.refineChoiceButtonTitleDict = {
					self.REFINE_TYPE_GRADE : self.GetChild("GradeSlotTitle"),
					self.REFINE_TYPE_STEP : self.GetChild("StepSlotTitle"),
					self.REFINE_TYPE_STRENGTH : self.GetChild("RefineSlotTitle")
				}

''' 4. '''
# Search @ DragonSoulRefineWindow.Show
		self.currentRefineType = self.REFINE_TYPE_GRADE
		self.wndMoney.SetText(localeInfo.NumberToMoneyString(0))

# Add above
		if app.ENABLE_DS_CHANGE_ATTR:
			ui.ScriptWindow.Show(self)
			return

''' 5. '''
# Search @ DragonSoulRefineWindow.__FlushRefineItemSlot
		for invenType, invenPos, itemCount in self.refineItemInfo.values():
			remainCount = player.GetItemCount(invenType, invenPos)
			player.SetItemCount(invenType, invenPos, remainCount + itemCount)

# Add above
		if app.ENABLE_DS_CHANGE_ATTR:
			if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
				if self.refineItemInfo:
					invenType, invenPos, itemCount = self.refineItemInfo[self.REFINE_STONE_SLOT]
					remainCount = player.GetItemCount(invenType, invenPos)
					player.SetItemCount(invenType, invenPos, remainCount + itemCount)

				self.__Initialize()
				return

''' 6. '''
# Search @ DragonSoulRefineWindow.__SetItem
		if dstSlotIndex >= self.refineSlotLockStartIndex:
			return False

# Add above
		if app.ENABLE_DS_CHANGE_ATTR:
			if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
				if dstSlotIndex >= self.DRAGON_SOUL_SLOT:
					return False

''' 7. '''
# Search @ DragonSoulRefineWindow.__CheckCanRefine
		if self.REFINE_TYPE_GRADE == self.currentRefineType:
			return self.__CanRefineGrade(vnum)

# Add above
		if app.ENABLE_DS_CHANGE_ATTR:
			if self.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
				return self.__CanRefineChangeAttr(vnum)

''' 8. '''
# Search @ DragonSoulRefineWindow.__SelectRefineItemSlot
			attachedInvenType, attachedSlotPos, attachedItemCount = self.refineItemInfo[selectedSlotPos]
			selectedItemVnum = player.GetItemIndex(attachedInvenType, attachedSlotPos)

# Add above
			if app.ENABLE_DS_CHANGE_ATTR:
				if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
					if selectedSlotPos == self.DRAGON_SOUL_SLOT:
						return

''' 9. '''
# Search @ DragonSoulRefineWindow.__SelectRefineItemSlot
			player.SetItemCount(invenType, invenPos, remainCount + itemCount)
			del self.refineItemInfo[selectedSlotPos]

# Add below
			if app.ENABLE_DS_CHANGE_ATTR:
				if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
					if selectedSlotPos == self.REFINE_STONE_SLOT:
						self.__Initialize()
						self.Refresh()
						return

''' 10. '''
# Search @ DragonSoulRefineWindow.__PressDoRefineButton
		player.SendDragonSoulRefine(DragonSoulRefineWindow.DS_SUB_HEADER_DIC[self.currentRefineType], self.refineItemInfo)

# Add above
		if app.ENABLE_DS_CHANGE_ATTR:
			if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
				if not self.__CheckDoRefineChangeAttr():
					self.wndPopupDialog.SetText(localeInfo.DRAGON_SOUL_NOT_ENOUGH_MATERIAL)
					self.wndPopupDialog.Open()
					return

''' 11. '''
# Search @ DragonSoulRefineWindow.__RefreshRefineItemSlot
							if 0 != reference_vnum:
								item.SelectItem(reference_vnum)

# Add above
							if app.ENABLE_DS_CHANGE_ATTR:
								if DragonSoulRefineWindow.REFINE_TYPE_CHANGE_ATTR == self.currentRefineType:
									if DragonSoulRefineWindow.DRAGON_SOUL_SLOT == slotPos:
										reference_vnum = 100700

''' 12. '''
# Add to the bottom of the document
	if app.ENABLE_DS_CHANGE_ATTR:
		def SetWindowType(self, type):
			self.currentRefineType = type

			if type == self.REFINE_TYPE_CHANGE_ATTR:
				for btn in self.refineChoiceButtonDict.values():
					btn.SetUp()
					btn.Disable()

				for btnTitle in self.refineChoiceButtonTitleDict.values():
					btnTitle.SetText("")

				self.refineChoiceButtonDict[self.REFINE_TYPE_STRENGTH].Down()
				self.refineChoiceButtonTitleDict[self.REFINE_TYPE_STRENGTH].SetText(uiScriptLocale.CHANGE_ATTR_SELECT)
			else:
				for btn in self.refineChoiceButtonDict.values():
					btn.SetUp()
					btn.Enable()

				self.refineChoiceButtonDict[self.REFINE_TYPE_GRADE].Down()
				self.refineChoiceButtonTitleDict[self.REFINE_TYPE_GRADE].SetText(uiScriptLocale.GRADE_SELECT)
				self.refineChoiceButtonTitleDict[self.REFINE_TYPE_STEP].SetText(uiScriptLocale.STEP_SELECT)
				self.refineChoiceButtonTitleDict[self.REFINE_TYPE_STRENGTH].SetText(uiScriptLocale.STRENGTH_SELECT)

			self.__Initialize()
			self.Refresh()

		def __CanRefineChangeAttr(self, vnum):
			if self.currentRecipe:
				return False

			ds_info = self.__GetDragonSoulTypeInfo(vnum)

			if DragonSoulRefineWindow.INVALID_DRAGON_SOUL_INFO == ds_info:
				self.__PopUp(localeInfo.DRAGON_SOUL_IS_NOT_DRAGON_SOUL)
				return False

			ds_type, grade, step, strength = ds_info
			if grade < 5:
				return False

			self.currentRecipe = { "ds_info" : ds_info, "need_count" : 2, "fee" : 500000, "material_count" : (1, 3, 9, 27, 81) }
			if self.currentRecipe:
				material_vnum = 100700
				material_count = self.currentRecipe["material_count"][step]
				for slotNumber in xrange(player.ITEM_SLOT_COUNT):
					itemVNum = player.GetItemIndex(slotNumber)
					itemCount = player.GetItemCount(slotNumber)

					if material_vnum == itemVNum and itemCount != 0:
						item.SelectItem(material_vnum)

						self.refineItemInfo[self.DRAGON_SOUL_SLOT] = (player.INVENTORY, slotNumber, material_count)

						chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.DS_SYSTEM_MSG_1 % (item.GetItemName(), material_count))
						break

				self.refineSlotLockStartIndex = self.currentRecipe["need_count"]
				self.wndMoney.SetText(localeInfo.NumberToMoneyString(self.currentRecipe["fee"]))
				return True
			else:
				self.__PopUp(localeInfo.DRAGON_SOUL_CANNOT_REFINE)
				return False

		def __CheckDoRefineChangeAttr(self):
			if not self.currentRecipe:
				return False

			ds_type, grade, step, strength = self.currentRecipe["ds_info"]
			invenType, invenPos, itemCount = self.refineItemInfo[self.DRAGON_SOUL_SLOT]
			if (grade >= 5) and (player.GetItemCountByVnum(100700) >= itemCount):
				return True

			return False
