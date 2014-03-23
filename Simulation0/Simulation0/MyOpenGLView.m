//
//  MyOpenGLView.m
//  Simulation0
//
//  Created by Bill Pugh on 3/3/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#import "MyOpenGLView.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLKit/GLKMath.h>
#import "trackball.h"
#import "platforms.h"
#import "leds.h"
#import "tier.h"
#import "model.h"

@implementation MyOpenGLView

GLint cube_num_vertices = 8;

GLfloat cube_vertices [8][3] = {
    {1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
    {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0} };

GLfloat cube_vertex_colors [8][3] = {
    {1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
    {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0} };

GLint num_faces = 6;

short cube_faces [6][4] = {
    {3, 2, 1, 0}, {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5}, {4, 5, 6, 7} };

GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};      // Fog Color

recVec gOrigin = {0.0, 0.0, 0.0};
// time and message info
CFAbsoluteTime gMsgPresistance = 10.0f;
// error output

float gErrorTime;

const GLint num_triangles = 20;
GLfloat triangleCenter[num_triangles][2];

static float randomFloat() {
    return random() / (float)RAND_MAX;
}

- (void) prepareOpenGL
{
    //    long swapInt = 1;
    //
    //    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; // set to vbl sync
    //
    //	// init GL stuff here
    //	glEnable(GL_DEPTH_TEST);
    
    //	glShadeMoe(GL_CULL_FACE);
    //	glFrontFace(GL_CCW);
    //	glPolygdel(GL_SMOOTH);
    //	glEnablonOffset (1.0f, 1.0f);
	
    //	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	[self resetCamera];
	shapeSize = 7.0f; // max radius of of objects
    
    
}


- (void) initialize {
    // Initialization code here.
    NSLog(@"Initializing");
    for(int i = 0; i < 20; i++) {
        triangleCenter[i][0] = randomFloat() - 0.5;
        triangleCenter[i][1] = randomFloat() - 0.5;
    }
    [self prepareOpenGL];
    rVel[0] = 0.3; rVel[1] = 0.1; rVel[2] = 0.2;
	rAccel[0] = 0.003; rAccel[1] = -0.005; rAccel[2] = 0.004;
	fInfo = 1;
	fAnimate = 1;
	time = CFAbsoluteTimeGetCurrent ();  // set animation time start time
	fDrawHelp = 1;
    setStartTime (); // get app start time
  	// start animation timer
	timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f) target:self selector:@selector(animationTimer:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode]; // ensure timer fires during resize
}

- (void) setFog {
    glClearColor(0.0f,0.5f,0.0f,1.0f);          // We'll Clear To The Color Of The Fog ( Modified )
    
    glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.3f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
    
}

uint8_t initialized = 0;
- (void) initOpenGL {
    
    if (!initialized) {
        
        initialized = 1;
        if (0)
            [self setFog];
        else
            glClearColor(0.0, 0, 0, 0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_POINT_SMOOTH);
        glGetFloatv(GL_POINT_SIZE_MAX, pmax);
        NSLog(@"pmax is %f", pmax[0]);
        glPointSize(2);
        glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, pointParams);
        glPointParameterf (GL_POINT_FADE_THRESHOLD_SIZE, 2.0);
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);
        
        definePlatforms();
    }
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}
- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) [self initialize];
    return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) [self initialize];
    return self;
    
}



// sets the camera data to initial conditions
- (void) resetCamera
{
    camera.aperture = 40;
    camera.rotPoint = gOrigin;
    
    camera.viewPos.x = 0.0;
    camera.viewPos.y = 0.0;
    camera.viewPos.z = 2.5;
    camera.viewDir.x = -camera.viewPos.x;
    camera.viewDir.y = -camera.viewPos.y;
    camera.viewDir.z = -camera.viewPos.z;
    
    camera.viewUp.x = 0;
    camera.viewUp.y = 1;
    camera.viewUp.z = 0;
    for(int i = 0; i < 4; i++)
        worldRotation [i] = objectRotation[i] = 0.0;
}


- (void) resizeGL
{
	NSRect rectView = [self bounds];
	
	// ensure camera knows size changed
	if ((camera.viewHeight != rectView.size.height) ||
	    (camera.viewWidth != rectView.size.width)) {
		camera.viewHeight = rectView.size.height;
		camera.viewWidth = rectView.size.width;
		NSLog(@" camera view %d %d", camera.viewWidth, camera.viewHeight);
		glViewport (0, 0, camera.viewWidth, camera.viewHeight);
		[self updateProjection];  // update projection matrix
        //		[self updateInfoString];
	}
}

