//
// Created by gcpease on 12/1/2021.
//

#ifndef FISHTUTORIAL_DIALOGUE_H
#define FISHTUTORIAL_DIALOGUE_H

#include <vector>
#include <string>

public:
std::vector<std::string> startDialogue = {
        "Welcome to the Baba Ghanoush Fish Information app!",
        "In this tutorial, you will learn how to take proper care of freshwater fish."
};

/*
 * This is the dialogue of the first task we are presenting the user - Preparing the tank.
 */
std::vector<std::string> dialogueOne = {
        "In order to start taking care of fish, we must initially have a tank with a proper filtration and heating system",
        "Proper water care for fresh water fish is very important.",
        "In the right conditions, your fish will flourish and be happy.",
        "In the incorrect conditions, you put the lives of your fish in danger.",
        "To create the right water conditions for your fish, you first need to fill the tank with water.",
        "However, water straight from the tap is very dangerous for your fish.",
        "You need to either let the water sit overnight or add water conditioner.",
        "Failure to do this will burn the gills of your fish.",
        "Once the water has been added, you will need to let it circulate for no less than an hour.",
        "After the water is circulated and brought up to temperature, you can now add fish to your tank."
};

/*
 * This is the dialogue for the second task - Adding fish to the tank.
 */
std::vector<std::string> dialogueTwo = {
        "Selecting compatible fish species is a critical part of taking care of a fish tank.",
        "Some fish tend to be much more aggressive, such as some African Cichlids.",
        "On the contrary, others tend to be much more docile, such as Plecostemouses.",
        "Having aggressive fish in your tank poses a risk for all the others living with them.",
        "In this tutorial, we have three selections you can chose from.",
        "A bushy nose Plecostemous, a Gold Fish, and a Black Ghost Knife Fish."
};

/*
 * This is the dialogue for the third task - Feeding fish.
 */
std::vector<std::string> dialogueThree = {
        "Feeding your fish can be a fun and very rewarding task.",
        "However, there are some details to be cautious about while feeding.",
        "For example, putting too much food in your tank will cause your water to go bad, and make your fish ill.",
        "It is recommended that you feed your fish at least once a day.",
        "The amount of food depends on how much the fish eats - it takes some time to find the right amount of food to give.",
        "Fish can eat a wide variety of food, however flakes are the best choice if you don't know what to give them.",
        "To feed your fish, simply poor some flakes into the lid of your fish food container, and poor the flakes on the lid in the tank."
};

/*
 * This is the dialogue for the fourth task - performing a filter change.
 */
std::vector<std::string> dialogueFour = {
        "After having your fish tank for some time, you might notice your filter getting clogged or your water looking different.",
        "This is a signal that you need to change your filter.",
        "Filter changes are an easy task to accomplish, and require little work depending on what filter you are using.",
        "In this example, we are using a simple air powered waterfall filter.",
        "To change the filter, you must first turn off the pump.",
        "After turning off the pump, you need to extract the filter cartridge.",
        "Depending on the quality of the cartridge, you may be able to just clean off the cartridge and have it work out.",
        "If your cartridge is becoming degraded, you need to replace the unit as a whole.",
        "Keeping your filter working is an important task for caring for fish."
};

/*
 * This is the dialogue for the fifth task - adding new fish to a tank.
 */
std::vecotr<std::string> dialogueFive = {
        "Adding more fish to your aquarium is a really fun and rewarding thing to do, however, it may be risky.",
        "Finding fish that are compatible with those already in your tank is extremely critical and cannot be forgotten.",
        "With the right balance, your fish will strive. With the incorrect balance, your fish may be attacked by others.",
        "To add a fish to your tank, you must first acclimate your new fish.  This can be done quite easily.",
        "To acclimate, put your fish in the fish bag it came with, in your tank for about half an hour.",
        "This allows your fish to get accustomed to the temperature of their new home.",
        "Mixing the water in the fish bag with some water from your tank is also important.",
        "This allows your new fish to also get accustomed to the water chemistry.",
        "After half an hour, you may release your new fish to their new home."
};

/*
 * This is the dialogue for the sixth task - water changes.
 */
std::vector<std::string> dialogueSix = {
        "Water changes are important for the health of your fish.",
        "Over time, the chemistry of your fish tank changes, and some of those changes may be hazardous.",
        "However, changing the water in your fish tank is not as bad as it seems.",
        "First, you must fill up some container with whatever amount of water you are wanting to change.",
        "Then, you need to either use water conditioner or let the water sit for about 24 hours before you can do a water change.",
        "After this, you need to siphon out roughly the same amount of water from your tank into a second container.",
        "The contents in this container can be drained in a sink or dumped outside.",
        "After siphoning the water out, you can pour water from the first container in the tank.",
        "Be sure to put your hand under the water stream to prevent hurting fish or damaging the tank."
};
#endif //FISHTUTORIAL_DIALOGUE_H
