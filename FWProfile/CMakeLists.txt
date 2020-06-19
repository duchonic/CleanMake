add_library (
	FWProfile
	FwPrConfig.c
	FwPrCore.c
	FwPrSCreate.c
	FwSmAux.c
	FwSmConfig.c
	FwSmCore.c
	FwSmSCreate.c
)
target_include_directories (FWProfile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