// update the projection matrix based on camera and view info
- (void) updateProjection
{
	GLdouble ratio, radians, wd2;
	GLdouble left, right, top, bottom, near, far;
    
    [[self openGLContext] makeCurrentContext];
    
    shapeSize = 6.0;
	// set projection
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	near = -camera.viewPos.z - shapeSize * 0.5;
	if (near < 0.00001)
		near = 0.00001;
	far = -camera.viewPos.z + shapeSize * 0.5;
	if (far < 1.0)
		far = 1.0;
    near = 1.0;
    far = 7.0;
	radians = 0.0174532925 * camera.aperture / 2; // half aperture degrees to radians
	wd2 = near * tan(radians);
	ratio = camera.viewWidth / (float) camera.viewHeight;
	if (ratio >= 1.0) {
		left  = -ratio * wd2;
		right = ratio * wd2;
		top = wd2;
		bottom = -wd2;
	} else {
		left  = -wd2;
		right = wd2;
		top = wd2 / ratio;
		bottom = -wd2 / ratio;
	}
    NSLog(@"glFrustum %f  %f %f  %f %f  %f %f",
          ratio, left, right, bottom, top, near, far);
	glFrustum (left, right, bottom, top, near, far);
}

// update the projection matrix based on camera and view info
- (void) updateProjection2
{
    glMatrixMode(GL_PROJECTION);
    
    GLKMatrix4 p = GLKMatrix4MakePerspective(3.14159*50.0/180,((float)camera.viewHeight)/camera.viewWidth, 1.0, 7.0);
    glLoadMatrixf(p.m);
    
    
}

// updates the contexts model view matrix for object and camera moves
- (void) updateModelView
{
    [[self openGLContext] makeCurrentContext];
	
	// move view
	glMatrixMode (GL_MODELVIEW);
    
    
    if (0) NSLog(@"look at %f %f %f    %f %f %f   %f %f %f", camera.viewPos.x, camera.viewPos.y, camera.viewPos.z,
                 camera.viewPos.x + camera.viewDir.x,
                 camera.viewPos.y + camera.viewDir.y,
                 camera.viewPos.z + camera.viewDir.z,
                 camera.viewUp.x, camera.viewUp.y ,camera.viewUp.z);
    glLoadIdentity ();
    gluLookAt(camera.viewPos.x, camera.viewPos.y, camera.viewPos.z,
              camera.viewPos.x + camera.viewDir.x,
              camera.viewPos.y + camera.viewDir.y,
              camera.viewPos.z + camera.viewDir.z,
              camera.viewUp.x, camera.viewUp.y ,camera.viewUp.z);
    
    // if we have trackball rotation to map (this IS the test I want as it can be explicitly 0.0f)
	if ((gTrackingViewInfo == self) && gTrackBallRotation[0] != 0.0f) {
		glRotatef (gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
        NSLog(@"Trackball rotation %f %f %f %f", gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
	}
	// accumlated world rotation via trackball
	glRotatef (worldRotation[0], worldRotation[1], worldRotation[2], worldRotation[3]);
    //    NSLog(@"world rotation %f %f %f %f", worldRotation[0], worldRotation[1], worldRotation[2], worldRotation[3]);
	
	// object itself rotating applied after camera rotation
    if (objectRotation[0] != objectRotation[0]) {
        objectRotation[0]
        = objectRotation[1]
        =  objectRotation[2]
        = objectRotation[3] = 0.0;
    }
	glRotatef (objectRotation[0], objectRotation[1], objectRotation[2], objectRotation[3]);
    //	NSLog(@"object rotation %f %f %f %f", objectRotation[0], objectRotation[1], objectRotation[2], objectRotation[3]);
	rRot[0] = 0.0f; // reset animation rotations (do in all cases to prevent rotating while moving with trackball)
	rRot[1] = 0.0f;
	rRot[2] = 0.0f;
    
}




static void drawASmallObject ()
{
    drawAnObject(1.0);
}


static void drawALargeObject ()
{
    glPushMatrix();
    glScalef(0.05, 0.05, 0.05);
    drawAnObject(20.0);
    glPopMatrix();
}


static void definePlatforms ()
{
   	
	glNewList(1, GL_COMPILE);
    glBegin(GL_POINTS);
    for(int i = 0; i < 84; i++) {
        short x,y,z;
        x =platformPositions[i][0];
        y = platformPositions[i][1];
        z = platformPositions[i][2]+50;
        short t = tier[i];
        short r = t & 1;
        short g = (t & 2) >> 1;
        short b = (t & 4) >> 2;
        if (1) {
            glColor3f(r,g,b);
            glVertex3f( x,z,y);
            for(int j = 0; j < 219; j++)
                glVertex3f( x + 1.15*ledPositions[j][1],z,y+ 1.15*ledPositions[j][0]);
        }
//        glColor3f(1.0f, 1.0f, 1.0f);
//        glVertex3f( x,0,y);
        
    }
    glEnd();
    glEndList();
}

static void drawPlatforms ()
{
    glPushMatrix();
    
    glScalef(0.0001f, 0.0001f, 0.0001f);
    glTranslatef(0,-5000,0);
    drawModel();
    glCallList(1);
    glPopMatrix();

}


static void drawModel() {
    glColor3f(0.5f, 0.2f, 0.1f);
    // set input data to arrays
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < popNumVerts; i++) {
        if (0 && i % 9 == 0) {
             glColor3f(0.5f, 0.2f, ((i / 10) % 100 / 100.f));
        }
        GLfloat x = popVerts[3*i];
        GLfloat y = popVerts[3*i+1];
        GLfloat z = popVerts[3*i+2];
        glVertex3f( (x - 8970)/1.077, y/1.077+89.5, (-9502-z)/1.077 );
    }
    glEnd();
}


static void drawAnObject (GLfloat fSize)
{
    for(int i = 0; i < num_triangles; i++) {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_TRIANGLES);
        {
            int r = i & 3;
            int g = (i & 12) >> 2;
            int b =  (i & 48) >> 4;
            glColor3f(r/4.0f+0.25f, g/4.0f + 0.25f, b/4.0f+0.25f);
            float x = triangleCenter[i][0];
            float y = triangleCenter[i][1];
            float z = -(i-10)/10.0;
            glVertex3f(  fSize*(0.0+x),  fSize*(0.6+y), fSize*z);
            glVertex3f( fSize*(-0.2+x), fSize*(-0.3+y), fSize*z);
            glVertex3f(  fSize*(0.2+x), fSize*(-0.3+y) , fSize*z);
            
        }
        glEnd();
    }
}

