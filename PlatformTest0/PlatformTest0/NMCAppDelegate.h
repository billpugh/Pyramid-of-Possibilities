//
//  NMCAppDelegate.h
//  PlatformTest0
//
//  Created by Bill on 2/23/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <CoreMotion/CoreMotion.h>


@interface NMCAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic, readonly) CMMotionManager *sharedManager;
@end
