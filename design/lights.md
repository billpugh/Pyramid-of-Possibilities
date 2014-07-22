The RNLights class is the standard class used for manipulating a color buffer for an LED stip. A plain RNLights is just a color buffer, a RNLightsOctoWS2811 provides a way to directly copy the color buffer to a LED strip using the OctoWS2811 library, and a RNLightsNeoPixel provides code to directly copy the color buffer to a LED strip using the NeoPixel library.

The constructor simply requires the number of lights:

	// Specify the number of pixels assocaited with this set of RNLights
	RNLights(uint16_t numPixels);

There is an overall brightness level that effects the brightness of the LEDs, with 0 being completely black and 256 being full brightness. Changing this value is non-destructive, you can change the brightness to 0 to make the strip go dark, and then change it back to 256 to restore full brightness and all of the previous colors.

	  // Set overall brightness (non-destructive), 256 = max
	  void setBrightness(uint16_t amount=256);
	  // Get overall brightness
	  uint16_t getBrightness();

Some standard utility methods:

	  // Get number of pixels
	  uint16_t getNumPixels();
	  // wrap pixel address (e.g., -1 -> getNumPixels()-1
	  uint16_t normalize(int16_t pixel);
	  // reset colors to black set brightness to full
	  void reset();
	  
Ways to copy from one color buffer to another. 
	  
	  // copy pixel colors
	  void copyPixels(RNLights & from);
	  // set pixel colors using maximum of current or from colors
	  void copyPixelsMax(RNLights & from);
	  
Rotate the colors in the color buffer (e.g., copy color from pixel i to pixel i+1). This is done very quickly by just adjusting an internal offset.

	  // rotate pixel values
	  void rotate(bool up);
	  // shift pixel values, filling in with black
	  void shift(bool up);
	  
Ways to get/set pixel color. 
	    
	  // Various methods for getting/setting pixel color
	  void setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
	  void setPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value);
	  
	  void setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
	  // saturating add
	  void addPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
	  void copyPixelColor(uint16_t fromPixel, uint16_t toPixel);
	
	  void getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue);
	    
	  uint8_t getPixelRed(uint16_t pixel);
	  uint8_t getPixelGreen(uint16_t pixel);
	  uint8_t getPixelBlue(uint16_t pixel);
	
	  // Set all pixels to the same color
	  void setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue);
	  void setAllPixelHSVs(uint8_t hue, uint8_t saturation, uint8_t value);

The strips support doing a destructive time based fade of the entire strip, where the color values for each pixel are faded. You first set whether you want a normal fade (which has a halflife), or a linear fade (which decreases the color values at a constant rate per millisecond). Once the fade is configured, call fade to allow the fade to occur. The fade time based, it doesn't much how frequently you call fade (e.g., once per ms or once every 50 ms), it used the ms time values to determine how much time has passed since the last call to fade and decreases the color values appropriately. 

In practice, you should probably plan to call fade once per display refresh cycle.
	    
	  // Set the fade parameters; ms is current time
	  void setFade(long unsigned ms, uint16_t halfLifeMS);
	  // Set the linear fade parameters; ms is current time
	  void setLinearFade(long unsigned ms, uint8_t fadePerSec);
	  // update the fade; ms is current time
	  int fade(unsigned long ms);