static void drawCube (GLfloat fSize)
{
	long f, i;
	if (1) {
		glColor3f (1.0, 0.5, 0.0);
		glBegin (GL_TRIANGLES);
		for (f = 0; f < num_faces; f++)
			for (i = 0; i < 3; i++) {
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			}
		glEnd ();
	}
	if (1) {
		glColor3f (0.0, 0.0, 0.0);
		for (f = 0; f < num_faces; f++) {
			glBegin (GL_LINE_LOOP);
            for (i = 0; i < 4; i++)
                glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			glEnd ();
		}
	}
}

GLfloat pointParams[] =  {0.01, 0.0, 0.5};
static GLfloat pmax[1];
-(void) drawRect: (NSRect) bounds
{
    NSRect rectView = [self bounds];
	
    [self initOpenGL];
    if (0) NSLog(@" view %f x %f", rectView.size.width, rectView.size.height);
    GLboolean depthTest = glIsEnabled (GL_DEPTH_TEST);
    if (!depthTest)
        NSLog(@"Depth test not enabled");
    
    [self resizeGL];
    [self updateModelView];
    
//    drawALargeObject();
    drawPlatforms();
//    drawCube(1.5);
    glFlush();
}

#pragma mark ---- Camera controls ----

// single set of interaction flags and states
GLint gDollyPanStartPoint[2] = {0, 0};
GLfloat gTrackBallRotation [4] = {0.0f, 0.0f, 0.0f, 0.0f};
GLboolean gDolly = GL_FALSE;
GLboolean gPan = GL_FALSE;
GLboolean gTrackball = GL_FALSE;
MyOpenGLView * gTrackingViewInfo = NULL;

// move camera in z axis
-(void)mouseDolly: (NSPoint) location
{
	GLfloat dolly = (gDollyPanStartPoint[1] -location.y) * -camera.viewPos.z / 300.0f;
	camera.viewPos.z += dolly;
	if (camera.viewPos.z == 0.0) // do not let z = 0.0
		camera.viewPos.z = 0.0001;
	gDollyPanStartPoint[0] = location.x;
	gDollyPanStartPoint[1] = location.y;
}

// ---------------------------------

