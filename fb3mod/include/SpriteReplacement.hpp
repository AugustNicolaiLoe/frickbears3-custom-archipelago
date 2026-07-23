#pragma once

#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>

#include <filesystem>

namespace FB3AP::SpriteReplacement
{
	Aurie::AurieStatus Initialize(
		Aurie::AurieModule* module,
		YYTK::YYTKInterface* module_interface,
		const std::filesystem::path& module_path
	);
}