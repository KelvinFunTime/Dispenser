/***************************************************************
*Debounce maybe? This is a late game addition.
*
*
****************************************************************/
int debounce (int button, int button_debounce_length, int direction)
{
	int return_value = 0;
	
	usleep (button_debounce_length);
	
	if(senseCup(button) == direction)
	{
		return_value = 1;
	}
	
	return return_value;
}