// move camera in x/y plane
- (void)mousePan: (NSPoint) location
{
	GLfloat panX = (gDollyPanStartPoint[0] - location.x) / (900.0f / -camera.viewPos.z);
	GLfloat panY = (gDollyPanStartPoint[1] - location.y) / (900.0f / -camera.viewPos.z);
	camera.viewPos.x -= panX;
	camera.viewPos.y -= panY;
	gDollyPanStartPoint[0] = location.x;
	gDollyPanStartPoint[1] = location.y;
}

// ---------------------------------



// ---------------------------------


// given a delta time in seconds and current rotation accel, velocity and position, update overall object rotation
- (void) updateObjectRotationForTimeDelta:(CFAbsoluteTime)deltaTime
{
    if (!doRotation)
        return;
	// update rotation based on vel and accel
	float rotation[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GLfloat fVMax = 2.0;
	short i;
	// do velocities
	for (i = 0; i < 3; i++) {
		rVel[i] += rAccel[i] * deltaTime * 30.0;
		
		if (rVel[i] > fVMax) {
			rAccel[i] *= -1.0;
			rVel[i] = fVMax;
		} else if (rVel[i] < -fVMax) {
			rAccel[i] *= -1.0;
			rVel[i] = -fVMax;
		}
		
		rRot[i] += rVel[i] * deltaTime * 30.0;
		if (rRot[i] != rRot[i])
            rRot[i] = 0.0;
		while (rRot[i] > 360.0)
			rRot[i] -= 360.0;
		while (rRot[i] < -360.0)
			rRot[i] += 360.0;
	}
	rotation[0] = rRot[0];
	rotation[1] = 1.0f;
    rotation[2] = rotation[3] = 0.0f;
    //	addToRotationTrackball (rotation, objectRotation);
	rotation[0] = rRot[1];
	rotation[1] = 0.0f; rotation[2] = 1.0f;
	addToRotationTrackball (rotation, objectRotation);
	rotation[0] = rRot[2];
	rotation[2] = 0.0f; rotation[3] = 1.0f;
    //	addToRotationTrackball (rotation, objectRotation);
}

#pragma mark ---  timer ---

static CFAbsoluteTime gStartTime = 0.0f;

// set app start time
static void setStartTime (void)
{
	gStartTime = CFAbsoluteTimeGetCurrent ();
}

// return float elpased time in seconds since app start
static CFAbsoluteTime getElapsedTime (void)
{
	return CFAbsoluteTimeGetCurrent () - gStartTime;
}

// per-window timer function, basic time based animation preformed here
- (void)animationTimer:(NSTimer *)timer
{
	BOOL shouldDraw = NO;
	if (fAnimate) {
		CFTimeInterval deltaTime = CFAbsoluteTimeGetCurrent () - time;
        
		if (deltaTime > 10.0) // skip pauses
			return;
		else {
			// if we are not rotating with trackball in this window
			if (!gTrackball || (gTrackingViewInfo != self)) {
				[self updateObjectRotationForTimeDelta: deltaTime]; // update object rotation
			}
			shouldDraw = YES; // force redraw
		}
	}
	time = CFAbsoluteTimeGetCurrent (); //reset time in all cases
	// if we have current messages
	if (((getElapsedTime () - msgTime) < gMsgPresistance) || ((getElapsedTime () - gErrorTime) < gMsgPresistance))
		shouldDraw = YES; // force redraw
	if (YES == shouldDraw)
		[self drawRect:[self bounds]]; // redraw now instead dirty to enable updates during live resize
}
#pragma mark ---- Mouse/Keyboard handling ----

-(void)keyDown:(NSEvent *)theEvent
{
    NSString *characters = [theEvent characters];
    if ([characters length]) {
        unichar character = [characters characterAtIndex:0];
		switch (character) {
			case 'h':
				// toggle help
				fDrawHelp = 1 - fDrawHelp;
				[self setNeedsDisplay: YES];
				break;
			case 'c':
				// toggle caps
				fDrawCaps = 1 - fDrawCaps;
				[self setNeedsDisplay: YES];
				break;
            case 'u':
                worldRotation [0] = 90;
                worldRotation[1] =
                worldRotation[2]=
                worldRotation[3] = 0.0;
                break;
            case 'b':
                worldRotation [0] = -90;
                worldRotation[1] =
                worldRotation[2] =
                worldRotation[3] = 0.0;
                break;
            case 'f':
                worldRotation [0] =
                worldRotation[1] =
                worldRotation[2] =
                worldRotation[3] = 0.0;
                break;
            case 'r':
                doRotation = !doRotation;
                break;
            case '0':
                [self resetCamera];
                break;
                
                
		}
	}
}

// ---------------------------------

- (void)mouseDown:(NSEvent *)theEvent // trackball
{
    NSLog(@"Mouse down");
    if ([theEvent modifierFlags] & NSControlKeyMask) // send to pan
		[self rightMouseDown:theEvent];
	else if ([theEvent modifierFlags] & NSAlternateKeyMask) // send to dolly
		[self otherMouseDown:theEvent];
	else {
		NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
		location.y = camera.viewHeight - location.y;
		gDolly = GL_FALSE; // no dolly
		gPan = GL_FALSE; // no pan
		gTrackball = GL_TRUE;
		startTrackball (location.x, location.y, 0, 0, camera.viewWidth, camera.viewHeight);
		gTrackingViewInfo = self;
	}
}

// ---------------------------------

- (void)rightMouseDown:(NSEvent *)theEvent // pan
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	location.y = camera.viewHeight - location.y;
	if (gTrackball) { // if we are currently tracking, end trackball
		if (gTrackBallRotation[0] != 0.0)
			addToRotationTrackball (gTrackBallRotation, worldRotation);
		gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
	}
	gDolly = GL_FALSE; // no dolly
	gPan = GL_TRUE;
	gTrackball = GL_FALSE; // no trackball
	gDollyPanStartPoint[0] = location.x;
	gDollyPanStartPoint[1] = location.y;
	gTrackingViewInfo = self;
}

