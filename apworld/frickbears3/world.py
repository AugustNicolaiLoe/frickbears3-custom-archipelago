from BaseClasses import Item, ItemClassification, Location, Region
from worlds.AutoWorld import World
from worlds.generic.Rules import set_rule

from .options import Frickbears3Options

# THESE ARE JUST TO NOT MESS UP AND WRITE "Frikbear's 3"
# IMPORTANT HAS TO STAY CONSISTANT
GAME_NAME = "Frickbear's 3"

# ITEMS
LEVEL_2_ACCESS = "Level 2 Access"

# LOCATIONS
CADET_SHOP_PURCHASE = "Cadet Shop Purchase"
BEAT_LEVEL_2 = "Beat Level 2"

# GOAL
VICTORY = "Victory"



# classes weee
class Frickbears3Item(Item):
    game = GAME_NAME

class Frickbears3Location(Location):
    game = GAME_NAME


class Frickbears3World(World):
    """
    Creates the frickbears3 world that allows ap to understand how to randomise
    right? i think so, im just using whatever sources i can find lol
    """
    game = GAME_NAME

    options_dataclass = Frickbears3Options
    options: Frickbears3Options

    item_name_to_id = {
        LEVEL_2_ACCESS: 1
    }

    location_name_to_id = {
        CADET_SHOP_PURCHASE: 1
    }

    def create_regions(self) -> None:
        menu_region = Region(
            "Menu",
            self.player,
            self.multiworld
        )

        game_region = Region(
            "Game",
            self.player,
            self.multiworld
        )

        cadet_shop_location = Frickbears3Location(
            self.player,
            CADET_SHOP_PURCHASE,
            self.location_name_to_id[CADET_SHOP_PURCHASE],
            game_region
        )

        game_region.locations.append(cadet_shop_location)

        victory_location = Frickbears3Location(
            self.player,
            BEAT_LEVEL_2,
            None,
            game_region
        )

        victory_item = Frickbears3Item(
            VICTORY,
            ItemClassification.progression,
            None,
            self.player
        )

        victory_location.place_locked_item(victory_item)
        game_region.locations.append(victory_location)

        menu_region.connect(game_region)

        self.multiworld.regions.extend([
            menu_region,
            game_region
        ])

    def create_item(self, name: str) -> Frickbears3Item:
        return Frickbears3Item(
            name,
            ItemClassification.progression,
            self.item_name_to_id[name],
            self.player
        )

    def create_items(self) -> None:
        level_2_access = self.create_item(LEVEL_2_ACCESS)
        self.multiworld.itempool.append(level_2_access)

    def set_rules(self) -> None:
        beat_level_2 = self.multiworld.get_location(
            BEAT_LEVEL_2,
            self.player,
        )

        set_rule(
            beat_level_2,
            lambda state: state.has(LEVEL_2_ACCESS, self.player),
        )

        self.multiworld.completion_condition[self.player] = (
            lambda state: state.has(VICTORY, self.player)
        )