#ifndef AL_LEDHandler_H
#define AL_LEDHandler_H
#include "AdvancedLED4.h"
#include "Animations.h"
//
//LED handler class. Highest level of abstraction
class LEDHandler {
public:
	//Array containing all currently loaded animations
	class animation* animation_array[NUMBER_OF_ANIMATIONS];
	//Array showing where to find each animations variables for the correspodning index
	int variable_start_locations[NUMBER_OF_ANIMATIONS];
	//Array containing how many variables each animation has
	int number_of_variables[NUMBER_OF_ANIMATIONS];
	//Array containing time values for each animation
	unsigned long long int start_time[NUMBER_OF_ANIMATIONS];
	//Array containing all of the variables for each animation
	int animation_variables[NUMBER_OF_VARIABLES];
	//Array specifying if the variables is in use or not
	bool variable_in_use[NUMBER_OF_VARIABLES];
	//Array specifying which layer each animation writes too
	class layer* layer_array[NUMBER_OF_ANIMATIONS];
	//Array containing all currently loaded layers
	class layer* loaded_layers[MAX_LAYERS];
	//Array Containing dependancies for deleting animations. A value of -1 indicates this animation is a root and independent
	int dependencies[NUMBER_OF_ANIMATIONS];
	//Array to tell that an animation has been marked for deletion
	bool animations_to_delete[NUMBER_OF_ANIMATIONS];
	//ToDo List of possible layer techniques to choose from
	//ToDo List of Possible Animations to choose from
	//ToDo triggers to choose from
	//ToDo color palletes to choose from

	//Variable which holds the current time. Determined at the start of each run cycle
	unsigned long long int current_time;

	//Variable specifying the index of whatever animation is currently being played
	int animation_index_number;

	//ToDo initializes the LEDHandler
	void initializeHandler();

	//ToDo runs a full cycle of what needs to be done by the handler each frame 
	void run();

	//ToDo checks for bluetooth message and does proper updates
	void bluetoothCheck();
	
	//ToDo updates audio information, calculates meta data and updates triggers
	void audioUpdates();

	//ToDo Plays each animation
	void playAnimations();

	//ToDo Deletes animations
	void deleteAnimations();

	//ToDo marks an animation for deletion
	void markForDeletion(int index);

	//ToDo Adds an animation to the handlers animation array. Need to update parameters
	void addAnimation(animation* new_animation);

	//ToDo defragments the variable array, returns the first available memory location
	int cleanVariableArray();

	//ToDo Send message containing all animations to choose from
	//ToDo send message containing all layers to choose from
	//ToDo Send message containing all triggers to choose from
	//ToDo Send message containing all colorpalletes to choose from

	//ToDo Load new trigger
	//ToDo load new layer
	//ToDo load new colorPallete
};

#endif