// ---------------------------------

- (void)otherMouseDown:(NSEvent *)theEvent //dolly
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	location.y = camera.viewHeight - location.y;
	if (gTrackball) { // if we are currently tracking, end trackball
		if (gTrackBallRotation[0] != 0.0)
			addToRotationTrackball (gTrackBallRotation, worldRotation);
		gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
	}
	gDolly = GL_TRUE;
	gPan = GL_FALSE; // no pan
	gTrackball = GL_FALSE; // no trackball
	gDollyPanStartPoint[0] = location.x;
	gDollyPanStartPoint[1] = location.y;
	gTrackingViewInfo = self;
}

// ---------------------------------

- (void)mouseUp:(NSEvent *)theEvent
{
	if (gDolly) { // end dolly
		gDolly = GL_FALSE;
	} else if (gPan) { // end pan
		gPan = GL_FALSE;
	} else if (gTrackball) { // end trackball
		gTrackball = GL_FALSE;
		if (gTrackBallRotation[0] != 0.0)
			addToRotationTrackball (gTrackBallRotation, worldRotation);
		gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
	}
	gTrackingViewInfo = NULL;
}

// ---------------------------------

- (void)rightMouseUp:(NSEvent *)theEvent
{
	[self mouseUp:theEvent];
}

// ---------------------------------

- (void)otherMouseUp:(NSEvent *)theEvent
{
	[self mouseUp:theEvent];
}

// ---------------------------------

- (void)mouseDragged:(NSEvent *)theEvent
{
	NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	location.y = camera.viewHeight - location.y;
	if (gTrackball) {
		rollToTrackball (location.x, location.y, gTrackBallRotation);
		[self setNeedsDisplay: YES];
	} else if (gDolly) {
		[self mouseDolly: location];
		[self updateProjection];  // update projection matrix (not normally done on draw)
		[self setNeedsDisplay: YES];
	} else if (gPan) {
		[self mousePan: location];
		[self setNeedsDisplay: YES];
	}
}

// ---------------------------------

- (void)scrollWheel:(NSEvent *)theEvent
{
	float wheelDelta = [theEvent deltaX] +[theEvent deltaY] + [theEvent deltaZ];
	if (wheelDelta)
	{
		GLfloat deltaAperture = wheelDelta * -camera.aperture / 200.0f;
		camera.aperture += deltaAperture;
		if (camera.aperture < 0.1) // do not let aperture <= 0.1
			camera.aperture = 0.1;
		if (camera.aperture > 179.9) // do not let aperture >= 180
			camera.aperture = 179.9;
		[self updateProjection]; // update projection matrix
		[self setNeedsDisplay: YES];
	}
}

// ---------------------------------

- (void)rightMouseDragged:(NSEvent *)theEvent
{
	[self mouseDragged: theEvent];
}

// ---------------------------------

- (void)otherMouseDragged:(NSEvent *)theEvent
{
	[self mouseDragged: theEvent];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

// ---------------------------------

- (BOOL)becomeFirstResponder
{
    return  YES;
}

// ---------------------------------

- (BOOL)resignFirstResponder
{
    return YES;
}

@end
