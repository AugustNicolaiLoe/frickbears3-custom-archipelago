# Frickbears3 Custom Archipelago Randomizer
Archiepelago randomizer is a project that allows people to randomize games cross each other, meaning that items can be unlocked by checks in other games. This project aims to add the possibility to do this with the game Frickbears 3.

This project is done outside of the main and secondary Archipelago project.


# Current goals
- Create an .apworld file that allows for cross randomisation through the Archipelago randomisation system.
- Prepare a .yaml file for use in settings for the randomisation.
- Create a mod for Frickbears3 that allows for communication between Archipelago and making the game actually behave how we need.

The current plan for the game and it's checks goes like this:
- Animatronics:
    - Salvagable animatronics will be linked to a check.
        - When the check is not already released, the linked check will count as the salvage value. This way, when you salvage the animatronic, you will add it to the run and release the related check.
        - When the check is already released, and the animatronic has not been gotten through a check, it's salvage value will be 0.
        - It is only when the related check is released and the animatronics check has been gotten that it's salvage value is set back to normal.

    - Animatronics themselves are a check.
        - When an animatronic is found it is added the current night automatically. If it is already added, it's difficulty level is heightened.
        - This also makes the salvage value for the animatronic go to it's original, instead of 0 after the check if released.

    - Animatronics are always added through salvage
        - This is done so the start of the game is not simply done with a few animatronics, and the gameplay loop is preserved.
        - We hope the salvage value dropping to 0, however, will be enough to make it feel special and usefull when you get the animatronics check.

    - The salvagable animatronics in an area will also be randomised.
        - The animatronics found within an area will be shuffeled
        - While this randomisation is set by the Archipelago system, it is not related to a check, and only happens and changes the game itself. It's simply to give a little bit more randomisation and fun options within the game.
        - Certain animatronics will only be added to this pool if an option is added, this is mainly the animatronics related to boss fights.
        - Certain ending specific animatronics will only be randomised within it's original area, seeing as they seemingly need a specific order.

    - A visual change will be made to the target symbol that apears when you look at animatronics
        - This is way quicker show players what the animatronic is currently linked to.
        - When the check if for something outbound, it will be something related to the Archipelago symbol
        - When the check if for something inbound, it will be something related to the fb3
        - When the check has been released, it will be the normal target symbol

- Upgrade Cadet Store:
    - Each upgrade will be a check.
        - This means that the shop will be filled with checks
        - A range will be used in the settings to set the random range of items for these checks
        - When a check has been bought, the item will be removed form the shop list

    - Each upgrade from the store will be free after it is released.
        - If you get a check that is one of the original upgrades form the store, it will be added to the list permanently, and it's price will be made 0.
        - This is to give a form of permanent upgrades to the game, instead of adding inn all new checks and items that need to be kept through runs
        - This means you will still have to find the item in the store, but when you do it is free

    - A visual will show what the item is.
        - If the item is outbound, it will have an 8-bit visual of the the Archipelago symbol
        - Everything that is in the game will have it's own symbol to much more easily see what it is at a glance

    - Prices of animatronics.
        - A setting can be enabled to set the prices of animatronics to -(their original salvage value). Meaning you would earn the money you would from salvage, since they are added to your run as animatronics
    
- Minigame unlocks:
    - Minigames as checks.
        - A lot of the minigames are unlocked in the game through the arcade cabinets
        - These arcade cabinets will unlock a check, and other checks can unlock mingames

    - A visual will show what the check is
        - In some way, not determined yet, the hope is to show the player quickly and easily if the check if outbound or not

- Office store and trophy checks:
    - Since we didn't see an easy way of doing any checks with trophies and the office store, we decided to join them
        - Unlike the Upgrade Cadet Store, the office store is static, meaning that purchasing checks and unlocking purchasable items would have some weird logic.
        - Instead we decided to use the trophies as checks for the store

    - Unlocking purchasable items
        - You only start with the pickle jar
        - When someone releases a check related to one of the items, you can start purchasing them
    
    - Releasing checks with trophies
        - The checks are not linked to specific trophies, but rather trophies amount
        - There are 12 purchasable items, 11 without the pickle jar, and 45 trophies
        - A bunch of these trophies are hard to get or linked to items, so we decided on these check: 1, 2, 4, 6, 8, 10, 12, 15, 17, 20, 25

- Endings:
    - Each ending will give a check
        - It's as easy as it sounds, an ending is a check
        - This also means that checks can be endings, and the only way to actually get all four endings to get the ultimate ending is to get the first four endings, this then being the win condition with this goal

- Custom night challanges:
    - Like the trophy checks, these checks will not be set on specicif challanges, but amount beaten
    
    - When someone releases a custom night challange check, that custom challange is marked as done, and is counted towards the amount beaten



- Checks and permanence:
    - All checks will, to some degree, be permanent.
        - At the start of each new run, the game will check with archipelago to see what it should unlock for the player.
        - Animatronics will have their prices set to the original
        - Cadet Upgrade Store upgrades will be added to the list and set to 0
        - Minigames will be unlocked from the start
        - Office store items will be unlocked from the start
        - Endings are permanent by nature
        - Custom night challanges beaten is also permanent by nature

- Goals:
    - Though not fully set in stone, there are two ideas of goals that might work
        - Beating the ultimate ending, which means you must beat the 4 other endings first

        - Unlock all (currently) 47 animatronics

- Options:
    - Every check and randomisation here will be optional, and have options to use that decides how things will be done

    - one of my goals is to give as much freedom of choice to the player with what they want in their run