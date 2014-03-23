//
//  MyOpenGLView.h
//  Simulation0
//
//  Created by Bill Pugh on 3/3/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#import <Cocoa/Cocoa.h>

typedef struct {
    GLdouble x,y,z;
} recVec;

typedef struct {
	recVec viewPos; // View position
	recVec viewDir; // View direction vector
	recVec viewUp; // View up direction
	recVec rotPoint; // Point to rotate about
	GLdouble aperture; // pContextInfo->camera aperture
	GLint viewWidth, viewHeight; // current window/screen height and width
} recCamera;

@interface MyOpenGLView : NSOpenGLView {
    
    recCamera camera;
    
    CFAbsoluteTime msgTime; // message posting time for expiration
	
    NSTimer* timer;
    
    bool fAnimate;
	IBOutlet NSMenuItem * animateMenuItem;
    bool fInfo;
	IBOutlet NSMenuItem * infoMenuItem;

    bool fDrawHelp;
    bool doRotation;
	bool fDrawCaps;
    CFAbsoluteTime time;
    
    
	// spin
	GLfloat rRot [3];
	GLfloat rVel [3];
	GLfloat rAccel [3];
	
	// camera handling
	GLfloat worldRotation [4];
	GLfloat objectRotation [4];
	GLfloat shapeSize;
	
}

@end
