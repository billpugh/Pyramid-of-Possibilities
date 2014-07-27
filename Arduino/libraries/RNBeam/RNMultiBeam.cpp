#include "RNMultiBeam.h"

#pragma mark - RNBeam

RNBeam::RNBeam() {
	position = 0;
	maxval = 240;
	range = 240;
	halfrange = 120;
	minval = 0;
	speed = 22;
	direction_sign = 1;
	width = 100;
	width_speed = 0;
	width_direction = 1;
	r = 100;
	g = 0;
	b = 200;
	min_range_of_lights_to_draw = 0;
	max_range_of_lights_to_draw = 0; 
	offset = 0;
}

RNBeam::~RNBeam() {
}