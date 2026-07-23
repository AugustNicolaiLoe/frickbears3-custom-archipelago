#include <YYToolkit/YYTK_Shared.hpp>

#include "SpriteReplacement.hpp"

using namespace Aurie;
using namespace YYTK;

static YYTKInterface* g_ModuleInterface = nullptr;

EXPORTED AurieStatus ModuleInitialize(
	IN AurieModule* Module,
	IN const fs::path& ModulePath
)
{
	g_ModuleInterface = YYTK::GetInterface();

	if (!g_ModuleInterface)
		return AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;

	g_ModuleInterface->Print(
		CM_LIGHTGREEN,
		"[FB3AP] Plugin initialized."
	);

	const AurieStatus sprite_status =
		FB3AP::SpriteReplacement::Initialize(
			Module,
			g_ModuleInterface,
			ModulePath
		);

	if (!AurieSuccess(sprite_status))
		return sprite_status;

	return AURIE_SUCCESS;
}