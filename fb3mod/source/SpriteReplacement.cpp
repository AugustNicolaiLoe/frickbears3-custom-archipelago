#include "SpriteReplacement.hpp"

#include <vector>

using namespace Aurie;
using namespace YYTK;

namespace FB3AP::SpriteReplacement{
    static YYTKInterface* g_ModuleInterface = nullptr; // Interface to YYtoolkit that can hook fb3
    static fs::path g_ModuleDirectory; // Will be used to keep the directory we're in, so we can find sprites easily

    static int32_t g_OriginalTitleSprite = -1; // This will be changed with the ID of the original sprite we want to change
    static int32_t g_ReplacementTitleSprite = -1; // This will be changed with the ID of the new sprite we are going to add

    static TRoutine g_OriginalDrawSpriteExt = nullptr; // Unsure, but I believe this is the routine we are hooking onto?

    static void DrawSpriteExtHook(
        OUT RValue& Result, // the result of this????
        IN CInstance* Self, // SELFexplanatory HAHAHA
        IN CInstance* Other, // Other, i have no puns
        IN int ArgumentCount, // each sprite has some arguments, these are count them
        IN RValue* Arguments // them argumans
    ) { 
        if (
            ArgumentCount >= 1 && // if there are arguments
            g_OriginalTitleSprite >= 0 && // if the sprite has been found and exists
            g_ReplacementTitleSprite >= 0 && // if the sprite has been found and exists
            Arguments[0].ToInt32() == g_OriginalTitleSprite // if we are actually changing the correct sprite
        ) {
            Arguments[0] = g_ReplacementTitleSprite; // changing the sprite ID, changing the sprite
        }

        g_OriginalDrawSpriteExt( // changing the uh... idk? but i know i need it, i think?
            Result,
            Self,
            Other,
            ArgumentCount,
            Arguments
        );
    }

    static void FrameCallback(FWFrame& FrameContext) {
        UNREFERENCED_PARAMETER(FrameContext);

        static bool has_initialized = false;

        if (has_initialized) {
            return;
        }

        has_initialized = true;

        std::vector<RValue> asset_get_index_arguments;
		asset_get_index_arguments.emplace_back("sGameTitle"); // getting sprite info

        g_OriginalTitleSprite = g_ModuleInterface->CallBuiltin(
			"asset_get_index",
			asset_get_index_arguments
		).ToInt32(); // getting the sprite index

        if (g_OriginalTitleSprite < 0) // woops no sprite
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Could not find sGameTitle."
			);

			return;
		}

        const fs::path replacement_path = g_ModuleDirectory / "assets" / "sGameTitleAP.png"; // my new sprite

        if (!fs::exists(replacement_path)) // no new sprite :(
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Replacement image was not found: %s",
				replacement_path.string().c_str()
			);

			return;
		}

        // getting sprite info about position
        std::vector<RValue> xoffset_arguments;
		xoffset_arguments.emplace_back(g_OriginalTitleSprite); 
        const double original_x_origin = g_ModuleInterface->CallBuiltin(
			"sprite_get_xoffset",
			xoffset_arguments
		).ToDouble();
        std::vector<RValue> yoffset_arguments;
		yoffset_arguments.emplace_back(g_OriginalTitleSprite);
		const double original_y_origin = g_ModuleInterface->CallBuiltin(
			"sprite_get_yoffset",
			yoffset_arguments
		).ToDouble();
        // foxing info for new sprite
        std::vector<RValue> sprite_add_arguments;
		sprite_add_arguments.emplace_back(replacement_path.string());
		sprite_add_arguments.emplace_back(1);
		sprite_add_arguments.emplace_back(false);
		sprite_add_arguments.emplace_back(false);
		sprite_add_arguments.emplace_back(original_x_origin);
		sprite_add_arguments.emplace_back(original_y_origin);


        g_ReplacementTitleSprite = g_ModuleInterface->CallBuiltin( // trying to send in replacement
			"sprite_add",
			sprite_add_arguments
		).ToInt32();

        if (g_ReplacementTitleSprite < 0)
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Failed to load replacement title sprite."
			);

			return;
		}

		g_ModuleInterface->Print(
			CM_LIGHTGREEN,
			"[FB3AP] Title replacement loaded. Original: %d, replacement: %d",
			g_OriginalTitleSprite,
			g_ReplacementTitleSprite
		);
    }

    AurieStatus Initialize(
		AurieModule* module,
		YYTKInterface* module_interface,
		const fs::path& module_path
	) {
        g_ModuleInterface = module_interface;
		g_ModuleDirectory = module_path.parent_path();

		TRoutine draw_sprite_ext = nullptr;

        AurieStatus status = g_ModuleInterface->GetNamedRoutinePointer( // telling YYTK that we want to intercept drawing sprite thingy
			"draw_sprite_ext",
			reinterpret_cast<PVOID*>(&draw_sprite_ext)
		);

		if (!AurieSuccess(status) || !draw_sprite_ext)
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Could not locate draw_sprite_ext."
			);

			return status;
		}

        status = MmCreateHook(
			module,
			"FB3AP_DrawSpriteExt",
			draw_sprite_ext,
			DrawSpriteExtHook,
			reinterpret_cast<PVOID*>(&g_OriginalDrawSpriteExt)
		);

		if (!AurieSuccess(status))
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Could not hook draw_sprite_ext."
			);

			return status;
		}
        
        status = g_ModuleInterface->CreateCallback(
			module,
			EVENT_FRAME,
			FrameCallback,
			0
		);

		if (!AurieSuccess(status))
		{
			g_ModuleInterface->Print(
				CM_LIGHTRED,
				"[FB3AP] Could not register sprite initialization callback."
			);

			return status;
		}

		g_ModuleInterface->Print(
			CM_LIGHTGREEN,
			"[FB3AP] Sprite replacement initialized."
		);

		return AURIE_SUCCESS;
    }
}